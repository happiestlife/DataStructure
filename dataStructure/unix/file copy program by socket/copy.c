#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>

#define PORT 9000
#define MAX 100
#define SERVER 1
#define CLIENT 2

char buf[BUFSIZ], ack[BUFSIZ];
struct sockaddr_in s_in;
int sd, ns;

void bubblesort(struct dirent* dlist[BUFSIZ], int num) {
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - 1 - i; j++) {
			if (strcmp(dlist[j]->d_name, dlist[j + 1]->d_name) > 0) {
				struct dirent* dtmp = dlist[j];
				dlist[j] = dlist[j + 1];
				dlist[j + 1] = dtmp;
			}
		}
	}
}

// ls -R 명령어와 같은 결과물을 소켓으로 전송하는 함수 
void lsr(char* dir) {
	DIR* dp;
	char sbuf[BUFSIZ];
	char buf[BUFSIZ];

	sprintf(sbuf, "%s:\n", dir);
	if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
		perror("send");
		exit(1);
	}
	memset(sbuf, '\0', sizeof(sbuf));

	if ((dp = opendir(dir)) == NULL) {
		perror("open dir");
		exit(1);
	}

	struct dirent* dent;
	struct dirent* dlist[BUFSIZ];
	int di = 0, i = 0;

	strcpy(buf, dir);

	while (dent = readdir(dp)) {
		if (dent->d_name[0] != '.') {
			sprintf(sbuf, "%s  ", dent->d_name);
			if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
				perror("send");
				exit(1);
			}
			memset(sbuf, '\0', sizeof(sbuf));
			
			i++;

			if (dent->d_type == 4)  dlist[di++] = dent;
		}
	}

	bubblesort(dlist, di);
	if (i % 10 != 0){ 
		sprintf(sbuf, "\n");
		if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
			perror("send");
			exit(1);
		}
		memset(sbuf, '\0', sizeof(sbuf));
	}

	for (int i = 0; i < di; i++) {
		sprintf(buf, "%s/%s", dir, dlist[i]->d_name);

		sprintf(sbuf, "\n");
		if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
			perror("send");
			exit(1);
		}
		memset(sbuf, '\0', sizeof(sbuf));
	
		lsr(buf);

		strcpy(buf, dir);
	}
}

// 클라이언트에 파일을 전송하는 함수입니다. 입력으로는 파일의 이름(절대 경로)입니다. 
void send_file(char* tname){
	printf("\n-- file transmission start --\n");
	printf("-- name : %s --\n", tname);

	char name[BUFSIZ];
	strcpy(name, tname);

	// 파일 접근 시 접근 권한 부족으로 인한 접근 불가, 접근 에러 등과 같은 문제가 발생하면 
	// 클라이언트에 문제 발생했다는 메세지와 함께 해당 파일은 전송 X
	FILE* fp = fopen(name, "r");
	if(fp == NULL){ 
		perror("fopen");
	
		send(ns, "error", 5, 0);
		recv(ns, ack, sizeof(ack), 0);

		fclose(fp);
		return;
	}

	// 파일 크기 측정을 위한 stat()함수
	struct stat fdata;
	stat(name, &fdata);
	int fsize = (int)fdata.st_size;

	// 파일의 크기와 접근 권한 정보를 클라이언트에 송신
	sprintf(buf, "%d %d", fsize, (int)fdata.st_mode);
	send(ns, buf, strlen(buf), 0);

	// 다음에 서버에서 보낼 데이터가 위의 정보와 합쳐지지 않기 위한 ack 메세지
	recv(ns, ack, sizeof(ack), 0);

	printf("   file size : %d, mode : %o--\n", fsize, (int)fdata.st_mode);
	if(fsize == 0){
		// 빈 파일이라면 아무것도 하지 않고 종료
		printf("!! empty file !!\n");	
		printf("-- file transmission terminated --\n\n");

		fclose(fp);
		return;
	}
	
	// 파일에서 데이터를 읽어들여 클라이언트에 송신합니다. 
	// 파일의 크기를 이용하여 더 데이터를 송신할지 while()문을 종료할지 결정합니다.
	while( 1 ){
		printf("   sending...\n");
		memset(buf, '\0', sizeof(buf));	
		fread(buf, sizeof(char), sizeof(buf), fp);
		send(ns, buf, sizeof(buf), 0);
	
		if(fsize < sizeof(buf)) break;
		fsize -= sizeof(buf);
	}

	printf("-- file transmission terminated --\n\n");

	fclose(fp);
	return;
}

// 디렉토리안 모든 파일들을 클라이언트에 전송합니다. 인자는 디렉토리의 절대 경로입니다.
void send_dir(char* tloc){
	printf("<directory transmission start>\n");

	char loc[BUFSIZ];
	sprintf(loc, "%s", tloc);
	
	// 디렉토리안 일반 파일들을 전송하기 위해서 opendir()을 통해 인자로 전달된 디렉토리의 정보를 불러옵니다. 
	DIR* dp = opendir(loc);
	struct dirent* dent;
	struct dirent* dlist[BUFSIZ];
	int dlistlen = 0;

	while (1) {
		// 디렉토리에 전송할 파일이 있는지 확인하고 있다면 지속합니다. 
		dent = readdir(dp);
		if(dent == NULL){
			send(ns, "end", 3, 0);
			break;
		}else {
			send(ns, "no", 2, 0);
		}

		// 아래에서 전송하는 데이터와 위의 데이터가 겹쳐서 전송되는 것을 방지하기 위한 ack 메세지 수신
		recv(ns, ack, sizeof(ack), 0);
		
		// 일반 파일이고 숨겨진 파일이 아닌 경우에만 파일 복사, 검사하는 파일 중 숨겨진 파일이 아니면서 디렉토리인 경우 현재 디렉토리 안 모든 파일들을 복사한 후
		// send_dir()를 재귀호출하면서 현재 디렉토리안에 포함된 디렉토리들도 순회하며 파일을 복사합니다. 
		if (dent->d_type == 8 && dent->d_name[0] != '.') {
			memset(buf, '\0', sizeof(buf));
			sprintf(buf, "%s", dent->d_name);
			send(ns, buf, strlen(buf), 0);
			
			// ack 메세지
			recv(ns, ack, sizeof(ack), 0);

			// 파일 복사
			memset(buf, '\0', sizeof(buf));
			sprintf(buf, "%s/%s", loc, dent->d_name);
			send_file(buf);
		}else{
			send(ns, "skip", 4, 0);
			if(dent->d_type == 4 && dent->d_name[0] != '.') dlist[dlistlen++] = dent;
		}
		
		// 위에서 클라이언트로 send()해 줬음으로 다음에 보내질 end/no와 위에서 전송한 데이터가 겹쳐져서 보내지지 않게 하기 위한 ack 메세지 수신
		recv(ns, ack, sizeof(ack), 0);
	}
	
	// 위에서 end 메세지를 송신함과 동시에 반복문을 탈출하기 때문에 ack 메세지 수신
	recv(ns, ack, sizeof(ack), 0);

	// 현재 디렉토리 안에 포함된 디렉토리 개수를 클라이언트에 전송
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%d", dlistlen);
	send(ns, buf, strlen(buf), 0);
	
	recv(ns, ack, sizeof(ack), 0);

	// send_dir() 재귀 호출을 통한 현재 디렉토리에 포함된 모든 디렉토리 및 파일 전송
	char nloc[BUFSIZ];	
	for (int i = 0; i < dlistlen; i++) {
		memset(buf, '\0', sizeof(buf));
		sprintf(buf, "%s", dlist[i]->d_name);	
		send(ns, buf, sizeof(buf), 0);
		printf("copying loc....\n");
			
		recv(ns, ack, sizeof(ack), 0);

		memset(nloc, '\0', sizeof(nloc));
		sprintf(nloc, "%s/%s", loc, buf);
		printf("  Inner dir copy start!!\n");
		printf("  dir name : %s\n", nloc);
		
		send_dir(nloc);
	}
	printf("<directory transmission terminated>\n");
}

void server(){
	printf("** server **\n");

	// 만들어진 소켓에 주소를 부여하고 연결할 클라이언트 수를 설정
	if( bind(sd, (struct sockaddr*)&s_in, sizeof(s_in)) == -1 ){
		perror("bind");
		exit(1);
	}

	if( listen(sd, 1) == -1){
		perror("listen");
		exit(1);
	}

	// 서버 프로그램을 사용하는 사람이 시그널을 통해 종료시키지 않는 이상 서버 프로그램은 종료되지 않습니다.
	while(1){
		// 만들어진 소켓을 가지고 연결 요청을 한 클라이언트와 연결
		ns = accept(sd, NULL, 0);
		
		// 연결 확인 테스트
		sprintf(ack, "conntected... by server");
		send(ns, ack, strlen(ack), 0);

		memset(ack, '\0', sizeof(ack));
		recv(ns, ack, sizeof(ack), 0);
		printf("%s\n", ack);
	
		// 서버에 대한 lsr 실행 결과를 client에 전송	
		struct passwd* pw = getpwuid(getuid());
		lsr(pw->pw_dir);

		memset(buf, '\0', sizeof(buf));
		char* msg = "\n원하는 디렉토리/파일을 입력하십시오.";
		sprintf(buf, "%s\n", msg);
		if( send(ns, buf, strlen(buf), 0) == -1 ){
			perror("send");
			exit(1);
		}
		
		sleep(1);

		// 종료와 함께 클라이언트는 lsr() 결과물 수신을 종료
		send(ns, "end", 3, 0);
	
		// 클라이언트로부터 원하는 파일 혹은 디렉토리의 이름 및 경로를 받는다.
		memset(buf, '\0', sizeof(buf));
		recv(ns, buf, sizeof(buf), 0);
		
		char* ptr = strtok(buf, " ");
		int file_or_directory;
		char loc[BUFSIZ], name[BUFSIZ];
		for(int i = 0; ptr; i++){		
			switch(i){
				case 0:
					file_or_directory = atoi(ptr);	
					break;
				case 1: 
					strcpy(loc, (char*)ptr); 
					break;
				case 2: 
					strcpy(name, (char*)ptr);	
					break;
			}
			ptr = strtok(NULL, " ");
		}

		printf("loc : %s", loc);

		// 파일 복사
		if(file_or_directory == 1){
			printf(", file name : %s\n", name);
			sprintf(loc, "%s/%s", loc, name);
			
			send_file(loc);  
		}
		// 디렉토리 복사
		else{
			printf("\n");
			send_dir(loc);
		}

		printf("disconnected...\n");	
		// 현재 연결된 클라이언트와 연결을 종료합니다.
		close(ns);
	}
	close(sd);
}

// 서버로부터 파일 데이터를 받아 저장합니다. 인자는 복사하려는 파일의 이름(경로)을 말합니다. 경로는 이 프로그램을 실행시키는 디렉토리를 베이스 디렉토리로 갖습니다. 
void copy_file(char* tname){
	printf("-- start file copy --\n");
	printf("   name : %s \n", tname);

	char name[BUFSIZ];
	strcpy(name, tname);

	FILE* fp = fopen(name, "w");
	if( fp == NULL ) {
		perror("fopen");
		exit(1);
	}

	// 서버로부터 파일의 크기와 접근 권한 정보를 받아옵니다.
	// 만약 서버로부터 에러가 발생했다는 메세지를 받으면 파일은 빈 파일인 채로 놔두고 해당 파일은 복사하지 않습니다.
	memset(buf, '\0', sizeof(buf));
	recv(sd, buf, sizeof(buf), 0);
	if(strcmp(buf, "error") == 0){
		send(sd, "ok", 2, 0);
		printf("   error occured from server...\n");
		fclose(fp);
		return;
	}
	
	char* ptr = strtok(buf, " ");
	int fsize, fmode;
	for(int i = 0; ptr; i++){		
		if(i == 0) fsize = atoi(ptr);
		else fmode = atoi(ptr);
			
		ptr = strtok(NULL, " ");
	}
	// 파일의 접근 권한을 설정합니다.
	chmod(name, fmode);
	printf("   file size : %d, mode : %o\n", fsize, fmode);

	// 아래의 코드에서 받을 파일 데이터와 위에서 받은 데이터가 겹쳐져서 클라이언트로 수신되는 것을 막기 위한 ack 메세지
	send(sd, "ok", 2, 0);

	if(fsize == 0){
		// 빈 파일이라면 파일 복사 종료
		printf("!! empty file !!\n");
		printf("-- file copy terminated --\n\n");
		
		fclose(fp);
		return;
	}
	
	while( 1 ){
		// 파일 데이터를 서버로부터 받아옵니다.
		memset(buf, '\0', sizeof(buf));	
		recv(sd, buf, sizeof(buf), 0);
	
		// 만약 파일의 크기가 buf의 크기보다 작다는 것은 더이상 보낼 파일이 없다는 것을 의미.
		// 서버와 클라이언트 모두 같은 buf를 사용하여 데이터를 주고 받기 때문에 buf를 기준으로 데이터를 저장합니다.
		if(fsize < sizeof(buf)) {
			fwrite(buf, sizeof(char), fsize, fp);
			break; 	
		}else {
			fwrite(buf, sizeof(char), sizeof(buf), fp);
			fsize -= sizeof(buf);
		}
	}
	
	fclose(fp);
	
	printf("-- file copy terminated --\n\n");
}

// 서버의 디렉토리에 저장된 파일, 내부 디렉토리 와 그 디렉토리를 순회하며 찾을 수 있는 파일들을 모두 복사
void copy_dir(char *tloc){
	printf("<< directory copy start >>\n");
	printf("   name : %s\n\n", tloc);
	
	char loc[BUFSIZ], fname[BUFSIZ];
	sprintf(loc, "%s", tloc);

	while(1){
		// 서버로부터 더 이상 복사할 파일이 있는지 수신
		memset(buf, '\0', strlen(buf));
		recv(sd, buf, sizeof(buf), 0);
		if(strcmp(buf, "end") == 0) break;

		// 위에서 전송받은 데이터와 아래의 코드에서 전송 받은 파일 데이터를 분리하여 받기 위한 ack 메세지
		send(sd, "ok", 2, 0);

		// 만약 숨겨진 파일이 아니고 일반 파일이라면 파일을 복사  
		memset(buf, '\0', strlen(buf));
		recv(sd, buf, sizeof(buf), 0);
		if(strcmp(buf, "skip") != 0) {
			send(sd, "ok", 2, 0);

			memset(fname, '\0', sizeof(fname));
			sprintf(fname, "%s/%s", loc, buf);
			copy_file(fname);
		}

		// 위에서 받은 파일 데이터와 이 다음의 실행에서 받을 end/no 데이터를 구분하여 받기 위한 ack 메세지		
		send(sd, "recv success", 12, 0);
	}
	
	// 위의 while()문은 위에서 3번째줄인 break;문을 통해서 탈출
	// 따라서 아래에서 받을 copy_dir() 재귀 호출 반복 횟수와 end/no 데이터를 겹쳐서 받지 않기 위한 ack 메세지 
	send(sd, "end?", 4, 0);

	// copy_dir() 재귀 호출을 반복할 횟수, 즉 현재 복사하려는 디렉토리의 자식 디렉토리(자손 x) 개수를 말합니다.
	memset(buf, '\0', sizeof(buf));
	recv(sd, buf, sizeof(buf), 0);
	int count;
	sscanf(buf, "%d", &count);

	// ack 메세지
	send(sd, "ok", 2, 0);

	// 재귀 호출을 통해 자식 디렉토리를 방문 및 파일 복사
	// 결과론적으로 모든 자손 디렉토리를 방문하여 파일을 복사합니다.
	for (int i = 0; i < count; i++) {
		memset(buf, '\0', sizeof(buf));
		recv(sd, buf, sizeof(buf), 0);

		send(sd, "ok", 2, 0);
		
		memset(fname, '\0', sizeof(fname));
		sprintf(fname, "%s/%s", loc, buf);
		printf(" directory name : %s\n", fname);

		mkdir(fname, 0755);
		copy_dir(fname);
	}

	printf("<< directory copy terminated >>\n\n");
}
	
void client(){
	printf("--client\n");
	
	// 서버와의 연결 상태를 확인
	recv(sd, ack, sizeof(ack), 0);
	printf("%s\n", ack);
	
	send(sd, "connected!", 11, 0);

	// 서버의 디렉토리 및 파일내역 받기 (서버의 홈 디렉토리에서 ls -R 실행 결과물)
	while(1){
		memset(buf, '\0', sizeof(buf));
		recv(sd, buf, BUFSIZ, 0);
		if(strcmp(buf, "end") == 0) break;
		printf("%s", buf);
	}	
	
	// 사용자로부터 원하는 파일/디렉토리의 이름 및 경로를 입력 받습니다.
	char loc[BUFSIZ], name[BUFSIZ];
	int select;
	printf("\n1. 파일  2. 디렉토리\n>> ");
	scanf("%d", &select);

	if(select == 1){
		printf("디렉토리와 파일 이름을 입력하세요.\n ex) /home/사용자명 lsr.c \n>> ");
		fscanf(stdin, "%s %s", loc, name);	
	}
	else{
		printf("디렉토리를 입력하세요.\n ex) /home/사용자명/unix \n>> ");
		fscanf(stdin, "%s", loc);	
	}

	// 사용자 입력을 서버로 송신
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%d %s %s", select, loc, name); 
	send(sd, buf, strlen(buf), 0);
	
	// 아래의 copy_file() / copy_dir()에서 recv()를 수행하기 때문에 겹쳐 받을 데이터가 없습니다.
	// 따라서 ack 메세지는 필요하지 않습니다.  
	
	if(select == 1) copy_file(name);
	else copy_dir(".");

	close(sd);
}
	
int start_connect(){
	// 소켓을 생성합니다. 이 소켓은 인터넷을 통해서 통신을 할 것이고 통신 방법으로는 TCP를 사용합니다.
	// 프로토콜은 지정하지 않았습니다.
	if( (sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	// 연결하려는 소켓의 특성을 명시하는 코드입니다.
	// 인터넷을 통해 통신하고 주소는 127.0.0.1(자기 자신), 포트번호는 9000번 입니다. 
	memset((char*)&s_in, '\0', sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(PORT);
	s_in.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 위에서 명시한 특성을 가진 소켓과 연결을 시도합니다. 실패시 서버가 존재하지 않는다고 판단하고 서버 역할로 프로그램을 작동시킵니다. 다시 말해, 먼저 프로그램을 작동한 사람이 
	// 프로그램을 전달하는 서버 역할을 합니다. 연결하려는 소켓이 존재한다면 파일을 복사받는 클라이언트 역할로 프로그램을 실행합니다.
	if( connect(sd, (struct sockaddr*)&s_in, sizeof(s_in)) == -1 )
		return SERVER;
	else
		return CLIENT;
}

int main() {
	// 서버의 소켓과 연결을 시도하고 아직 연결하려는 소켓이 없다면, 자신이 서버가 되어 소켓을 생성하고 연결 요청을 대기
	// 소켓 존재시 클라이언트로 서버와 연결 요청
	if( start_connect() == SERVER ) server();
	else client();

	printf("\n*--- program end ---*\n");
	return 0;
}

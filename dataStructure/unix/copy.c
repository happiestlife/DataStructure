#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>

#define PORT 9000
#define MAX 1000
#define SERVER 1
#define CLIENT 2

char buf[BUFSIZ];
struct sockaddr_in s_in, cli;
int sd, ns, clientLen = sizeof(cli);
int lsrIndex = 0;

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

void lsr(char* dir) {
	DIR* dp;
	char buf[BUFSIZ];
	char sbuf[BUFSIZ];

	sprintf(sbuf, "%s:\n", dir);
//	printf("%s", sbuf);
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
//			printf("%s", sbuf);
			if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
				perror("send");
				exit(1);
			}
			memset(sbuf, '\0', sizeof(sbuf));
			
			i++;
			//if (i % 10 == 0) printf("\n");

			if (dent->d_type == 4)  dlist[di++] = dent;
		}
	}

	bubblesort(dlist, di);
	if (i % 10 != 0){ 
		sprintf(sbuf, "\n");
//		printf("%s", sbuf);
		if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
			perror("send");
			exit(1);
		}
		memset(sbuf, '\0', sizeof(sbuf));
	}

	for (int i = 0; i < di; i++) {
		sprintf(buf, "%s/%s", dir, dlist[i]->d_name);

		sprintf(sbuf, "\n");
//		printf("%s",sbuf);
		if (send(ns, sbuf, strlen(sbuf), 0) == -1) {
			perror("send");
			exit(1);
		}
		memset(sbuf, '\0', sizeof(sbuf));
	
		lsr(buf);

		strcpy(buf, dir);
	}
}

int connecting(){
	if( bind(sd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1 ){
		perror("bind");
		exit(1);
	}

	if( listen(sd, 5) == -1){
		perror("listen");
		exit(1);
	}

	return accept(sd, (struct sockaddr *)&cli, &clientLen);
}

void send_file(char* loc){
	printf("\n--file transmission start--\n");
	
	FILE* fp = fopen((char*)loc, "r");
	if(fp == NULL){ 
		perror("fopen");
		exit(1);	
	}
	
	memset(buf, '\0', sizeof(buf));	
	while( fread(buf, 1, sizeof(buf), fp) > 0){
		send(ns, buf, strlen(buf), 0);
		memset(buf, '\0', strlen(buf));
	}
	
	fclose(fp);
	
	printf("--file transmission terminated--\n");
}

void send_dir(char* loc){
	printf("<directory transmission start>\n");

	DIR* dp = opendir(loc);
	struct dirent* dent;
	int di = 0, i = 0;

	dent = readdir(dp);
	while (1) {
		if (dent->d_type != 4 && dent->d_name[0] != '.') {
			sprintf(buf, "%s/%s", loc, dent->d_name);
			send(ns, buf, strlen(buf), 0);
			printf("%s file\n", buf);
			recv(ns, (void*)NULL, 0, 0);
			send_file(buf);
			memset(buf, '\0', sizeof(buf));

			recv(ns, (void*)NULL, 0, 0);
			if( (dent = readdir(dp)) == NULL){
				send(ns, "end", 3, 0);
				break;
			}else
				send(ns, "no", 2, 0);
		}
	}

	printf("<directory transmission terminated>\n");
}

void server(){
	printf("--server\n");

	if( (ns = connecting()) == -1){
		perror("connect");
		exit(1);
	}
	
	// lsr을 실행하여 결과를 client에 전송	
	lsr("/home/chickenman");

	char* msg = "\n원하는 디렉토리/파일을 입력하십시오.\nEx) /home/chickenman/unix lsr.c";
	sprintf(buf, "%s\n", msg);
	if( send(ns, buf, strlen(buf), 0) == -1 ){
		perror("send");
		exit(1);
	}
		
	sleep(1);

	memset(buf, '\0', strlen(buf));
	sprintf(buf, "end");
	send(ns, buf, strlen(buf), 0);
	
	memset(buf, '\0', strlen(buf));
	if( recv(ns, buf, sizeof(buf), 0) == -1) {
		perror("recv");
		exit(1);
	}
	
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

	// 파일일 경우
	if(file_or_directory == 1){
		printf(", file name : %s\n", name);
		sprintf(loc, "%s/%s", loc, name);
		send_file(loc);	
	}
	else{
		printf("\n");
		send_dir(loc);
	}

	close(ns);
	close(sd);
}

void copy_file(char* name){
	printf("--start file copy--\n");

	FILE* fp = fopen(name, "w");
	if( fp == NULL ) {
		perror("fopen");
		exit(1);
	}

	char exit[3];
	while(1){
		memset(buf, '\0', strlen(buf));
		recv(sd, buf, sizeof(buf), 0);
		fwrite(buf, 1, strlen(buf), fp);	
		
		if(strlen(buf) < sizeof(buf)) break;
	}
	fclose(fp);

	printf("--file copy terminated--\n");
}

void copy_dir(char* loc){
	printf("--directory copy start--\n");

	while(1){
		memset(buf, '\0', strlen(buf));
		recv(sd, buf, sizeof(buf), 0);
		printf("%s file--\n", buf);
		send(sd, "ok", 2, 0);
		copy_file(buf);
		
		send(sd, "Finished?", 9, 0);
	
		recv(sd, buf, sizeof(buf), 0);
		printf("Finished? %s\n", buf);
		if(strcmp(buf, "end") == 0) break;
	}

	printf("--directory copy terminated--\n");
}
	
void client(){
	printf("--client\n");
	
	// 서버의 디렉토리 및 파일내역 받기 
	while(1){
		memset(buf, '\0', sizeof(buf));
		recv(sd, buf, BUFSIZ, 0);
		if(strcmp(buf, "end") == 0) break;
		printf("%s", buf);
	}	
	
	char loc[BUFSIZ], name[BUFSIZ];
	int select;
	printf("\n1. 파일  2. 디렉토리\n>> ");
	scanf("%d", &select);

	if(select == 1){
		printf("디렉토리와 파일 이름을 입력하세요.\n>> ");
		fscanf(stdin, "%s %s", loc, name);	
	}
	else{
		printf("디렉토리를 입력하세요.\n>> ");
		fscanf(stdin, "%s", loc);	
	}

	sprintf(buf, "%d %s %s", select, loc, name); 
	if( send(sd, buf, strlen(buf), 0) == -1 ){
		perror("send");
		exit(1);
	}
	
	if(select == 1) copy_file(name);
	else copy_dir(loc);

	close(sd);
}
	
int start_connect(int port){
	if( (sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	memset((char*)&s_in, '\0', sizeof(s_in));
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr("127.0.0.1");

	if( connect(sd, (struct sockaddr*)&s_in, sizeof(s_in)) == -1 )
		return SERVER;
	else
		return CLIENT;
}

int main(int argc, char* argv[]) {
	if( start_connect(atoi(argv[1])) == SERVER ) server();
	else client();

	printf("\nprogram end\n");
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>

void bubblesort(struct dirent* dlist[BUFSIZ], int num){
	for(int i = 0; i < num - 1; i++) {
		for(int j = 0; j < num - 1 - i; j++) {
			if(strcmp(dlist[j]->d_name, dlist[j+1]->d_name) > 0){
				struct dirent* dtmp = dlist[j];
				dlist[j] = dlist[j+1];
				dlist[j+1] = dtmp;
			}
		}
	}	
}

void lsr(char* dir){
	// dir : 탐색할 디렉토리 주소입니다. "./~~" 형식 ( 처음에는 "."입니다.)
	DIR* dp;
	char buf[BUFSIZ];

	printf("%s:\n", dir);

	if( (dp = opendir(dir)) == NULL){
		perror("open dir");
		exit(1);
	}

	struct dirent* dent;
	struct dirent* dlist[BUFSIZ];
	int di = 0, i = 0;

	// buf에 현재 탐색할려 하는 주소를 임시 저장합니다.
	strcpy(buf, dir);

	// 탐색할 디렉토리안의 개체들을 하나씩 방문하여 출력하고, 파일 종류가 디렉토리인 파일들은 dlist에 저장하였다가 뒤에서 lsr()을 통해 탐색합니다. 
	while( dent = readdir(dp) ){

		// 숨겨진 파일('.'으로 시작하는 파일)을 제외한 모든 파일을 출력합니다. 한번에 10개씩 출력합니다.
		if(dent->d_name[0] != '.'){
			printf("%s  ", dent->d_name);
			i++;
			if( i % 10 == 0 ) printf("\n");

			if (dent->d_type == 4)  dlist[di++] = dent;
		}
	}	

	// 마지막으로 발견된 디렉토리들은 정렬된 순서(영어(abc...)->한글(가나다...))로 방문하기 위해 dlist에 버블 정렬을 실행합니다.
	bubblesort(dlist, di);	
	if(i % 10 != 0) printf("\n");

	for(int i = 0; i < di; i++){

		// 위의 stat()에서 "탐색할 디렉토리/entity이름"의 형식과 같이 현재 탐색하고 있는 디렉토리에 포함되어 있는 디렉토리를
		// 방문하기 위해서 형식을 맞춰줍니다.
		sprintf(buf, "%s/%s", dir, dlist[i]->d_name);
		
		// 현재 탐색하고 있는 디렉토리안에 포함된 디렉토리에 대해서 lsr() 재귀적으로 실행합니다.
		printf("\n");	
		lsr(buf);
		
		// 처음 디렉토리(dir)안의 디렉토리를 방문하기 위해서 buf에 처음 디렉토리 주소를 저장합니다.
		strcpy(buf, dir);
	}			
}

void main(){
	lsr(".");
	// 시작 디렉토리는 현재 디렉토리입니다.
}

#include<vector>
#include<queue>
#include<functional> 
#include<algorithm>
#pragma warning(disable:4996)

using namespace std;
#define MAX 100
int n, m;
vector<int> graph[MAX];
vector<bool> isVisited[MAX];
void init() {
	for (int i = 1; i <= n; i++)
		isVisited[i].push_back(false);
}

void dfs(int vindex) {
	if (isVisited[vindex][0] == true) return;
	
	printf("%d ", vindex);
	isVisited[vindex][0] = true;

	for (int i = 0; i < graph[vindex].size(); i++) {
		dfs(graph[vindex][i]);
	}
}

void insert() {
	FILE* fp = fopen("graph1.txt", "r");
	if (fp == NULL) {
		printf("error");
		exit(1);
	}

	int u, v;
	fscanf(fp, "%d %d", &n, &m);
	for (int i = 0; i < 2*m; i++) {
		fscanf(fp, "%d %d", &u, &v);
		graph[u].push_back(v);
	}

	fclose(fp);
}
int main(void) {
	insert();
	init();

	printf("--graph--\n");
	for (int i = 1; i <= n; i++) {
		printf("%d : ", i);
		for (int j = 0; j < graph[i].size(); j++) {
			printf("<%d, %d> ", i, graph[i][j]);
		}
		printf("\n");
	}

	int st = 1;
	for (int i = 1; i <= n; i++) {
		if (isVisited[i][0] == false) {
			printf("\n%dst connected component\n", st++);
			dfs(i);
		}
	}
	return 0;
}
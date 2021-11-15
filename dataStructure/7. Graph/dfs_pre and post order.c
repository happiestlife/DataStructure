#include<vector>
#include<queue>
#include<functional> 
#include<algorithm>
#pragma warning(disable:4996)

using namespace std;
#define MAX 100
int n, m;
int order;
vector<int> graph[MAX];
vector<bool> isVisited[MAX];
vector<int> pre[MAX];
vector<int> post[MAX];

void init() {
	for (int i = 1; i <= n; i++) {
		isVisited[i].push_back(false);
		pre[i].push_back(-1);
		post[i].push_back(-1);
	}
}

void dfs(int vindex) {
	if (isVisited[vindex][0] == true) return;
	pre[vindex][0] = ++order;
	isVisited[vindex][0] = true;

	for (int i = 0; i < graph[vindex].size(); i++) {
		dfs(graph[vindex][i]);
	}
	post[vindex][0] = ++order;
}

void insert() {
	FILE* fp = fopen("graph1.txt", "r");
	if (fp == NULL) {
		printf("error");
		exit(1);
	}

	int u, v;
	fscanf(fp, "%d %d", &n, &m);
	for (int i = 0; i < 2 * m; i++) {
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
		for (int j = 0; j < graph[i].size(); j++)
			printf("<%d, %d> ", i, graph[i][j]);
		printf("\n");
	}

	int st = 1;
	for (int i = 1; i <= n; i++)
		if (isVisited[i][0] == false) dfs(i);

	printf("\n--pre & post order--\n");
	for (int i = 1; i <= n; i++) printf("%d : pre = %d, post = %d\n", i, pre[i][0], post[i][0]);

	return 0;
}
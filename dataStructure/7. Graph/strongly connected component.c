#include<vector>
#include<queue>
#include<functional> 
#include<algorithm>
#include<algorithm>
#pragma warning(disable:4996)

using namespace std;
#define MAX 100
int n, m;
int order;
vector<int> graph[MAX];
vector<int> rgraph[MAX];
vector<bool> isVisited[MAX];
vector<int> post[MAX];

void init() {
	for (int i = 1; i <= n; i++) {
		isVisited[i].push_back(false);
		post[i].push_back(-1);
	}
}

bool sccCompare(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}

bool compare(int a, int b) {
	return a > b;
}


void insert() {
	FILE* fp = fopen("graph2.txt", "r");
	if (fp == NULL) {
		printf("error");
		exit(1);
	}

	int u, v;
	fscanf(fp, "%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		fscanf(fp, "%d %d", &u, &v);
		graph[u].push_back(v);
	}

	fclose(fp);
}

void reverse() {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			rgraph[graph[i][j]].push_back(i);
		}
	}

	for (int i = 1; i <= n; i++) sort(rgraph[i].begin(), rgraph[i].end(), compare);
}


void rdfs(int vindex) {
	if (isVisited[vindex][0] == true) return;

	//printf("%d ", vindex);
	isVisited[vindex][0] = true;

	for (int i = 0; i < rgraph[vindex].size(); i++) {
		rdfs(rgraph[vindex][i]);
	}
	post[vindex][0] = ++order;
}

void dfs(int vindex) {
	if (isVisited[vindex][0] == true) return;

	printf("%d ", vindex);
	isVisited[vindex][0] = true;

	for (int i = 0; i < graph[vindex].size(); i++) {
		dfs(graph[vindex][i]);
	}
}

void scc() {

	// graph reverse
	reverse();

	printf("\n--reversed--\n");
	for (int i = 1; i <= n; i++) {
		printf("%d : ", i);
		for (int j = 0; j < rgraph[i].size(); j++)
			printf("<%d, %d> ", i, rgraph[i][j]);
		printf("\n");
	}
	printf("\n");

	// reverse된 graph의 dfs() 
	for (int i = n; i >= 1; i--)
		if (isVisited[i][0] == false)  rdfs(i);

	vector<pair<int, int>> sortedPost;
	for (int i = 1; i <= n; i++)
		sortedPost.push_back(make_pair(i, post[i][0]));
	sort(sortedPost.begin(), sortedPost.end(), sccCompare);

	for (int i = 1; i <= n; i++) isVisited[i][0] = false;

	// 기존 graph에서 rgraph의 post 번호가 높은 순으로 dfs()
	int num = 1;
	printf("--strongly connected component--\n");
	for (int i = 0; i < sortedPost.size(); i++) {
		if (isVisited[sortedPost[i].first][0] == false) {
			printf("%dst strongly connected component\n", num++);
			dfs(sortedPost[i].first);
			printf("\n");
		}
	}
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

	scc();

	return 0;
}
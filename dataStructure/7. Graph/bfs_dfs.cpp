#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
#pragma warning(disable:4996)

#define MAX 10000

using namespace std;

int vnum, edgenum, startv;
vector<int> edge[MAX];
bool isVisited[MAX];

void init() {
	for (int i = 0; i < MAX; i++) 
		isVisited[i] = false;
}

void insert() {
	int u, v;
	for (int i = 0; i < edgenum; i++) {
		scanf("%d %d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	for (int i = 1; i <= vnum; i++)
		sort(edge[i].begin(), edge[i].end());
}

void dfs(int u) {
	if (isVisited[u] == false) {
		isVisited[u] = true;
		printf("%d ", u);
		for (int i = 0; i < edge[u].size(); i++)
			dfs(edge[u][i]);
	}
}

void bfs(int u) {
	queue<int> q;
	q.push(u);

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		if (isVisited[v] == false) {
			printf("%d ", v);
			isVisited[v] = true;
		}

		for (int i = 0; i < edge[v].size(); i++) {
			int nextv = edge[v][i];
			if (isVisited[nextv] == false)
				q.push(nextv);
		}
	}
}

int main() {
	init();
	
	scanf("%d %d %d", &vnum, &edgenum, &startv);
	insert();

	dfs(startv);
	printf("\n");

	init();
	bfs(startv);
}
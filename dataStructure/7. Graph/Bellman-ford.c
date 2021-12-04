#include<iostream>
#include<queue>
#include<algorithm>
#pragma warning(disable:4996)
using namespace std;
#define MAX 1000000

int v, e;
int dist[MAX];
int pre[MAX];
vector<pair<int, int>> graph[MAX];
struct cmp {
	bool operator()(pair<int, int> n1, pair<int, int> n2) {
		return n1.second > n2.second;
	}
};

void print() {
	printf("<graph>\n");
	printf("--------------------------\n");
	for (int i = 1; i <= v; i++) {
		printf("%d : ", i);
		for (int j = 0; j < graph[i].size(); j++)
			printf("%d(w = %d), ", graph[i][j].first, graph[i][j].second);
		printf("\n");
	}
	printf("\n");
}

void init() {
	FILE* fp = fopen("graph.txt", "r");
	fscanf(fp, "%d %d", &v, &e);

	int from, to, w;
	for (int i = 0; i < e; i++) {
		fscanf(fp, "%d %d %d", &from, &to, &w);
		graph[from].push_back(make_pair(to, w));
	}

	for (int i = 0; i < v; i++)
		sort(graph[i].begin(), graph[i].end());
	print();

	for (int i = 1; i <= v; i++) {
		dist[i] = 1000000000;
		pre[i] = i;
	}
}

void bellmanford() {
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> q;

	dist[1] = 0;
	q.push(make_pair(1, dist[1]));
	while (!q.empty()) {
		int u = q.top().first;
		q.pop();
		for (int i = 1; i < v; i++) {
			for (int j = 0; j < graph[u].size(); j++) {
				int v = graph[u][j].first;
				int ndist = dist[u] + graph[u][j].second;

				if (dist[v] > ndist) {
					dist[v] = ndist;
					pre[v] = u;
					q.push(make_pair(v, dist[v]));
				}
			}
		}
	}

	printf("--Bellman-ford algorithm--\n");
	for (int i = 2; i <= v; i++)
		printf("1 to %d is %d\n", i, dist[i]);
	printf("\n--prev vertex--\n");
	for (int i = 1; i <= v; i++)
		printf("%d prev is %d\n", i, pre[i]);
}

int main() {
	init();
	bellmanford();
	return 0;
}
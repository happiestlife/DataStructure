#include<iostream>
#include<queue>
#include<stack>
#include<algorithm>
#pragma warning(disable:4996)

using namespace std;

#define MAX 1000000
#define min(x,y) x < y ? x : y

int v, e;
int dfn[MAX];
int low[MAX];
int dfnum = 0;
vector<int> graph[MAX];
stack<pair<int, int>> s;

bool cmp(int a, int b){
	return a > b;
}

void print() {
	printf("<graph>\n");
	printf("--------------------------\n");
	for (int i = 0; i < v; i++) {
		printf("%d : ", i);
		for (int j = 0; j < graph[i].size(); j++)
			printf("%d ", graph[i][j]);
		printf("\n");
	}
	printf("\n");
}

void init() {
	FILE* fp = fopen("graph1.txt","r");
	fscanf(fp, "%d %d", &v, &e);

	int from, to;
	for (int i = 0; i < 2*e; i++) {
		fscanf(fp, "%d %d", &from, &to);
		graph[from].push_back(to);
	}

	for (int i = 0; i < v; i++)
		sort(graph[i].begin(), graph[i].end(), cmp);
	print();

	for (int i = 0; i < v; i++)
		dfn[i] = -1;
}

void dfs(int v, int pv) {
	dfn[v] = dfnum;
	low[v] = dfnum++;

	bool artcul = false;
	for (int i = 0; i < graph[v].size(); i++) {
		int cv = graph[v][i];
		if (dfn[cv] < 0) {
			s.push(make_pair(v, cv));
			dfs(cv, v);
			if (low[cv] < low[v]) low[v] = min(low[cv], dfn[v]);
			if (low[cv] >= dfn[v]) {
				printf("%d is articulation point!\n", v);
				printf("------------------------\n");
				pair<int, int> p;
				do {
					p = s.top();
					s.pop();
					printf("<%d, %d>\n", p.first, p.second);
				} while (p.first != v && p.second != cv);
				cout << endl;
			}
		}
		else if (cv != pv) {
			low[v] = min(low[cv], dfn[v]);
		}
	}

}

void bcc() {
	dfs(0, -1);
}

int main() {
	init();
	bcc();
	return 0;
}
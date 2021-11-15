#include<vector>
#include<deque>
#include<algorithm>
#pragma warning(disable:4996)

using namespace std;
#define MAX 100

int n, m;
int u, v, w;
// <(u,v), w>
vector<int> vertex[MAX];
vector<pair<pair<int, int>,int>> sortedEdge;
vector<pair<int, int>> result;


bool kruskal() {
	for (int i = 0; i < sortedEdge.size(); i++) {
		int fromv = sortedEdge[i].first.first;
		int tov = sortedEdge[i].first.second;
		if (vertex[fromv][0] == vertex[tov][0]) continue;
		else {
			result.push_back(make_pair(fromv, tov));
			for (int j = 1; j <= n; j++) 
				if(vertex[j][0] == vertex[tov][0]) vertex[j][0] = vertex[fromv][0];
		}
	}
	if (result.size() == n - 1) return true;
	else return false;
}

bool sorting(pair<pair<int,int>,int> p, pair<pair<int,int>,int> p2) {
	return p.second < p2.second;
}

bool check(int from, int to) {
	for (int i = 0; i < sortedEdge.size(); i++) {
		if (sortedEdge[i].first.first == from && sortedEdge[i].first.second == to)
			return false;
	}
	return true;
}

int main(void) {
	FILE* fp = fopen("graph.txt", "r");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}

	fscanf(fp, "%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		vertex[i].push_back(i);
	}
	for (int i = 0; i < m*2; i++) {
		fscanf(fp, "%d %d %d", &u, &v, &w);
		if(check(v,u))	sortedEdge.push_back(make_pair(make_pair(u, v), w));
	}

	sort(sortedEdge.begin(), sortedEdge.end(), sorting);
	printf("--sorted edges--\n");
	for (int i = 0; i < sortedEdge.size(); i++) {
		printf("(%d, %d), weight = %d\n", 
		sortedEdge[i].first.first, sortedEdge[i].first.second, sortedEdge[i].second);
	}
	printf("\n");

	printf("--minimun cost spanning tree with kruskal algorithm--\n");
	if (kruskal()) {
		for (int i = 0; i < result.size(); i++)
			printf("<%d, %d>\n", result[i].first, result[i].second);
	}
	else
		printf("false\n");

	fclose(fp);
	return 0;
}
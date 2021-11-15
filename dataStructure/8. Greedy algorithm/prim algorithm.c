#include<vector>
#include<queue>
#include<functional> 
#include<algorithm>
#pragma warning(disable:4996)

using namespace std;
#define MAX 100

struct cmp {
	bool operator()(pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {
		return a.second > b.second;
	}
};

int n, m;
int u, v, w;
// <(u,v), w>
vector<int> vertex;
vector<pair<int, int>> graph[MAX];
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, cmp> incidentEdge;
vector<pair<int, int>> result;

bool inResultCheck(int fromv, int tov) {
	for (int i = 0; i < result.size(); i++) {
		if (result[i].first == tov && result[i].second == fromv)
			return false;
	}
	return true;
}
bool inVertex(int tov) {
	for (int i = 0; i < vertex.size(); i++) 
		if (vertex[i] == tov) return false;
	return true;
}

bool prim() {
	vertex.push_back(1);

	while(vertex.size() < n) {

		// min heap 사용
		for (int i = 0; i < vertex.size(); i++) {
			int checkedv = vertex.at(i);
			for (int j = 0; j < graph[checkedv].size(); j++) {
				int incidentv = graph[checkedv][j].first;
				int incidentw = graph[checkedv][j].second;
				if(inResultCheck(checkedv, incidentv) && inVertex(incidentv)) incidentEdge.push(make_pair(make_pair(checkedv, incidentv), incidentw));
			}
		}
		if (incidentEdge.size() == 0) return false;

		pair<pair<int, int>, int> minEdge;
		int fromv, tov;
		bool inResult = false;
		while (!incidentEdge.empty()) {
			minEdge = incidentEdge.top();
			fromv = minEdge.first.first;
			tov = minEdge.first.second;
			for (int i = 0; i < result.size(); i++) 
				if (result[i].first == fromv && result[i].second == tov) inResult = true;

			if (!inResult) break;
			else incidentEdge.pop();
			inResult = false;
		}
		if(!inResult) result.push_back(make_pair(fromv, tov));
		
		bool fv = false, tv = false;
		for (int i = 0; i < vertex.size(); i++) {
			if (vertex[i] == fromv) fv = true;
			else if (vertex[i] == tov) tv = true;

			if (fv && tv == true) break;
		}
		if (!fv) vertex.push_back(fromv);
		else if (!tv) vertex.push_back(tov);

		while (!incidentEdge.empty())   incidentEdge.pop();
	}
}



int main(void) {
	FILE* fp = fopen("graph.txt", "r");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}

	fscanf(fp, "%d %d", &n, &m);
	for (int i = 0; i < m*2; i++) {
		fscanf(fp, "%d %d %d", &u, &v, &w);
		graph[u].push_back(make_pair(v, w));
	}
	printf("--graph--\n");
	for (int i = 1; i <= n; i++) {
		printf("%d : ", i);
		for (int j = 0; j < graph[i].size(); j++) {
			printf("<%d, %d> ", graph[i][j].first, graph[i][j].second);
		}
		printf("\n");
	}

	prim();
	printf("\n--minimum cost spanning tree with prim algorithm--\n");
	for (int i = 0; i < result.size(); i++)
		printf("%d, %d\n", result[i].first, result[i].second);

	fclose(fp);
	return 0;
}
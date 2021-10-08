#include<stdio.h>
typedef struct Edge;
typedef struct Vertice;
typedef struct LinkedGraph;

typedef struct Edge {
    struct Vertice* dest;
    struct Edge* link;
}Edge;

typedef struct Vertice {
    int num;
    char isVisited;
    struct Vertice* link;
    struct Edge* edgeLink;
}Vertice;

typedef struct LinkedGraph {
    int size;
    struct Vertice* link;
}LinkedGraph;

void initGraph(LinkedGraph* linkedGraph) {
    linkedGraph->link = NULL;
    linkedGraph->size = 0;
}

void insertVertice(LinkedGraph* linkedGraph, int num) {
    Vertice* newVertice = (Vertice*)malloc(sizeof(Vertice));
    if (!newVertice) {
        printf("memory assignment error\n");
        return;
    }
    newVertice->num = num;
    newVertice->edgeLink = NULL;
    newVertice->isVisited = 0;

    if (linkedGraph->link == NULL) {
        linkedGraph->link = newVertice;
        newVertice->link = NULL;
    }
    else {
        newVertice->link = linkedGraph->link;
        linkedGraph->link = newVertice;
    }
    linkedGraph->size += 1;
}

void insertEdge(LinkedGraph* linkedGraph, int from, int to) {
    if (linkedGraph == NULL || linkedGraph->link == NULL) {
        printf("no graph data\n");
        return;
    }
    Vertice* fromVertice = linkedGraph->link;
    while (fromVertice) {
        if (fromVertice->num == from)
            break;
        fromVertice = fromVertice->link;
    }

    Vertice* toVertice = linkedGraph->link;
    while (toVertice) {
        if (toVertice->num == to)
            break;
        toVertice = toVertice->link;
    }

    if (fromVertice == NULL) {
        printf("There is no vertice whose num is %d\n", from);
        return;
    }
    else {
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        if (!newEdge) {
            printf("memory assignment error\n");
            return;
        }
        newEdge->dest = toVertice;

        if (fromVertice->edgeLink == NULL) {
            fromVertice->edgeLink = newEdge;
            newEdge->link = NULL;
        }
        else {
            newEdge->link = fromVertice->edgeLink;
            fromVertice->edgeLink = newEdge;
        }
    }
}

void printGraph(LinkedGraph* linkedGraph) {
    for (Vertice* i = linkedGraph->link; i; i = i->link) {
        printf("Vertice num : %d\n", i->num);
        for (Edge* j = i->edgeLink; j; j = j->link) {
            printf("%d -> %d\n", i->num, j->dest->num);
        }
        printf("\n");
    }
}

void dfs(Vertice* vertice) {
    printf("%d\n", vertice->num);
    vertice->isVisited++;

    Edge* v = vertice->edgeLink;
    while (v) {
        if (!v->dest->isVisited)
            dfs(v->dest);
        v = v->link;
    }
}

void depthFirstSearch(Vertice* vertice) {
    while (vertice) {
        if (!vertice->isVisited) {
            dfs(vertice);
        }
        vertice = vertice->link;
    }
}

int main() {
    LinkedGraph* graph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
    initGraph(graph);
    for (int i = 5; i >=0 ; i--)
        insertVertice(graph, i + 1);

    insertEdge(graph, 1, 4);
    insertEdge(graph, 1, 2);
    insertEdge(graph, 2, 3);
    insertEdge(graph, 2, 1);
    insertEdge(graph, 3, 4);
    insertEdge(graph, 3, 2);
    insertEdge(graph, 4, 6);
    insertEdge(graph, 4, 5);
    insertEdge(graph, 4, 3);
    insertEdge(graph, 4, 1);
    insertEdge(graph, 5, 4);
    insertEdge(graph, 6, 4);

    printGraph(graph);

    depthFirstSearch(graph->link);
}
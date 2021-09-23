#include<stdio.h>
typedef struct Edge{
    int dest;
    struct Edge* link;
}Edge;

typedef struct Vertice{
    int type;
    struct Vertice* link;
    struct Edge* edgeLink;
}Vertice;

typedef struct LinkedGraph{
    int size;
    struct Vertice* link;
}LinkedGraph;

void initGraph(LinkedGraph* linkedGraph){
    linkedGraph->link = NULL;
    linkedGraph->size = 0;
}

void insertVertice(LinkedGraph* linkedGraph, int type){
    Vertice* newVertice = (Vertice*)malloc(sizeof(Vertice));
    if(!newVertice){
        printf("memory assignment error\n");
        return;
    }
    newVertice->type = type;
    newVertice->edgeLink = NULL;

    if(linkedGraph->link == NULL){
        linkedGraph->link = newVertice;
        newVertice->link = NULL;
    } else{
        newVertice->link = linkedGraph->link;
        linkedGraph->link = newVertice;
    }
    linkedGraph->size += 1;
}

void insertEdge(LinkedGraph* linkedGraph, int from, int to){
    if(linkedGraph == NULL || linkedGraph->link == NULL){
        printf("no graph data\n");
        return;
    }
    Vertice* vertice = linkedGraph->link;

    while(vertice){
        if(vertice->type == from)
            break;
        vertice = vertice->link;
    }

    if(vertice == NULL){
        printf("There is no vertice whose type is %d\n", from);
        return;
    }else{
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        if(!newEdge){
            printf("memory assignment error\n");
            return;
        }
        newEdge->dest = to;
        if(vertice->edgeLink == NULL){
            vertice->edgeLink = newEdge;
            newEdge->link = NULL;
        }else{
            newEdge->link = vertice->edgeLink;
            vertice->edgeLink = newEdge;
        }
    }
}

void printGraph(LinkedGraph* linkedGraph){
    for(Vertice* i = linkedGraph->link; i; i = i->link){
        printf("Vertice type : %d\n", i->type);
        for(Edge* j = i->edgeLink; j; j = j->link){
            printf("%d -> %d\n", i->type, j->dest);
        }
        printf("\n");
    }
}

int main(){
    LinkedGraph* graph = (LinkedGraph*)malloc(sizeof(LinkedGraph));
    initGraph(graph);
    for (int i = 0; i < 5; i++)
        insertVertice(graph, i + 1);

    insertEdge(graph, 1, 2);
    insertEdge(graph, 1, 5);
    insertEdge(graph, 1, 4);
    insertEdge(graph, 2, 1);
    insertEdge(graph, 2, 3);
    insertEdge(graph, 3, 2);
    insertEdge(graph, 3, 4);
    insertEdge(graph, 4, 1);
    insertEdge(graph, 4, 3);
    insertEdge(graph, 5, 1);
    insertEdge(graph, 5, 3);

    printGraph(graph);
}
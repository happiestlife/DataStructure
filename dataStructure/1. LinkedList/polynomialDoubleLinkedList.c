#include<stdio.h>
typedef struct term{
    int coef, expo;
    struct term* link;
}term;

typedef struct poly{
    struct term* head;
    struct term* tail;
}poly;

void init(poly* head){
    head->head = NULL;
    head->tail = NULL;
}

void insert(poly* h, int _coef, int _expo){
    term* newNode = (term*)malloc(sizeof(term));
    if(!newNode){
        fprintf(stderr,"%s\n", "error");
        return;
    }

    newNode->coef = _coef;
    newNode->expo = _expo;
    newNode->link = NULL;
    if(h->head == NULL){
        h->head = newNode;
        h->tail = newNode;
    }else{
        h->tail->link = newNode;
        h->tail = newNode;
    }
}

poly* polyAdd(poly* poly1, poly* poly2){
    poly* newPoly = (poly*)malloc(sizeof(poly));;
    init(newPoly);
    term* polyData1 = poly1->head;
    term* polyData2 = poly2->head;

    while(polyData1 && polyData2) {
        int poly1Expo = polyData1->expo;
        int poly2Expo = polyData2->expo;

        if(poly1Expo > poly2Expo){
            insert(newPoly, polyData1->coef, poly1Expo);
            polyData1 = polyData1->link;
        }else if(poly1Expo == poly2Expo){
            insert(newPoly, polyData1->coef + polyData2->coef, poly1Expo);
            polyData1 = polyData1->link;
            polyData2 = polyData2->link;
        }else{
            insert(newPoly, polyData2->coef, poly2Expo);
            polyData2 = polyData2->link;
        }
    }

    for(; polyData1; polyData1 = polyData1->link){
        insert(newPoly, polyData1->coef, polyData1->expo);
    }
    for (; polyData2; polyData2 = polyData2->link) {
        insert(newPoly, polyData2->coef, polyData2->expo);
    }

    return newPoly;
}

void polyPrint(poly* h){
    term* head = h->head;
    while(1){
        printf("%d^%d ", head->coef, head->expo);
        head = head->link;
        if(head == NULL) break;
        printf("+ ");
    }
    printf("\n");
}


int main(){
    poly poly1, poly2;
    poly* poly3;

    init(&poly1); init(&poly2);

    for(int i = 5; i >= 1; i--){
        insert(&poly1, i, i);
        if(i >= 3)
            insert(&poly2, i, i);
    }
    polyPrint(&poly1);
    polyPrint(&poly2);
    printf("---------------------------------------------------------------\n");
    poly3 = polyAdd(&poly1, &poly2);
    polyPrint(poly3);
}
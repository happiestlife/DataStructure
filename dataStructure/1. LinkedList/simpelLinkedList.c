#include<stdio.h>
typedef struct ListNode {
    struct ListNode* link;
    int data;
}ListNode;
/*
int isEmpty(ListNode* head);
ListNode* createNode(int data, ListNode* link);
void insertNode(ListNode* head, ListNode* link, ListNode* node);
void deleteNode();
void printList();
ListNode* search();
ListNode* reverse();
ListNode* concat();

int main() {
    ListNode* list1 = NULL, * list2 = NULL;
    ListNode* p;

    insertNode(&list1, NULL, createNode(1, NULL));
    insertNode(&list1, NULL, createNode(2, NULL));
    insertNode(&list1, NULL, createNode(3, NULL));
    printList(list1);

    deleteNode(&list1, 2);
    printList(list1);

    insertNode(&list2, NULL, createNode(4, NULL));
    insertNode(&list2, NULL, createNode(5, NULL));
    insertNode(&list2, NULL, createNode(6, NULL));
    printList(list2);

    list1 = concat(list1, list2);
    printList(list1);

    list1 = reverse(list1);
    printList(list1);

    p = search(list1, 3);
    if (p)
        printf("3 찾기 성공");
    else
        printf("검색 실패..");

    return 0;

}

ListNode* createNode(int data, ListNode* link) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (!newNode) {
        printf("node creation error\n");
        return;
    }
    newNode->data = data;
    newNode->link = link;
    return newNode;
}

int isEmpty(ListNode* head) {
    return head == NULL;
}

void insertNode(ListNode** head, ListNode* prevLink, ListNode* node) {
    if (*head == NULL) *head = node;
    else if (prevLink == NULL) {
        node->link = *head;
        *head = node;
    }
    else {
        node->link = prevLink->link;
        prevLink->link = node;
    }
}

void deleteNode(ListNode** head, int data) {
    ListNode* prevNode = *head;
    if (isEmpty(*head)) return;
    for (ListNode* i = *head; i != NULL; prevNode = i, i = i->link)
        if (i->data == data) {
            prevNode->link = i->link;
            free(i);
            break;
        }
}

void printList(ListNode* head) {
    while (1) {
        printf("%d", head->data);
        head = head->link;
        if (!head) break;
        printf(" -> ");
    }
    printf("\n");
}

ListNode* search(ListNode* head, int data) {
    while (head) {
        if (head->data == data) return head;
        head = head->link;
    }
    return NULL;
}

ListNode* reverse(ListNode* head) {
    ListNode* prevLink = NULL;
    ListNode* nextLink, * p = head;

    while (1) {
        nextLink = p->link;
        p->link = prevLink;
        if (nextLink == NULL) break;
        prevLink = p;
        p = nextLink;
    }
    return head;
}

ListNode* concat(ListNode* list1, ListNode* list2) {
    ListNode* point = NULL;
    for (point = list1; ; point = point->link)
        if (point->link == NULL) break;

    point->link = list2;
    return list1;
}
*/

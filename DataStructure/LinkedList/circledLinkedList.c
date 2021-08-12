#include<stdio.h>
typedef struct ListNode {
    struct ListNode* link;
    int data;
}ListNode;
/*
int isEmpty();
ListNode* createNode();
void insertNode();
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

   // deleteNode(&list1, 1);
    printList(list1);

    insertNode(&list2, NULL, createNode(4, NULL));
    insertNode(&list2, NULL, createNode(5, NULL));
    insertNode(&list2, NULL, createNode(6, NULL));
    printList(list2);
    
    //list1 = concat(list1, list2);
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

void insertNode(ListNode** head, ListNode* prevNode, ListNode* node) {
    if (*head == NULL) { 
        *head = node; 
        node->link = *head;
    } else if(prevNode == NULL){                  // 첫번째 부분에 노드 삽입
        node->link = (*head)->link;
        (*head)->link = node;
    } else if (prevNode == head) {                // 마지막 부분에 노드 삽입
        node->link = (*head)->link;
        (*head)->link = node;
        head = node;
    } else {
        node->link = prevNode->link;
        prevNode->link = node;
    }
}

void deleteNode(ListNode** head, int data) {
    if (isEmpty(*head)) return;
    ListNode* prevNode = *head,* i = (*head)->link; // 삭제하는 노드가 마지막 노드일 경우를 대비해서 첫 노드부터 탐색을 시작한다.
    while (1) {
        if (i->data == data) {
            if (i == *head) {                     // 삭제하는 노드가 마지막 노드일 경우 해당노드 삭제 후 전 노드를 head로 바꾼다.
                prevNode->link = i->link;
                *head = prevNode;
            }
            else 
                prevNode->link = i->link;
            free(i);
            return;
        }
        prevNode = i;
        i = i->link;
        if (i == (*head)->link) break;
    }
    printf("<삭제> 해당 데이터는 존재하지 않습니다.\n");
}

void printList(ListNode* head) {
    ListNode* p = head->link;                   // head가 마지막 노드를 가르키기 때문에 head->link로 시작해서 첫 노드부터 시작하도록 한다.
    while (1) {
        printf("%d", p->data);
        p = p->link;
        if (p == head->link) break;
        printf(" -> ");
    }
    printf("\n");
}

ListNode* search(ListNode* head, int data) {
    ListNode* p = head;
    while (1) {
        if (p->data == data) return p;
        p = p->link;
        if (p == head) break;
    }
    return NULL;
}

ListNode* reverse(ListNode* head) {
    int i = 1;
    int headData = head->data;
    ListNode* prevLink = head;
    ListNode* nextLink, * p = head->link;
    while (1) {
        nextLink = p->link;
        p->link = prevLink;
        if (p->data == headData) break;
        prevLink = p;
        p = nextLink;
    }
    return nextLink;
    //printf("\n%d<head> %d<head->link> %d<head->link->link> ", head->data, head->link->data, head->link->link->data);
}

ListNode* concat(ListNode* list1, ListNode* list2) {
    ListNode* first = list1->link;
    list1->link = list2->link;
    list2->link = first;
    list1 = list2;                                  // list1뒤에 list2를 붙이기 때문에 list1뒤에 list2를 대입힌다.  (아니면 list2부터 시작)
    return list1;
}
*/
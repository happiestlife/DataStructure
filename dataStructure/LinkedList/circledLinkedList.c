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
        printf("3 ã�� ����");
    else
        printf("�˻� ����..");
    
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
    } else if(prevNode == NULL){                  // ù��° �κп� ��� ����
        node->link = (*head)->link;
        (*head)->link = node;
    } else if (prevNode == head) {                // ������ �κп� ��� ����
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
    ListNode* prevNode = *head,* i = (*head)->link; // �����ϴ� ��尡 ������ ����� ��츦 ����ؼ� ù ������ Ž���� �����Ѵ�.
    while (1) {
        if (i->data == data) {
            if (i == *head) {                     // �����ϴ� ��尡 ������ ����� ��� �ش��� ���� �� �� ��带 head�� �ٲ۴�.
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
    printf("<����> �ش� �����ʹ� �������� �ʽ��ϴ�.\n");
}

void printList(ListNode* head) {
    ListNode* p = head->link;                   // head�� ������ ��带 ����Ű�� ������ head->link�� �����ؼ� ù ������ �����ϵ��� �Ѵ�.
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
    list1 = list2;                                  // list1�ڿ� list2�� ���̱� ������ list1�ڿ� list2�� ��������.  (�ƴϸ� list2���� ����)
    return list1;
}
*/
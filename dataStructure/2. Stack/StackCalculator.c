#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define SIZE 4
typedef struct Equation {        // �� �׿� ���� ����
    int operand;
    char operation;
    struct Equation* link;
}Equation;
typedef struct {                // ���� ǥ������ ��ȯ�� ��
    struct Equation* first;
    struct Equation* last;
}EquationInfo;

typedef struct StackData {       // ���þ� �� ������
    char Soperation;
    struct StackData* llink;    // ���� �Ʒ����� �ǹ�
    struct StackData* rlink;    // ���� ������ �ǹ�
}StackData;
typedef struct StackInfo {      // ���� ����
    struct StackData* first;
    struct StackData* last;
}StackInfo;
void push(StackInfo* head, char operation) {
    StackData* newNode = (StackData*)malloc(sizeof(StackData));
    if (!newNode) {
        printf("error\n");
        return;
    }

    newNode->Soperation = operation;

    if (head == NULL) {
        head->first = head->last = newNode;
        newNode->rlink = newNode->llink = NULL;
    }
    else {
        head->last->rlink = newNode;
        newNode->llink = head->last;
        head->last = newNode;
        newNode->rlink = NULL;
    }
}
void pop(StackInfo* stackInfo) {
    if (stackInfo->first == NULL) {
        printf("no data\n");
        return;
    }
    StackData* tmp = stackInfo->last;
    stackInfo->last = tmp->llink;
    free(tmp);
}

void init(EquationInfo* head) {
    head->first = head->last = NULL;
}
Equation* transfer(char* string) {
    int num = 0;
    int lastOperationIndex = 0;
    Equation* newNode = NULL;
    EquationInfo* head = (EquationInfo*)malloc(sizeof(EquationInfo));      // ����ǥ����
    head->first = head->last = NULL;
    if (!head) {
        printf("error");
        return;
    }
    StackData* newStackNode = NULL;
    StackInfo* stackHead = (StackInfo*)malloc(sizeof(StackInfo));          // ����ǥ������ ����� ���� ����
    if (!stackHead) {
        printf("error");
        return;
    }
    stackHead->first = stackHead->last = NULL;

    for (int i = 0; i < strlen(string); i++) {
        char c = string[i];
        if (c == '+' || c == '-' || c == '*' || c == '/') {               // ex. a*b+c a�� *�� ���� ���� �ܼ� ���Ḯ��Ʈ�� ����
            newNode = (Equation*)malloc(sizeof(Equation));              // a�κ�           
            if (!newNode) {
                printf("error");
                return;
            }

            for (int j = lastOperationIndex; j < i; j++)                 // a�� 10�̻��� ��� ������
                num = num * 10 + string[j] - '0';
            newNode->operand = num;
            newNode->operation = 0;

            newNode->link = NULL;
            if (head->first == NULL) {
                head->first = newNode;
                head->last = newNode;
            }
            else {
                head->last->link = newNode;
                head->last = newNode;
            }

            newNode = (Equation*)malloc(sizeof(Equation));              // *�κ�          
            if (!newNode) {
                printf("error");
                return;
            }

            newNode->operand = 0;
            newNode->operation = string[i];
            head->last->link = newNode;
            head->last = newNode;

            num = 0;
            lastOperationIndex = i + 1;
        }
    }
    for (int i = lastOperationIndex; i < strlen(string); i++)            // a, *, b, +���� ���� ����� c�� ���⿡ ���� ����� �������ش�.
        num = num * 10 + string[i] - '0';

    newNode = (Equation*)malloc(sizeof(Equation));
    if (!newNode) {
        printf("error");
        return;
    }
    newNode->operand = num;
    newNode->operation = 0;

    newNode->link = NULL;
    head->last->link = newNode;
    head->last = newNode;

    return head;
}
int calculate(Equation* expression) {

}
int main() {
    char* string[] = { "10*20+30", "10+20*30", "(10+20)*30", "((10+20)*(30+40))" };
    EquationInfo* equationStack[SIZE];
    int result[SIZE];
    for (int i = 0; i < SIZE; i++) {
        equationStack[i] = (EquationInfo*)malloc(sizeof(EquationInfo));
        init(equationStack[i]);
        equationStack[i] = transfer(string[i]);                         // ���� ǥ���� -> ���� ǥ����
    }
    for (int i = 0; i < 4; i++) {
        for (Equation* j = equationStack[i]->first; j; j = j->link) {
            if (j->operation == 0) printf("%d ", j->operand);
            else printf("%c ", j->operation);
        }
        printf("\n");
    }


    for (int i = 0; i < SIZE; i++)
        //printf("%d : %d\n",i+1, calculate(equationStack[i]));

        return 0;
}
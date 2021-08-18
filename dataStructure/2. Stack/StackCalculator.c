#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define SIZE 4
typedef struct Equation {        // 각 항에 대한 정보
    int operand;
    char operation;
    struct Equation* link;
}Equation;
typedef struct {                // 후위 표현으로 변환한 식
    struct Equation* first;
    struct Equation* last;
}EquationInfo;

typedef struct StackData {       // 스택안 각 데이터
    char Soperation;
    struct StackData* llink;    // 가장 아랫단을 의미
    struct StackData* rlink;    // 가장 윗단을 의미
}StackData;
typedef struct StackInfo {      // 스택 정보
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
    EquationInfo* head = (EquationInfo*)malloc(sizeof(EquationInfo));      // 후위표현식
    head->first = head->last = NULL;
    if (!head) {
        printf("error");
        return;
    }
    StackData* newStackNode = NULL;
    StackInfo* stackHead = (StackInfo*)malloc(sizeof(StackInfo));          // 후위표현식을 만들기 위한 스택
    if (!stackHead) {
        printf("error");
        return;
    }
    stackHead->first = stackHead->last = NULL;

    for (int i = 0; i < strlen(string); i++) {
        char c = string[i];
        if (c == '+' || c == '-' || c == '*' || c == '/') {               // ex. a*b+c a와 *를 노드로 만들어서 단순 연결리스트로 연결
            newNode = (Equation*)malloc(sizeof(Equation));              // a부분           
            if (!newNode) {
                printf("error");
                return;
            }

            for (int j = lastOperationIndex; j < i; j++)                 // a가 10이상일 경우 적용방법
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

            newNode = (Equation*)malloc(sizeof(Equation));              // *부분          
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
    for (int i = lastOperationIndex; i < strlen(string); i++)            // a, *, b, +까지 노드로 만들면 c가 남기에 노드로 만들어 연결해준다.
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
        equationStack[i] = transfer(string[i]);                         // 중위 표현식 -> 후위 표현식
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
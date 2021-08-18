#include"MakePostfix.h"

void init(EquationInfo* head) {
    head->first = head->last = NULL;
}

void equationInsert(EquationInfo* head, Equation* newNode) {
    newNode->link = NULL;
    if (head->first == NULL) {
        head->first = newNode;
        head->last = newNode;
    }
    else {
        head->last->link = newNode;
        head->last = newNode;
    }
}

Equation* transfer(char* string) {
    int num = 0;
    Equation* newNode = NULL;
    EquationInfo* equationHead = (EquationInfo*)malloc(sizeof(EquationInfo));      // 후위표현식
    equationHead->first = equationHead->last = NULL;
    if (!equationHead) {
        printf("error");
        return;
    }
    StackInfo* stackHead = (StackInfo*)malloc(sizeof(StackInfo));          // 후위표현식을 만들기 위한 스택
    if (!stackHead) {
        printf("error");
        return;
    }
    stackHead->first = stackHead->last = NULL;

    for (int i = 0; i < strlen(string); i++) {
        char c = string[i];
        printf("c : %c, ", c);
        // ex. a*b+c a와 *를 노드로 만들어서 단순 연결리스트로 연결
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            // a부분
            printf("insert operand ");
            newNode = (Equation*)malloc(sizeof(Equation));
            if (!newNode) {
                printf("error");
                return;
            }
            newNode->operand = num;
            newNode->operator = 0;
            equationInsert(equationHead, newNode);

            // *부분 
            printf("insert operator, ");
            newNode = (Equation*)malloc(sizeof(Equation));
            if (!newNode) {
                printf("error");
                return;
            }
            newNode->operand = 0;
            switch (c) {
            case '+':
            case '-':
                printf("+,-\n");
                if (stackHead->first != NULL) {
                    newNode->operator = pop(stackHead);
                    push(stackHead, c);
                    break;
                }
                else {
                    push(stackHead, c);
                    free(newNode);
                    num = 0;
                    continue;
                }
            case '*':
            case '/':
                printf("*,/\n");
                if (peek(stackHead) == '+' || peek(stackHead) == '-') {
                    push(stackHead, c);
                    free(newNode);
                    num = 0;
                    continue;
                }
                else {
                    if (stackHead->first != NULL) newNode->operator = pop(stackHead->last);
                    push(stackHead, c);
                }
                break;
            }
            printf("operator inserted\n");
            equationInsert(equationHead, newNode);

            num = 0;
            for (Equation* j = equationHead->first; j; j = j->link) {
                if (j->operator == 0) printf("%d ", j->operand);
                else printf("%c ", j->operator);
            }
            printf("\n");
        }
        else if (c == '(') {
            push(stackHead, c);
        }
        else if (c == ')') {
            while (1) {
                char tmpOperator = pop(stackHead);
                if (tmpOperator == '(')
                    continue;
                else if (tmpOperator == ')')
                    break;
                newNode = (Equation*)malloc(sizeof(Equation));              // *부분          
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = 0;
                newNode->operator = tmpOperator;

                equationInsert(equationHead, newNode);
            }
        }
        else {
            num = num * 10 + string[i] - '0';
        }
        printf("stack : ");
        for (StackData* i = stackHead->first; i; i = i->rlink) {
            printf("%c ", i->Soperation);
        }
        printf("\n");
    }
    newNode = (Equation*)malloc(sizeof(Equation));
    if (!newNode) {
        printf("error");
        return;
    }
    newNode->operand = num;
    newNode->operator = 0;

    equationInsert(equationHead, newNode);

    while (isStackEmpty(stackHead)) {
        newNode = (Equation*)malloc(sizeof(Equation));
        if (!newNode) {
            printf("error");
            return;
        }
        newNode->operand = 0;
        newNode->operator = pop(stackHead);

        equationInsert(equationHead, newNode);
    }

    return equationHead;
}
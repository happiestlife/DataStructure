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
    char beforeChar = 0;
    char lastOperation;
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

    char c;
    for (int i = 0; i < strlen(string); beforeChar = c, i++) {
        c = string[i];
        // ex. a*b+c a와 *를 노드로 만들어서 단순 연결리스트로 연결
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            // a부분
            if (beforeChar != ')') {
                newNode = (Equation*)malloc(sizeof(Equation));
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = num;
                newNode->operator = 0;

                equationInsert(equationHead, newNode);
            }

            // *부분 
            newNode = (Equation*)malloc(sizeof(Equation));
            if (!newNode) {
                printf("error");
                return;
            }
            newNode->operand = 0;
            switch (c) {
            case '+':
            case '-':
                if (stackHead->first == NULL) {
                    push(stackHead, c);
                    free(newNode);
                    num = 0;
                    continue;
                }
                else {
                    lastOperation = peek(stackHead);
                    if(lastOperation == '(') {
                        push(stackHead, c);
                        free(newNode);
                        num = 0;
                        continue;
                    } else {
                        newNode->operator = pop(stackHead);
                        push(stackHead, c);
                        break;
                    }
                }
            case '*':
            case '/':
                if (stackHead->first == NULL) {
                    push(stackHead, c);
                    free(newNode);
                    num = 0;
                    continue;
                }else {
                    lastOperation = peek(stackHead);
                    if (lastOperation == '+' || lastOperation == '-' || lastOperation == '(') {
                        push(stackHead, c);
                        free(newNode);
                        num = 0;
                        continue;
                    }else {
                        newNode->operator = pop(stackHead->last);
                        push(stackHead, c);
                    }
                }
                break;
            }
            equationInsert(equationHead, newNode);

            num = 0;
        }
        else if (c == '(') {
            push(stackHead, c);
        }
        else if (c == ')') {
            if (num != 0) {
                newNode = (Equation*)malloc(sizeof(Equation));
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = num;
                newNode->operator = 0;

                equationInsert(equationHead, newNode);
            }

            while (1) {
                char tmpOperator = pop(stackHead);
                if (tmpOperator == '(')
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
            num = 0;
        }
        else {
            num = num * 10 + string[i] - '0';
        }
    }

    if (num != 0) {
        newNode = (Equation*)malloc(sizeof(Equation));
        if (!newNode) {
            printf("error");
            return;
        }
        newNode->operand = num;
        newNode->operator = 0;

        equationInsert(equationHead, newNode);
    }

    while (!isStackEmpty(stackHead)) {
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
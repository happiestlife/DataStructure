#include"MakePostfix.h"

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
    int num = 0;                                                                   // 피연산자가 10이상일 경우 삽입을 위한 변수
    char beforeChar = 0;                                                           // 직전의 문자로 피연산자를 넣을지 말지 결정하는 제어변수
    char lastOperation;                                                            // 가장 최근에 후위표현식을 만들기 위한 스택에 들어간 연산자에 대한 변수

    Equation* newNode = NULL;
    EquationInfo* equationHead = (EquationInfo*)malloc(sizeof(EquationInfo));      // 후위표현식 (단순 연결리스트로 스택형태 구현)
    equationHead->first = equationHead->last = NULL;
    if (!equationHead) {
        printf("error");
        return;
    }
    StackInfo* stackHead = (StackInfo*)malloc(sizeof(StackInfo));                   // 후위표현식을 만들기 위한 스택(이하 스택)
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
            if (beforeChar != ')') {                                                // 만약 직전의 문자가 ')'일 경우, 그다음으로는 반드시 연산자 혹은 ')'가 오기 때문에  
                newNode = (Equation*)malloc(sizeof(Equation));                      // 피연산자를 후위표현식에 넣지 않는다.
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = num;
                newNode->operator = 0;                                              // 나중에 계산 및 출력에서 후위표현식의 각 노드가 피연산자인지 연산자인지 구분하기 위한 용도
                                                                                    // operator == 0 -> 피연산자, operator =! = -> 연산자
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
                if (stackHead->first == NULL) {                                     // 만약 스택이 비었다면 '+/-' push
                    push(stackHead, c);
                    free(newNode);
                    num = 0;                                                        // 연산자 전의 피연산자를 후위표현식에 넣었기 때문에 0으로 초기화
                    continue;
                }
                else {
                    lastOperation = peek(stackHead);
                    if(lastOperation == '(') {                                      // 만약 스택의 가장 위 데이터가 '('이면 
                        push(stackHead, c);                                         // 후위표현식에 넣을 필요 없기 때문에 현재 연산자 push
                        free(newNode);
                        num = 0;
                        continue;
                    } else {                                                        // 모든 연산자는 '+/-'보다 연산자 우선순위가 같거나 크기때문에         
                        newNode->operator = pop(stackHead);                         // 스택에서 값을 pop하여 후위표현식에 삽입 후 현재 연산자 push
                        push(stackHead, c);
                        break;
                    }
                }
            case '*':
            case '/':
                if (stackHead->first == NULL) {                                     // 만약 스택이 비었다면 '* / /(나누기)' push
                    push(stackHead, c);
                    free(newNode);
                    num = 0;
                    continue;
                }else {
                    lastOperation = peek(stackHead);                                
                    if (lastOperation == '+' || lastOperation == '-' || lastOperation == '(') {     // 스택 가장 위의 값이 '('경우 pop할 필요가 없기때문에 push
                        push(stackHead, c);                                         // '* / /'은 '+/-'보다 연산자 우선순위가 높기때문에 push
                        free(newNode);
                        num = 0;
                        continue;
                    }else {                                                         // '* / /'은 현재 연산자와 같기때문에 스택에서 값을 pop하여 후위표현식에 삽입 후 현재 연산자 push
                        newNode->operator = pop(stackHead->last);
                        push(stackHead, c);
                    }
                }
                break;
            }
            equationInsert(equationHead, newNode);

            num = 0;
        }
        else if (c == '(') {                                                        // '('인 경우, 스택에 push, 나중에 ')'이 나올경우 해당 문자가 나오기 전까지 스택 값 pop을 위한 용도
            push(stackHead, c);
        }
        else if (c == ')') {
            if (num != 0) {                                                         // 그전의 값이 ')'인 경우 데이터 삽입 x   ex) ((1+2))
                newNode = (Equation*)malloc(sizeof(Equation));
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = num;
                newNode->operator = 0;

                equationInsert(equationHead, newNode);
            }

            while (1) {                                                             // '('문자가 나오기 전까지 스택 값 pop후 후위 표현식에 저장      
                char tmpOperator = pop(stackHead);
                if (tmpOperator == '(')
                    break;
                newNode = (Equation*)malloc(sizeof(Equation));                    
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
        else {                                                                      // 연산자가 나오기 전까지 피연산자 제작
            num = num * 10 + string[i] - '0';
        }
    }

    if (num != 0) {                                                                 // 피연산자가 홀수개 일 경우, 마지막 피연산자를 후위표현식에 삽입
        newNode = (Equation*)malloc(sizeof(Equation));                              // ex) 1+2+3
        if (!newNode) {
            printf("error");
            return;
        }
        newNode->operand = num;
        newNode->operator = 0;

        equationInsert(equationHead, newNode);
    }

    while (!isStackEmpty(stackHead)) {                                               // 스택에 저장되어 있던 모든 연산자 후위표현식에 삽입
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
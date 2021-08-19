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
    int num = 0;                                                                   // �ǿ����ڰ� 10�̻��� ��� ������ ���� ����
    char beforeChar = 0;                                                           // ������ ���ڷ� �ǿ����ڸ� ������ ���� �����ϴ� �����
    char lastOperation;                                                            // ���� �ֱٿ� ����ǥ������ ����� ���� ���ÿ� �� �����ڿ� ���� ����

    Equation* newNode = NULL;
    EquationInfo* equationHead = (EquationInfo*)malloc(sizeof(EquationInfo));      // ����ǥ���� (�ܼ� ���Ḯ��Ʈ�� �������� ����)
    equationHead->first = equationHead->last = NULL;
    if (!equationHead) {
        printf("error");
        return;
    }
    StackInfo* stackHead = (StackInfo*)malloc(sizeof(StackInfo));                   // ����ǥ������ ����� ���� ����(���� ����)
    if (!stackHead) {
        printf("error");
        return;
    }
    stackHead->first = stackHead->last = NULL;

    char c;
    for (int i = 0; i < strlen(string); beforeChar = c, i++) {
        c = string[i];
        // ex. a*b+c a�� *�� ���� ���� �ܼ� ���Ḯ��Ʈ�� ����
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            // a�κ�
            if (beforeChar != ')') {                                                // ���� ������ ���ڰ� ')'�� ���, �״������δ� �ݵ�� ������ Ȥ�� ')'�� ���� ������  
                newNode = (Equation*)malloc(sizeof(Equation));                      // �ǿ����ڸ� ����ǥ���Ŀ� ���� �ʴ´�.
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = num;
                newNode->operator = 0;                                              // ���߿� ��� �� ��¿��� ����ǥ������ �� ��尡 �ǿ��������� ���������� �����ϱ� ���� �뵵
                                                                                    // operator == 0 -> �ǿ�����, operator =! = -> ������
                equationInsert(equationHead, newNode);
            }

            // *�κ� 
            newNode = (Equation*)malloc(sizeof(Equation));
            if (!newNode) {
                printf("error");
                return;
            }
            newNode->operand = 0;
            switch (c) {
            case '+':
            case '-':
                if (stackHead->first == NULL) {                                     // ���� ������ ����ٸ� '+/-' push
                    push(stackHead, c);
                    free(newNode);
                    num = 0;                                                        // ������ ���� �ǿ����ڸ� ����ǥ���Ŀ� �־��� ������ 0���� �ʱ�ȭ
                    continue;
                }
                else {
                    lastOperation = peek(stackHead);
                    if(lastOperation == '(') {                                      // ���� ������ ���� �� �����Ͱ� '('�̸� 
                        push(stackHead, c);                                         // ����ǥ���Ŀ� ���� �ʿ� ���� ������ ���� ������ push
                        free(newNode);
                        num = 0;
                        continue;
                    } else {                                                        // ��� �����ڴ� '+/-'���� ������ �켱������ ���ų� ũ�⶧����         
                        newNode->operator = pop(stackHead);                         // ���ÿ��� ���� pop�Ͽ� ����ǥ���Ŀ� ���� �� ���� ������ push
                        push(stackHead, c);
                        break;
                    }
                }
            case '*':
            case '/':
                if (stackHead->first == NULL) {                                     // ���� ������ ����ٸ� '* / /(������)' push
                    push(stackHead, c);
                    free(newNode);
                    num = 0;
                    continue;
                }else {
                    lastOperation = peek(stackHead);                                
                    if (lastOperation == '+' || lastOperation == '-' || lastOperation == '(') {     // ���� ���� ���� ���� '('��� pop�� �ʿ䰡 ���⶧���� push
                        push(stackHead, c);                                         // '* / /'�� '+/-'���� ������ �켱������ ���⶧���� push
                        free(newNode);
                        num = 0;
                        continue;
                    }else {                                                         // '* / /'�� ���� �����ڿ� ���⶧���� ���ÿ��� ���� pop�Ͽ� ����ǥ���Ŀ� ���� �� ���� ������ push
                        newNode->operator = pop(stackHead->last);
                        push(stackHead, c);
                    }
                }
                break;
            }
            equationInsert(equationHead, newNode);

            num = 0;
        }
        else if (c == '(') {                                                        // '('�� ���, ���ÿ� push, ���߿� ')'�� ���ð�� �ش� ���ڰ� ������ ������ ���� �� pop�� ���� �뵵
            push(stackHead, c);
        }
        else if (c == ')') {
            if (num != 0) {                                                         // ������ ���� ')'�� ��� ������ ���� x   ex) ((1+2))
                newNode = (Equation*)malloc(sizeof(Equation));
                if (!newNode) {
                    printf("error");
                    return;
                }
                newNode->operand = num;
                newNode->operator = 0;

                equationInsert(equationHead, newNode);
            }

            while (1) {                                                             // '('���ڰ� ������ ������ ���� �� pop�� ���� ǥ���Ŀ� ����      
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
        else {                                                                      // �����ڰ� ������ ������ �ǿ����� ����
            num = num * 10 + string[i] - '0';
        }
    }

    if (num != 0) {                                                                 // �ǿ����ڰ� Ȧ���� �� ���, ������ �ǿ����ڸ� ����ǥ���Ŀ� ����
        newNode = (Equation*)malloc(sizeof(Equation));                              // ex) 1+2+3
        if (!newNode) {
            printf("error");
            return;
        }
        newNode->operand = num;
        newNode->operator = 0;

        equationInsert(equationHead, newNode);
    }

    while (!isStackEmpty(stackHead)) {                                               // ���ÿ� ����Ǿ� �ִ� ��� ������ ����ǥ���Ŀ� ����
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
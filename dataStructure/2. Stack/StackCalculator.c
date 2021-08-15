#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define SIZE 4
typedef struct Equation{
    char* data;
    struct Equation* link;
}Equation;
typedef struct info{
    struct Equation* first;
    struct Equation* last;
}EquationInfo;

void init(EquationInfo* head){
    head->first = head->last = NULL;
}
Equation* transfer(char* string){
    int num = 0;
    int lastOperationIndex = 0;
    Equation* newNode = NULL;
    EquationInfo* head = (EquationInfo*)malloc(sizeof(EquationInfo));
    head->first = head->last = NULL;
    if(!head){
        printf("error");
        return;
    }
    for(int i = 0; i < strlen(string); i++){
        char c = string[i];
        if(c == '+' || c == '-' || c == '*' || c == '/'){               // ex. a*b+c a�� *�� ���� ���� �ܼ� ���Ḯ��Ʈ�� ����
            newNode = (Equation*)malloc(sizeof(Equation));              // a�κ�           
            if(!newNode){
                printf("error");
                return;
            }
            for(int j = lastOperationIndex; j < i; j++)                 // a�� 10�̻��� ��� ������
                num = num*10 + string[j]-'0';
            newNode->data = (char*)malloc(sizeof(char)*5);
            itoa(num, newNode->data, 10);
            newNode->link = NULL;

            if(head->first == NULL){ 
                head->first = newNode;
                head->last = newNode;
            } else{
                head->last->link = newNode;
                head->last = newNode;
            }
           
            newNode = (Equation*)malloc(sizeof(Equation));              // *�κ�          
            if(!newNode){
                printf("error");
                return;
            }
            newNode->data = string[i];
            head->last->link = newNode;
            head->last = newNode;
            num = 0;
            lastOperationIndex = i+1;
        }
    }
    for(int i = lastOperationIndex; i < strlen(string); i++){           // a, *, b, +���� ���� ����� c�� ���⿡ ���� ����� �������ش�.
        newNode = (Equation*)malloc(sizeof(Equation));
        if(!newNode){
            printf("error");
            return;
        }
        for(int j = lastOperationIndex; j < i; j++)
            num = num*10 + string[j];
        newNode->data = (char*)malloc(sizeof(char) * 5);
        itoa(num, newNode->data, 10);
        newNode->link = NULL;

        head->last->link = newNode;
        head->last = newNode;
    }
    return head;
}
int calculate(Equation* expression){

}
int main() {
    char* string[] = {"10*20+30", "10+20*30", "(10+20)*30", "((10+20)*(30+40))"};
    EquationInfo* equationStack[SIZE];
    int result[SIZE];
    for(int i = 0; i < SIZE; i++){
        equationStack[i] = (EquationInfo*)malloc(sizeof(EquationInfo));
        init(equationStack[i]);
        equationStack[i] = transfer(string[i]);                         // ���� ǥ���� -> ���� ǥ����
    }

    for(Equation* i = equationStack[0]->first; i; i = i->link)
        printf("%s�� ", i->data);

    for(int i = 0; i < SIZE; i++)
        //printf("%d : %d\n",i+1, calculate(equationStack[i]));

    return 0;
}
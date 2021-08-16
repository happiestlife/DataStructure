#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define SIZE 4
typedef struct Equation{
    int operand;
    char operation;
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
        if(c == '+' || c == '-' || c == '*' || c == '/'){               // ex. a*b+c a와 *를 노드로 만들어서 단순 연결리스트로 연결
            newNode = (Equation*)malloc(sizeof(Equation));              // a부분           
            if(!newNode){
                printf("error");
                return;
            }

            for(int j = lastOperationIndex; j < i; j++)                 // a가 10이상일 경우 적용방법
                num = num*10 + string[j]-'0';
            newNode->operand = num;
            newNode->operation = 0;

            newNode->link = NULL;
            if(head->first == NULL){ 
                head->first = newNode;
                head->last = newNode;
            } else{
                head->last->link = newNode;
                head->last = newNode;
            }

            newNode = (Equation*)malloc(sizeof(Equation));              // *부분          
            if(!newNode){
                printf("error");
                return;
            }

            newNode->operand = 0;
            newNode->operation = string[i];
            head->last->link = newNode;
            head->last = newNode;

            num = 0;
            lastOperationIndex = i+1;
        }
    }
    for(int i = lastOperationIndex; i < strlen(string); i++){           // a, *, b, +까지 노드로 만들면 c가 남기에 노드로 만들어 연결해준다.
        newNode = (Equation*)malloc(sizeof(Equation));
        if(!newNode){
            printf("error");
            return;
        }
        for(int j = lastOperationIndex; j < i; j++)
            num = num*10 + string[j] - '0';
        newNode->operand = num;
        newNode->operation = 0;

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
        equationStack[i] = transfer(string[i]);                         // 중위 표현식 -> 후위 표현식
    }

    for (Equation* i = equationStack[0]->first; i; i = i->link) {
        if (i->operation == 0) printf("%d ", i->operand);
        else printf("%c ", i->operation);
    }
        

    for(int i = 0; i < SIZE; i++)
        //printf("%d : %d\n",i+1, calculate(equationStack[i]));

    return 0;
}
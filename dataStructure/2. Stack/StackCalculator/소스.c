#include"DataStructure.h"
#include"Stack.h"
#include"MakePostfix.h"
int calculate(Equation* expression){

}
int main() {
    char* string[] = {"10*20+30", "10+20*30", "(10+20)*30", "((10+20)*(30+40))"};
    EquationInfo* equations[SIZE];
    int result[SIZE];
    for(int i = 0; i < SIZE; i++){
        equations[i] = (EquationInfo*)malloc(sizeof(EquationInfo));
        init(equations[i]);
        equations[i] = transfer(string[i]);                         // 중위 표현식 -> 후위 표현식
    }
    for (int i = 0; i < 4; i++) {
        for (Equation* j = equations[i]->first; j; j = j->link) {
            if (j->operator == 0) printf("%d ", j->operand);
            else printf("%c ", j->operator);
        }
        printf("\n");
    }
        

    for(int i = 0; i < SIZE; i++)
        //printf("%d : %d\n",i+1, calculate(equationStack[i]));
    return 0;
}
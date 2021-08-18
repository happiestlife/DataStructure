#pragma once
#include<stdio.h>
#pragma warning(disable:4996)
#define SIZE 4

typedef struct StackData {       // 스택안 각 데이터
    char Soperation;
    struct StackData* llink;    // 가장 아랫단을 의미
    struct StackData* rlink;    // 가장 윗단을 의미
}StackData;
typedef struct StackInfo {      // 스택 정보
    struct StackData* first;
    struct StackData* last;
}StackInfo;

typedef struct Equation {        // 각 항에 대한 정보
    int operand;
    char operator;
    struct Equation* link;
}Equation;
typedef struct {                // 후위 표현으로 변환한 식
    struct Equation* first;
    struct Equation* last;
}EquationInfo;
#pragma once
#include<stdio.h>
#pragma warning(disable:4996)
#define SIZE 4

// 스택 정보
typedef struct StackInfo {
    struct StackData* first;
    struct StackData* last;
}StackInfo;
// 스택안 각 데이터
typedef struct StackData {       
    char Soperation;
    struct StackData* llink;    // 가장 아랫단을 의미
    struct StackData* rlink;    // 가장 윗단을 의미
}StackData;

// 후위 표현으로 변환한 식
typedef struct {
    struct Equation* first;     // 후위 표현식 출력을 위한 용도
    struct Equation* last;      // 데이터 입력/삭제를 위한 용도
}EquationInfo;
// 후위 표현식 각 항에 대한 정보
typedef struct Equation {        
    int operand;
    char operator;
    struct Equation* link;
}Equation;
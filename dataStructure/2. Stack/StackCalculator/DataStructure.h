#pragma once
#include<stdio.h>
#pragma warning(disable:4996)
#define SIZE 4

// ���� ����
typedef struct StackInfo {
    struct StackData* first;
    struct StackData* last;
}StackInfo;
// ���þ� �� ������
typedef struct StackData {       
    char Soperation;
    struct StackData* llink;    // ���� �Ʒ����� �ǹ�
    struct StackData* rlink;    // ���� ������ �ǹ�
}StackData;

// ���� ǥ������ ��ȯ�� ��
typedef struct {
    struct Equation* first;     // ���� ǥ���� ����� ���� �뵵
    struct Equation* last;      // ������ �Է�/������ ���� �뵵
}EquationInfo;
// ���� ǥ���� �� �׿� ���� ����
typedef struct Equation {        
    int operand;
    char operator;
    struct Equation* link;
}Equation;
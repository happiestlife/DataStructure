#pragma once
#include<stdio.h>
#pragma warning(disable:4996)
#define SIZE 4

typedef struct StackData {       // ���þ� �� ������
    char Soperation;
    struct StackData* llink;    // ���� �Ʒ����� �ǹ�
    struct StackData* rlink;    // ���� ������ �ǹ�
}StackData;
typedef struct StackInfo {      // ���� ����
    struct StackData* first;
    struct StackData* last;
}StackInfo;

typedef struct Equation {        // �� �׿� ���� ����
    int operand;
    char operator;
    struct Equation* link;
}Equation;
typedef struct {                // ���� ǥ������ ��ȯ�� ��
    struct Equation* first;
    struct Equation* last;
}EquationInfo;
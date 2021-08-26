#include<stdio.h>
#include<stdlib.h>
#include"Traversal.h"
Tree* createNode(int data){
    Tree* newNode = (Tree*)malloc(sizeof(Tree));
    if(!newNode){
        printf("error\n");
        return;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Tree* insert(Tree* root, int data){
    if (root == NULL)
        return createNode(data);

    if(root->data == data){
        printf("Data is already in tree\n");
        return;
    }
    else if (root->data > data)  root->left = insert(root->left, data);
    else root->right = insert(root->right, data);

    return root;
}

void search(Tree* root, int data){
    if (root == NULL) {
        printf("There is no data\n");
        return;
    }
    if (data == root->data) printf("Data(%d) is in the Tree\n", data);
    else if (data < root->data) search(root->left, data);
    else search(root->right, data);
}

void delete(Tree* root, Tree* parent, int data) {
    if (root->data == data) {
        // �ܸ������ ���
        if (root->left == NULL && root->right == NULL) {
            if (parent->data > root->data)
                parent->left = NULL;
            else
                parent->right = NULL;
            free(root);
            return;
        }
        // ���� �ڽĳ�尡 ����ִ� ���
        else if (root->left == NULL) {
            if (parent == NULL) root = root->right;
            else {
                int newData = root->right->data;
                free(root->right);  free(root);
                printf("inserting ");
                insert(parent, newData);
                printf("end\n");
            }
            printf("R(%d %d)  %x %x \n", parent->data, parent->right->data, parent->right->left, parent->right->right);
            return;
        } else if (root->right == NULL) {
            if (parent == NULL) root = root->left;
            else {
                int newData = root->left->data;
                free(root->left);  free(root);
                printf("inserting ");
                insert(parent, newData);
                printf("end\n");
            }
            printf("L(%d %d)  %x %x \n", parent->data, parent->left->data, parent->left->left, parent->left->right);
            return;
        }
        // �ڽĳ�尡 2���� ���
        else {
            Tree* p_leftTree= root;
            Tree* leftTree = root->left;
            while (leftTree->right != NULL) {
                p_leftTree = leftTree;
                leftTree = leftTree->right;
            }
            Tree* p_rightTree = root;
            Tree* rightTree = root->right;
            while (leftTree->left != NULL) {
                p_rightTree = rightTree;
                leftTree = leftTree->left;
            }
            if (root - (leftTree->data) > abs((root - (rightTree->data)))) {
                root->data = leftTree->data;
                free(leftTree);
                p_leftTree->right = NULL;
            }else {
                root->data = rightTree->data;
                free(rightTree);
                p_rightTree->left = NULL;
            }
        }
    }
    else if (root->data > data) {
        delete(root->left, root, data);
    }
    else
        delete(root->right, root, data);
}

int main(){
    Tree* root = NULL;
    int arr[7] = {18, 7, 26, 3, 31, 12, 27};
    for (int i = 0; i < 7; i++) 
        root = insert(root, arr[i]);

    preOrder(root);

    printf("is there 27??\n");
    search(root, 27);

    delete(root, NULL, 31);
    preOrder(root);
}
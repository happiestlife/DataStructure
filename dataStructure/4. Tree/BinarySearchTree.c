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
    if (root == NULL) {
        printf("there is no data\n");
        return;
    }
    if (root->data == data) {
        if (root->left == NULL && root->right == NULL) {
            if (parent->data > root->data)
                parent->left = NULL;
            else
                parent->right = NULL;
            free(root);
            return;
        }
        else if (root->left == NULL) {
            if (parent == NULL) root = root->right;
            else {
                if (parent->left == root)
                    parent->left = root->right;
                else
                    parent->right = root->right;
                free(root);
            }
            return;
        } else if (root->right == NULL) {
            if (parent == NULL) root = root->left;
            else {
                if (parent->left == root)
                    parent->left = root->left;
                else
                    parent->right = root->left;
                free(root);
            }
            return;
        }
        else {
            Tree* leftNode, * rightNode;
            leftNode = root->left;
            while (leftNode->right != NULL) {
                leftNode = leftNode->right;
            }
            rightNode = root->right;
            while (rightNode->right != NULL) {
                rightNode = rightNode->left;
            }
            Tree* result = (root->data - leftNode->data) >= (rightNode->data - root->data) ? rightNode : leftNode;
            root->data = result->data;
            if (result == root->left)
                root->left = result->left;
            else
                root->right = result->right;
            free(result);
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

    delete(root, NULL, 7);
    preOrder(root);
}
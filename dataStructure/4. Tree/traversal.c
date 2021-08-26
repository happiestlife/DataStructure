#include"Traversal.h"
#include<stdio.h>
void preOrder(Tree* root){
    if(root == NULL) return;
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Tree* root){
    if(root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

void postOrder(Tree* root){
    if(root == NULL) return;
    postOrder(root->left);
    postOrder(root->right); 
    printf("%d ", root->data); 
}
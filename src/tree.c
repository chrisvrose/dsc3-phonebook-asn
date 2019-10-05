#ifndef _TREE_H
#include<tree.h>
#endif

#ifndef _STRING_H
#include<string.h>
#endif

#ifndef _STDLIB_H
#include<stdlib.h>
#endif

#define MAX(a,b) ((a)>(b)?(a):(b))

///A getter
int getHeight(treeNode* treenode){
    if(treenode==NULL){
        return 0;
    }else{
        return treenode->height;
    }
}

int getBalance(treeNode* root){
    if(root==NULL){
        return 0;
    }else{
        return getHeight(root->left)-getHeight(root->right);
    }
}


treeNode* getNewTreeNode(char* name,char* number){
    treeNode* newNode;
    if((newNode = malloc(sizeof(treeNode)))){
        newNode->left=newNode->right=NULL;
        newNode->height=1;
        strcpy(newNode->name,name);
        newNode->dataHead = insertEnd(NULL,number,NULL);
    }
    return newNode;
}

///Standard BST implementation
///Return searched element, null if not found
treeNode* treeSearch(treeNode* treenode,char* searchElement){
    if(treenode==NULL){
        return NULL;
    }
    int results = strcmp(treenode->name,searchElement);
    ///Was it that?
    if(!results){
        return treenode;
    }else if(results>0){
        return treeSearch(treenode->left,searchElement);
    }else{
        return treeSearch(treenode->right,searchElement);
    }
}




treeNode* leftRotate(treeNode* b){
    treeNode* a = b->left;
    treeNode * treeToChange = a->right;

    ///Make the rotation
    a->right = b;
    b->left = treeToChange;

    ///Recalc heights
    b->height = max(height(b->left),height(b->right))+1;
    a->height = max(height(a->left),height(a->right))+1;

    ///a becomes the new root
    return a;
}

treeNode* rightRotate(treeNode* b){
    treeNode* a = b->right;
    treeNode* treeToChange = a->left;

    ///Make rotations
    a->left = b;
    b->right = treeToChange;

    ///Recalc heights
    a->height = max(height(a->left),height(a->right))+1;
    b->height = max(height(b->left),height(b->right))+1;

    return a;
}




/* treeNode* insert(treeNode* root,char* name,char* number){
    
} */


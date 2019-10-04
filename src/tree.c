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

treeNode* getNewTreeNode(char* name,char* number){
    treeNode* newNode;
    if((newNode = malloc(sizeof(treeNode)))){
        newNode->left=newNode->right=NULL;
        newNode->height=0;
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


treeNode* insert(treeNode* root,char* name,char* number){

}


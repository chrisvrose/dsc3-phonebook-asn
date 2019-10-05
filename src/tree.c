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


///Balance:
///>0: left heavy
///<0: right heavy
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



/*
    AVL insert:
    returns:
        for each: more inserts/
        on whole: 
*/
treeNode* insert(treeNode* root,char* name,char* number){
    ///Step 1: Perform the bog standard BST insertion
    if(root==NULL){
        //We found where to insert, do it
        return getNewTreeNode(name,number);
    }

    int getCmp = strcmp(name,root->name);
    if(getCmp<0){
        root->left = insert(root->left,name,number);
    }else if(getCmp>0){
        root->right = insert(root->right,name,number);
    }else{
        ///Equality, yikes!
        root->dataHead = insertEnd(root->dataHead,number,NULL);
    }

    ///Done with insertion, get balance factor
    int balance = getBalance(root);

    ///Now the tricky part
    ///2 variables - where the node was pushed wrt root, and the balance
    /// 4 outcomes

    ///heavy on left side and it got inserted below the left child
    if(balance>1 && strcmp(name,root->left->name)<0){
        return rightRotate(root);
    }

    ///Heavy on the right side, and insertion occured on the right
    if(balance<-1 && strcmp(name,root->right->name)>0){
        return leftRotate(root);
    }

    ///Heavy on the left side, got inserted onto the right of the left child
    if(balance>1 && strcmp(name,root->left->name)>0){
        ///Rotate left
        root->left = leftRotate(root->left);
        ///Rotate self rightways
        return rightRotate(root);
    }

    ///Heavy on right, and got inserted on the left
    if(balance<-1 && strcmp(name,root->right->name)<0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }


    ////for anything else
    return root;
}


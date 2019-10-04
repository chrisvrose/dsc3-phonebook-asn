#ifndef _STR_LIST_H
#include<strList.h>
#endif

#ifndef _STRING_H
#include<string.h>
#endif

#ifndef _STDLIB_H
#include<stdlib.h>
#endif

//#define NULL ((void*)0)

///obtain node and set vals
node* getNode(char* data){
    node* newNode;
    if((newNode = malloc(sizeof(node)))){
        newNode->number;
        newNode->next=NULL;
    }
    return newNode;
}

///Trash node (getting val is optional)
void freeNode(node* element,char* outVar){
    if(element!=NULL){
        if(outVar!=NULL){
            int i;
            for(i=0;outVar[i]!=0;i++){
                element->number[i]=outVar[i];
            }
            outVar[i]=0;
        }
        free(element);
    }
}

///Remove all
void removeAll(node* headNode){
    if(headNode!=NULL){
        removeAll(headNode->next);
        free(headNode);
    }
}


///Returns modified head of new list
node* insertEnd(node* root,char* number,int* outStatus){
    if(root!=NULL){
        node* newNode = getNode(number);
        if(newNode==NULL){
            if(outStatus!=NULL) *outStatus = 1;
            return root;
        }
        ///find last
        node* last;
        for(last=root;last->next!=NULL;last=last->next);
        //Insert at last
        last->next=newNode;
        if(outStatus!=NULL) *outStatus=0;
        return root;
    }else{
        return getNode(number);
    }
}

///Returns found node, null if couldnt find
///Get parent is optional
node* find(node* root,char* searchElement,node** outParent){
    for(node *tmp=root,*parent=NULL;tmp!=NULL;tmp=tmp->next){
        if(!strcmp(searchElement,tmp->number)){
            return tmp;
            if(outParent!=NULL) *outParent = parent;
        }
        parent = tmp;
    }
    return NULL;
}

///Wrapper for recursive findAndRemove
///Root - root node
node* findAndRemove(node* root,char* searchTerm,int* wasFound){
    return _findAndRemove(root,root,NULL,searchTerm,wasFound);
}


///Find and remove an element
///Returns - new head;
///NOTE: ROOT IS A GIVEN ELEMENT IN RECURSION
///wasFound is optional
node* _findAndRemove(node* head,node* root,node* parent,char* searchTerm,int* wasFound){
    if(root==NULL){
        ///Could not find, return Head and set state to could not find
        if(wasFound!=NULL)*wasFound=0;
        return head;
    }
    if(!strcmp(searchTerm,root->number)){
        ///We have found the term, time to return the appropriate result (and propagate it outwards)
        if(wasFound!=NULL) *wasFound=1;
        ///if no parent, remove self, and return it
        if(parent==NULL){
            node* newHead = root->next;
            freeNode(root,NULL);
            return newHead;
        }
        ///Dont worry, we dont have to reassign anything, now worry about setting the right relations
        else{
            ///skip over root
            parent->next = root->next;
            freeNode(root,NULL);
            return head;
        }
    }
    else{
        ///Couldnt find in current element, send to next element
        _findAndRemove(head,root->next,root,searchTerm,wasFound);
    }
}
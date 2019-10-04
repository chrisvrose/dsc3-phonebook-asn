#include<strList.h>

#define PMNULL ((void*)0)

///obtain node and set vals
node* getNode(char* data){
    node* newNode;
    if((newNode = malloc(sizeof(node)))){
        newNode->number;newNode->next=PMNULL;
    }
    return newNode;
}

///Trash node (getting val is optional)
void freeNode(node* element,char* outVar){
    if(element!=PMNULL){
        if(outVar!=PMNULL){
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
    if(headNode!=PMNULL){
        removeAll(headNode->next);
        free(headNode);
    }
}


node* insertEnd(node* root){
    
}
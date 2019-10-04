#include<strList.h>

#define PMNULL ((void*)0)

node* getNode(char* data){
    node* newNode;
    if((newNode = malloc(sizeof(node)))){
        newNode->number;newNode->next=PMNULL;
    }
    return newNode;
}

//node* free

void removeAll(){

}
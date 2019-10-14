#define _STR_LIST_H 1

#define _STR_LIST_H_STRLEN 32


///Holds the number data
typedef struct node{
	///A standard notation is 10-digit number
	char number[_STR_LIST_H_STRLEN];
	struct node* next;
}node;

node* getNode(char*);

void freeNode(node*,char*);

void removeAll(node*);

node* insertEnd(node*,char*,int*);

node* find(node*,char*,node**);

node* findAndRemove(node*,char*,int*);

node* _findAndRemove(node*,node*,node*,char*,int*);

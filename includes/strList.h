#define _STR_LIST_H 1


///Holds the number data
typedef struct node{
	///A standard notation is 10-digit number
	char number[11];
	struct node* next;
}node;

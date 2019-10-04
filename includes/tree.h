/*

General logic:

Addition
1. Search if exists.
	True
		1. Insert into dataHead;
	False
		1. Create Tree Element


*/
#define _TREE_H

#define _TREE_H_STRLEN 32

#include<strList.h>

///Contains the tree def
typedef struct treeNode{
	struct treeNode* left;
	struct treeNode* right;
	///Contains data key
	char name[_TREE_H_STRLEN];
	///Height info
	int height;
	///Contains data
	struct node* dataHead;
}treeNode;

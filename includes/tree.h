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

typedef struct Tree{
	treeNode *root;
}Tree;


///Contains the tree def
typedef struct treeNode{
	struct treeNode* left;
	struct treeNode* right;
	//Contains data
	char name[_TREE_H_STRLEN];
	int count;
	struct node dataHead;
}treeNode;

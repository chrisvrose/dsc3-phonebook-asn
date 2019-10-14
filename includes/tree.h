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
	struct node* emailHead;
}treeNode;


int getHeight(treeNode* treenode);

int getBalance(treeNode* root);

treeNode* getNewTreeNode(char* name,char* number,char* email);

treeNode* trashTreeNode(treeNode* someNode);

treeNode* treeSearch(treeNode* treenode,char* searchElement);

treeNode* leftRotate(treeNode*);

treeNode* rightRotate(treeNode*);

treeNode* insert(treeNode* root,char* name,char* number,char* email);

treeNode* removeFromTree(treeNode* root,char* name);

treeNode* getMinTree(treeNode* tree);

treeNode *insertToTree(treeNode *root, int mode, char *name, char *insertable);

treeNode *trimFromTree(treeNode *root, int mode, char *name, char *deletable);
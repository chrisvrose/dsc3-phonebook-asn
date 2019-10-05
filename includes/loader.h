#define _LOADER_H

#ifndef _TREE_H
#include<tree.h>
#endif

int savetREE(treeNode* root,char* fileName);

treeNode* loadtREE(char* fileName);
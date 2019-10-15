#ifndef _TREE_H
#include <tree.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))

///A getter
int getHeight(treeNode* treenode)
{
    if (treenode == NULL) {
        return 0;
    } else {
        return treenode->height;
    }
}

///Balance:
///>0: left heavy
///<0: right heavy
int getBalance(treeNode* root)
{
    if (root == NULL) {
        return 0;
    } else {
        return getHeight(root->left) - getHeight(root->right);
    }
}

///Obtain a new treeNode
///Number if null, will create a listless entry (can be used to dataload)
treeNode* getNewTreeNode(char* name, char* number, char* email)
{
    treeNode* newNode;
    if ((newNode = malloc(sizeof(treeNode)))) {
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        strcpy(newNode->name, name);
        if (number != NULL) {
            newNode->dataHead = insertEnd(NULL, number, NULL);
            newNode->emailHead = insertEnd(NULL, email, NULL);
        }
    }
    return newNode;
}

///Required to trash all data inside if any
treeNode* trashTreeNode(treeNode* someNode)
{
    removeAll(someNode->dataHead);
    removeAll(someNode->emailHead);
    free(someNode);
    ///Just to help
    return NULL;
}

///Standard BST implementation
///Return searched element, null if not found
treeNode* treeSearch(treeNode* treenode, char* searchElement)
{
    if (treenode == NULL) {
        return NULL;
    }
    int results = strcmp(treenode->name, searchElement);
    ///Was it that?
    if (!results) {
        return treenode;
    } else if (results > 0) {
        return treeSearch(treenode->left, searchElement);
    } else {
        return treeSearch(treenode->right, searchElement);
    }
}

treeNode* rightRotate(treeNode* b)
{
    treeNode* a = b->left;
    treeNode* treeToChange = a->right;

    ///Make the rotation
    a->right = b;
    b->left = treeToChange;

    ///Recalc heights
    b->height = MAX(getHeight(b->left), getHeight(b->right)) + 1;
    a->height = MAX(getHeight(a->left), getHeight(a->right)) + 1;

    ///a becomes the new root
    return a;
}

treeNode* leftRotate(treeNode* b)
{
    treeNode* a = b->right;
    treeNode* treeToChange = a->left;

    ///Make rotations
    a->left = b;
    b->right = treeToChange;

    ///Recalc heights
    a->height = MAX(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = MAX(getHeight(b->left), getHeight(b->right)) + 1;

    return a;
}

/*
    AVL insert:
    returns:
        for each: more inserts/
        on whole: 
*/
treeNode* insert(treeNode* root, char* name, char* number, char* email)
{
    ///Step 1: Perform the bog standard BST insertion
    if (root == NULL) {
        //We found where to insert, do it
        return getNewTreeNode(name, number, email);
    }

    int getCmp = strcmp(name, root->name);
    if (getCmp < 0) {
        root->left = insert(root->left, name, number, email);
    } else if (getCmp > 0) {
        root->right = insert(root->right, name, number, email);
    } else {
        ///Equality, yikes!
        if (number) {
            root->dataHead = insertEnd(root->dataHead, number, NULL);
        }
        if (email) {
            root->emailHead = insertEnd(root->emailHead, email, NULL);
        }
    }

    ///Make new height
    root->height = MAX(getHeight(root->left), getHeight(root->right)) + 1;

    ///Done with insertion, get balance factor
    int balance = getBalance(root);

    ///Now the tricky part
    ///2 variables - where the node was pushed wrt root, and the balance
    /// 4 outcomes

    ///heavy on left side and it got inserted below the left child
    if (balance > 1 && strcmp(name, root->left->name) < 0) {
        return rightRotate(root);
    }

    ///Heavy on the right side, and insertion occured on the right
    if (balance < -1 && strcmp(name, root->right->name) > 0) {
        return leftRotate(root);
    }

    ///Heavy on the left side, got inserted onto the right of the left child
    if (balance > 1 && strcmp(name, root->left->name) > 0) {
        ///Rotate left
        root->left = leftRotate(root->left);
        ///Rotate self rightways
        return rightRotate(root);
    }

    ///Heavy on right, and got inserted on the left
    if (balance < -1 && strcmp(name, root->right->name) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    ///for anything else
    return root;
}

treeNode* getMinTree(treeNode* tree)
{
    treeNode* temp = tree;
    for (; temp != NULL ? temp->left != NULL : 0; temp = temp->left)
        ;
    return temp;
}

///If by chance both numberhead and emailHead get nulled, eradicate that node
///1 - phone 0 - email
treeNode* trimFromTree(treeNode* root, int mode, char* name, char* deletable)
{
    int wasDeleted = 0;
    if (mode) {
        root->dataHead = findAndRemove(root->dataHead, deletable, &wasDeleted);
    } else {
        root->emailHead = findAndRemove(root->emailHead, deletable, &wasDeleted);
    }
    ///If both are empty
    if (root->dataHead && root->emailHead) {
        root = removeFromTree(root, name);
    }
    return root;
}

treeNode* insertToTree(treeNode* root, int mode, char* name, char* insertable)
{
    int wasInserted = 0;
    treeNode* toFind = treeSearch(root, name);
    if (toFind) {
        if (mode) {
            toFind->dataHead = insertEnd(toFind->dataHead, insertable, &wasInserted);
        } else {
            toFind->emailHead = insertEnd(toFind->emailHead, insertable, &wasInserted);
        }
    }
    return root;
}

treeNode* removeFromTree(treeNode* root, char* name)
{
    ///If null, dont bother doing anything
    if (root == NULL) {
        return root;
    }

    int cmpRes = strcmp(name, root->name);
    ///BST descend
    if (cmpRes < 0) {
        root->left = removeFromTree(root->left, name);
    } else if (cmpRes > 0) {
        root->right = removeFromTree(root->right, name);
    } else {
        ///Found the element.
        ///If number is null, delete regardless
        ///All cases:
        ///0-2 children
        ///This: one or none
        if ((root->left == NULL) || (root->right == NULL)) {
            treeNode* loneChild = root->left ? root->left : root->right;

            ///LIE, there was no child
            if (loneChild == NULL) {
                loneChild = root;
                root = NULL;
            } else {
                ///Copy it over :O
                *root = *loneChild;
            }

            trashTreeNode(loneChild);
        } else {
            ///We have two children, oh no
            ///Get inorder successor
            treeNode* temp = getMinTree(root->right);

            ///To swap
            node* tempDataNode;
            tempDataNode = root->dataHead;
            root->dataHead = temp->dataHead;
            temp->dataHead = tempDataNode;
            strcpy(root->name, temp->name);

            tempDataNode = root->emailHead;
            root->emailHead = temp->emailHead;
            temp->emailHead = tempDataNode;

            ///Delete that thing
            root->right = removeFromTree(root->right, temp->name);
        }

        ///After deletion, nothing is left, no need to balance

        if (root == NULL) {
            return root;
        }

        ///Get the new height
        root->height = MAX(getHeight(root->left), getHeight(root->right)) + 1;

        ///Get balance stats
        int balance = getBalance(root);

        ///4 cases as in insertion
        ///Left heavy and left not right heavy
        if (balance > 1 && getBalance(root->left) >= 0) {
            return rightRotate(root);
        }
        ///Right heavy, and right not right heavy
        if (balance < -1 && getBalance(root->right) <= 0) {
            return leftRotate(root);
        }

        ///Left heavy and left is not left or left heavy
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->right);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    ///All said, return
    return root;
}
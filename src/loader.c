#ifndef _LOADER_H
#include <loader.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

int savetREE(treeNode* root, char* fileName)
{
    if (root != NULL) {
        int gv1 = savetREE(root->left, fileName);
        FILE* fp = fopen(fileName, "a");
        if (fp == NULL) {
            return 0;
        }
        fputs(root->name, fp);
        fputs(":", fp);
        node* temp = root->dataHead;
        for (; temp != NULL; temp = temp->next) {
            //fprintf(fp,"%s%s",temp->number,((temp->next==NULL)?",\n":",") );
            fputs(temp->number, fp);
            fputs(",", fp);
        }

        fputc('?', fp);

        temp = root->emailHead;
        for (; temp != NULL; temp = temp->next) {
            fputs(temp->number, fp);
            fputs((temp->next == NULL) ? ",\n" : ",", fp);
        }
        //printf("Wrote");
        fclose(fp);
        int gv2 = savetREE(root->right, fileName);

        return gv1 && gv2;
    } else {
        return 1;
    }
}

treeNode* loadtREE(char* fileName)
{
    ///Init everything
    treeNode* root = NULL;

    char name[_TREE_H_STRLEN], number[_TREE_H_STRLEN], getLine[10 * _TREE_H_STRLEN];
    FILE* fp = fopen(fileName, "r");

    if (fp != NULL) {
        int i = 0, j = 0, k = 0;
        while (fgets(getLine, sizeof(10 * 32), fp) > 0) {
            ///I - position on getLine
            ///J - position on name/number
            ///K - 0-name,1-number,2-email
            for (i = 0; getLine[i] != 0; i++) {
                switch (getLine[i]) {
                case ':':
                    ///Switch to num
                    name[j] = 0;
                    j = 0;
                    root = insert(root, name, NULL, NULL);
                    ///Switch to storing to number
                    k = 1;
                    break;
                case ',':
                    ///Number/email is ready
                    number[j] = 0;
                    j = 0;
                    ///Insert into tree
                    ///1 -> 1 - number
                    ///2 -> 0 - email
                    root = insertToTree(root, 2 - k, name, number);
                    break;
                case '?':
                    ///its emails now
                    k = 2;
                    j = 0;
                    break;
                case '\n':
                    ///EOL, reset name and word
                    j = 0;
                    k = 0;
                    break;
                default:
                    ///Where to dump? decide by k
                    if (k) {
                        ///k=1=>dump into number/email
                        number[j++] = getLine[i];
                    } else {
                        ///k=0=>dump into name
                        name[j++] = getLine[i];
                    }
                }
            }
        }
        fclose(fp);
    }
    return root;
}
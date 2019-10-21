
#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _TREE_H
#include <tree.h>
#endif

#ifndef _LOADER_H
#include <loader.h>
#endif

#include <time.h>

#define MENU                                                                                             \
    "1. Menu\n2. Insert\n3. Remove Entries\n4. Update Entries\n5. Find Entry\n6. Save entries\n7. Load " \
    "entries\n8. Search entries\n9. Print All\n0. Exit\n"

void printTreeNodeFormatted(treeNode* root)
{
    printf("Name:%s\n", root->name);
    printf("Phone numbers:\n\t");
    node* temp = root->dataHead;
    for (; temp != NULL; temp = temp->next) {
        printf("%s%c", temp->number, ((temp->next == NULL) ? '\n' : ','));
    }
    printf("Email Addresses:\n\t");
    temp = root->emailHead;
    for (; temp != NULL; temp = temp->next) {
        printf("%s%c", temp->number, ((temp->next == NULL) ? '\n' : ','));
    }
}

void prettyInOrder(treeNode* root)
{
    if (root != NULL) {
        prettyInOrder(root->left);
        printTreeNodeFormatted(root);
        prettyInOrder(root->right);
    }
}

int main()
{
    treeNode* phoneBookRoot = NULL;
    char buffer1[_TREE_H_STRLEN], buffer2[_TREE_H_STRLEN],
        buffer3[_TREE_H_STRLEN];
    /// Get status of buffer reads
    int status1 = 0, status2 = 0, status3 = 0, status4 = 0, iBuff1 = 0, iBuff2 = 0, iBuff3 = 0, clockable = 0, choice = 0;
    /// Clock to time events
    clock_t start, end;
    printf(MENU);
    for (choice = 0; (printf("Option\n:"), scanf("%d", &choice) == 1); clockable = 0) {
        switch (choice) {
        case 0:
            printf("...\n");
            return 0;
        case 1:
            printf(MENU);
            break;
        case 2:
            printf("Enter name\n:");
            status1 = scanf(" %31[^\n]", buffer1);
            printf("Enter number\n:");
            status2 = scanf(" %10s", buffer2);
            printf("Enter email\n:");
            status3 = scanf(" %31[^\n]", buffer3);

            start = clock();

            if (status1 == 1 && status2 == 1) {
                phoneBookRoot = insert(phoneBookRoot, buffer1, buffer2, buffer3);
            } else {
                fprintf(stderr, "E:Invalid input\n");
            }

            end = clock();
            clockable = 1;
            // getchar();getchar();
            break;
        case 3:
            printf("Enter name\n:");
            status1 = scanf(" %31[^\n]", buffer1);
            start = clock();
            if (status1 == 1 && status2 == 1) {
                phoneBookRoot = removeFromTree(phoneBookRoot, buffer1);
            } else {
                fprintf(stderr, "E:Invalid input\n");
            }
            end = clock();
            clockable = 1;

            break;
        case 4:
            printf("Enter name\n:");
            status1 = scanf(" %31[^\n]", buffer1);
            if (status1 == 1) {
                treeNode* info = treeSearch(phoneBookRoot, buffer1); //find(phoneBookRoot, buffer1, NULL);
                if (info) {
                    printTreeNodeFormatted(info);
                    printf("1. Insert\n2. Delete\n:");
                    status2 = scanf("%d", &iBuff2);
                    if (status2 == 1 && (iBuff2 == 1 ? 1 : iBuff2 == 2)) {
                        printf("1. Email\n2. Phone number\n:");
                        status3 = scanf("%d", &iBuff3);
                        if (status3 == 1 && (iBuff3 == 1 ? 1 : iBuff3 == 2)) {
                            /// Read
                            ///
                            iBuff3 -= 1;
                            if (iBuff2 == 1) {
                                printf("Enter element to insert\n:");
                                status4 = scanf(" %31[^\n]", buffer2);
                                if (status4 == 1) {
                                    start = clock();

                                    phoneBookRoot = insertToTree(phoneBookRoot, iBuff3 ? 1 : 0, buffer1, buffer2);

                                    end = clock();
                                    clockable = 1;
                                }
                            } else if (iBuff2 == 2) {
                                printf("Enter element to delete\n:");
                                status4 = scanf(" %31[^\n]", buffer2);
                                if (status4) {
                                    start = clock();

                                    phoneBookRoot = trimFromTree(phoneBookRoot, iBuff3 ? 1 : 0, buffer1, buffer2);

                                    end = clock();
                                    clockable = 1;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 5:
            printf("Enter name\n:");
            scanf(" %31[^\n]", buffer1);
            if (status1) {
                treeNode* foundNode = treeSearch(phoneBookRoot, buffer1);
                if (foundNode) {
                    printTreeNodeFormatted(foundNode);
                } else {
                    fprintf(stderr, "E:Could not find\n");
                }
            }
            break;
        case 6:
            printf("Enter filename\n:");
            status1 = scanf(" %31[^\n]", buffer1);

            start = clock();
            if (status1) {
                int status2 = savetREE(phoneBookRoot, buffer1);
                printf("S:%d\n", status2);
            } else {
                fprintf(stderr, "E:Invalid input\n");
            }
            end = clock();
            clockable = 1;
            break;
        case 7:
            printf("Enter filename\n:");
            status1 = scanf(" %31[^\n]", buffer1);

            start = clock();
            if (status1 && phoneBookRoot == NULL) {
                phoneBookRoot = loadtREE(buffer1);
                if (phoneBookRoot == NULL) {
                    fprintf(stderr, "E:Could not load\n");
                } else {
                    printf("Loaded records.\n");
                }
            } else {
                fprintf(stderr, "E:Invalid input or Tree already in memory\n");
            }
            end = clock();
            clockable = 1;
            break;
        case 8:
            printf("Enter name\n:");
            status1 = scanf(" %31[^\n]", buffer1);

            start = clock();
            if (status1) {
                treeNode* ele = treeSearch(phoneBookRoot, buffer1);
                if (ele == NULL) {
                    printf("Could not find\n");
                } else {
                    printf("%s:", ele->name);
                    node* temp = ele->dataHead;
                    for (; temp != NULL; temp = temp->next) {
                        printf("%s%c", temp->number, ((temp->next == NULL) ? '\n' : ','));
                    }
                }
            } else {
                fprintf(stderr, "E:Invalid input\n");
            }
            end = clock();
            clockable = 1;
            break;
        case 9:
            start = clock();
            prettyInOrder(phoneBookRoot);
            end = clock();
            clockable = 1;

            break;
        default:
            printf("Invalid choice\n");
        }
        if (clockable) {
            printf("Query took:%2.5lfs\n", ((double)end - start) / CLOCKS_PER_SEC);
        }
    }
}


#ifndef _STDIO_H
#include<stdio.h>
#endif

#ifndef _STDLIB_H
#include<stdlib.h>
#endif

#include<tree.h>

#define MENU "1.Insert\n2.Remove Entries\n3.Save entries\n4.Load entries\n5.Search entries\n6.Print All\n7. Exit\n"

void prettyInOrder(treeNode* root){
	if(root!=NULL){
		prettyInOrder(root->left);
		printf("%s:",root->name);
		node* temp = root->dataHead;
		for(;temp!=NULL;temp=temp->next){
			printf("%s%c",temp->number,((temp->next==NULL)?'\n':',') );
		}
		prettyInOrder(root->right);
	}
}




int main(){
	treeNode* phoneBookRoot=NULL;
	char buffer1[_TREE_H_STRLEN],buffer2[_TREE_H_STRLEN];
	///Get status of buffer reads
	int status1=0,status2=0;
	printf("%s",MENU);
	for(int choice=0;(printf("Option\n:",MENU),scanf("%d",&choice)==1);){
		switch(choice){
			case 1:
				printf("Enter name\n:");
				status1 = scanf(" %31[^\n]",buffer1);
				printf("Enter number\n:");
				status2 = scanf(" %10s",buffer2);

				if(status1==1&&status2==1){
					phoneBookRoot = insert(phoneBookRoot,buffer1,buffer2);
				}else{
					fprintf(stderr,"E:Invalid input\n");
				}

				//getchar();getchar();
				break;
			case 6:
				prettyInOrder(phoneBookRoot);

				//getchar();getchar();
				break;
			case 7:
				printf("...\n");

				//getchar();getchar();
				return 0;
			default:
				printf("Invalid choice\n");
		}
	}
}

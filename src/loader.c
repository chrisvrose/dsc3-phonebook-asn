#ifndef _LOADER_H
#include<loader.h>
#endif

#ifndef _STRING_H
#include<string.h>
#endif

#ifndef _STDIO_H
#include<stdio.h>
#endif

#ifndef _STDLIB_H
#include<stdlib.h>
#endif


int savetREE(treeNode* root,char* fileName){
    if(root!=NULL){
		int gv1 = savetREE(root->left,fileName);
        FILE* fp = fopen(fileName,"a");
        if(fp==NULL){
            return 0;
        }
		fputs(root->name,fp);
        fputs(":",fp);
		node* temp = root->dataHead;
		for(;temp!=NULL;temp=temp->next){
			//fprintf(fp,"%s%s",temp->number,((temp->next==NULL)?",\n":",") );
            fputs(temp->number,fp);
            fputs((temp->next==NULL)?",\n":",",fp);
		}
        //printf("Wrote");
        fclose(fp);
		int gv2 = savetREE(root->right,fileName);

        return gv1&&gv2;
	}else{
        return 1;
    }
}


treeNode* loadtREE(char* fileName){

}
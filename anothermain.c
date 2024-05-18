#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"tools.h"


char infix[MAX];
char postfix[MAX];
char* varnames;

int main(){

    char x;
    int choice;
    fgets(infix,MAX,stdin);
    fflush(stdin);

    int load = 0;
    int numvar=inttopos(infix, postfix, &load);
    char* varnames = setvarname(numvar);
    
    // evaluate
    bool* arr=(bool*)calloc(numvar,sizeof(bool));
    int NUV=pov2(numvar);
    
    for(int i=0;i<NUV;i++){
        for(int j=0;j<numvar;j++){
            printf("%d|",arr[j]);
        }
        printf("| %d",evaluate(postfix, arr, varnames, numvar));
        printf("\n");
        inc(arr,numvar-1);
    }
    for(int i=0;i<numvar;i++){
        printf("%c|",varnames[i]);
    }printf("| \n");

    return 0;
}
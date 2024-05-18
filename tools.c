/*START DATE - appprox 30Aug2023*/
/*Goal: Program to generate truth table of given bool expression
Step 1: Input bool expression
    ^ is AND
    v is OR
    > is implication (conditional)
    ~ is negation
    = is equivalence (biconditional)
Step 2: Converts given expression into postfix
Step 3: Evaluate Postfix Expression for variables p,q,r
NEXT STEP: Evaluate Postfix Expression in n number of arbitary variables...... ---- DONE
NEXT TO-DO: Implement better binary strings
            Use file input
***In Progress***
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "tools.h"
#define MAX 100
#define HASHTABLESIZE 50


bool AND(bool a,bool b){
    return(a&b);
}
bool OR(bool a,bool b){
    return(a|b);
}
bool NOT(bool a){
    return !a;
}
bool IMPLIES(bool a,bool b){
    return(!a|b);
}
bool BICOND(bool a,bool b){
    return(a==b);
}

int load = -1;
int top=-1;
char stack[MAX];
int hashtable[HASHTABLESIZE]={0};



char stacktop(){ // returns top element of stack
    return(top>=0?stack[top]:0); // returns null char if stack is empty
}
int iskali(){ // return 1 if top is -1
    return(top==-1 ? 1 : 0);
}
void printstack(){ // prints out the stack
 // used for debugging
    int i;
    printf("{ ");
    for(i=0;i<=top;i++){
        printf("%c ,",stack[top]);
    }
    printf("\b}");
}
 // string containing given input of infix boolean expression

int isoperator(char x){
    return((x=='=' || x=='>' || x=='v' || x=='&' || x=='V' || x=='^'));
}
int isunaryoperator(char x){
    return((x=='~' || x=='-'));
}
int isletter(char x){ // any letter except v or V
    return(((65<=x && x<=90) || (97<=x && x<=122)) && (x!='v' && x!='V'));
}
int prec(char x){ // order of precedence "~" > "&" > "v" > ">" > "=" > "("
    if(x=='(') return 0;
    else if(x=='=') return 1;
    else if(x=='>') return 2;
    else if(x=='v' || x=='V' || x=='+') return 3;
    else if(x=='&' || x=='^' || x=='*') return 4;
    else if(x=='~' || x=='-') return 5;
    else return -1;
}
void keep(char* postfix, char x){ // push a char onto postfix[]
    postfix[++load]=x;
}
char pop(char* postfix){ // remove element from stack and push them in postfix[];
    keep(postfix, stacktop());
    return(stack[top--]);
}
void push(char* postfix, char x){ // push char on to stack
    if(prec(x)>prec(stacktop())){ // if x has more precedence than the existing top element, then x can sit on top of it.
        top++;
        stack[top]=x; // the edge case of the stack being empty is also handled as stacktop return '\0'(which has precedence of -1) when top==-1.
    }
    else{ // else 
        pop(postfix); // pop the topmost element
        push(postfix, x); // recursivly try again
    }
}


int hashmap(char x){
    return x-97;
}
char invhashmap(int n){
    return n+97;
}
void printhashmap(){
    printf("{");
    for(int i=0;i<HASHTABLESIZE;i++){
        printf("%d,",hashtable[i]);
    }
    printf("\b}");
}

/*
char* varnames=(char*)malloc(num*sizeof(char));
    for(i=0;i<HASHTABLESIZE;i++){
        if(hashtable[i]){
            varnames[j]=invhashmap(i);
            j++;
        }
    }
*/

int inttopos(char* infix, char* postfix, int* loady){ // returns number of variables
    int i;
    int numberofvariables=0;
    for(i=0;infix[i];i++){
        if(isletter(infix[i])){ // if element is a letter, push it onto postfix
            keep(postfix, infix[i]);
            if(!hashtable[hashmap(infix[i])]){ //if var not already counted
                numberofvariables++;//icrement number of variables
                hashtable[hashmap(infix[i])]=1;//mark variable as counted
                // printf("\n\n_______n=%d,i=%d_______\n\n",numberofvariables,i);
            }
        }
        else if(isoperator(infix[i])||isunaryoperator(infix[i])){ // if element is a operator, push it onto stack
            push(postfix, infix[i]); 
        }
        else if(infix[i]=='('){ // if '(' then push it forcibly onto stack
            stack[++top]='('; // forcibly keep (
        }
        else if(infix[i]==')'){ // if '). then pop every element from stack till you reach '(' as top element
            while(stacktop()!='(') pop(postfix);
            top--; // get rid of (
        }
        else if(infix[i]==32){ // if SPACEBAR then continue
            continue;
        }
        else if(infix[i]==' ') continue;
        else if(infix[i]=='\n') continue;
        else{
            printf("Unknown char %d\n",(int)infix[i]);
            exit(1);
        }
    }
     // when you reach end of infix[] , pop all remaining elements from stack
    while(!iskali()){
        char check=pop(postfix);
        if(check=='(' || check==')') printf("UNBALANCED PARENTHESIES");
    }
    keep(postfix, 0); // append NULL character to postfix[] string
    loady = &load;
    
    //int array[2] = {numberofvariables,load};
    return(numberofvariables);
}

char* setvarname(int numberofvariables){
    char* varnames=(char*)malloc(numberofvariables*sizeof(char));
    int i,j=0;
    for(i=0;i<HASHTABLESIZE;i++){
        if(hashtable[i]){
            varnames[j]=invhashmap(i);
            j++;
        }
    }
    return varnames;
}

bool evaluate(char* postfix, bool* values, char* varnames, int num){
    //int* evalstack=(int*)malloc(MAX*sizeof(int));
    bool evalstack[MAX];
    int evaltop=-1;
    int i,j=0;
    
    // int* variables=(int*)malloc(num*sizeof(int));
    
     // j=0;

    for(i=0;i<=load;i++){
        /*
        isletter-- push onto eval stack
        isunaryoperator-- pop one element, push ~element
        is_operator-- pop 2 elements(let's say a,b), push a x b (whwere x is the operator)
        */
       if(isletter(postfix[i])){
        for(j=0;j<num;j++){
            if(postfix[i]==varnames[j]) evalstack[++evaltop]=values[j];
        }
       }
       else if(isunaryoperator(postfix[i])){ // NEGATION
         // top--;
        evalstack[evaltop]=NOT(evalstack[evaltop]);        
       }
       else if(postfix[i]=='v'||postfix[i]=='+'||postfix[i]=='V'){ // DISJUNCTION
        evalstack[evaltop-1]=OR(evalstack[evaltop],evalstack[evaltop-1]);
        evaltop--;
       }
       else if(postfix[i]=='^'||postfix[i]=='&'){ // CONJUNCTION
        evalstack[evaltop-1]=AND(evalstack[evaltop],evalstack[evaltop-1]);
        evaltop--;
       }
       else if(postfix[i]=='>'){ // CONDITIONAL
        evalstack[evaltop-1]=IMPLIES(evalstack[evaltop-1],evalstack[evaltop]);
        evaltop--;
       }
       else if(postfix[i]=='='){ // BICONDITIONAL
        evalstack[evaltop-1]=BICOND(evalstack[evaltop],evalstack[evaltop-1]);
        evaltop--;
       }

    }
    int hold=evalstack[evaltop];
     // free(evalstack);
     // the below is just a print line for debugging
     // printf("\n\n%d| %d %d %d\n\n",evaltop,evalstack[0],evalstack[1],evalstack[evaltop]);
    return(hold);
}

/* int main(){
    inttopos();
    for(int i=0;i<=load;i++){
        printf("%c",postfix[i]);
    }
    int num = countit();
    bool arr[5] = {1,1,1,0,1};
    
    int answer = evaluate(arr,num);
    printhashmap();
    printf("\n%d\nnum value is %d\n",answer,num);
    return 0;
} */

void inc(bool* bin,int n){ // not the best way to implement binary strings.
// It would be better to extract induvidual bits of integers 0 <= num < 2^n using (num&(1<<k))>>k
// But changing this needs a lot of work and I'll do it later.
    if(n==0){
        bin[n]=1;
        return;
    }
    if(bin[n]==0) bin[n]=1;
    else{
        bin[n]=0;
        inc(bin,n-1);
    }
}

char maptoTF(int n){
    if(n==0) return 'F';
    else if(n==1) return 'T';
    else return 'r';
}
int pov2(int n){
    int N=1;
    for(int i=0;i<n;i++){
        N=2*N;
    }
    return(N);
}

void menu(){
    printf("------------------------------------------------------Boolean Table------------------------------------------------------\n\n");
    printf("Input bool expression\n^ is AND \nv is OR\n> is implication (conditional)\n~ is negation\n= is equivalence (biconditional)\n\n");
    printf("\n__________________ENTER A BOOL EXPRESSION IN 4 VARIABLES p,q,r,s__________________\n\n");

}

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
#define MAX 100
#define HASHTABLESIZE 50


bool AND(bool a,bool b);
bool OR(bool a,bool b);
bool NOT(bool a);
bool IMPLIES(bool a,bool b);
bool BICOND(bool a,bool b);




char stacktop();
int iskali();
void printstack();
int isoperator(char x);
int isunaryoperator(char x);
int isletter(char x);
int prec(char x);
void keep(char*, char);
char pop(char*);
void push(char*, char x);

int hashmap(char x);
char invhashmap(int n);
void printhashmap();
int inttopos(char* infix, char* postfix, int* loady);
char* setvarname(int numberofvariables);
bool evaluate(char* postfix,bool* values,char* varnames, int num);

void inc(bool* bin,int n);

char maptoTF(int n);
int pov2(int n);

void menu();
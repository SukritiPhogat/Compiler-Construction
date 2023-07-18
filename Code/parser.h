/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef PARSER
#define PARSER

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexerdef.h"
#include"parserdef.h"

int findEnum(char *input);
void initializeHashEnum();

int contains(int *a,int n);
int isTerminal(int x);
int nonTerminalIndex(int nt);
int terminalIndex(int t);

void printFirstAndFollow();
void printParseTable();
struct TreeNode* getRoot();
void populateGrammar();
void calculateFirst(int nt);
void calculateFollow(int nt);
void findFirstAndFollow();
void fillParseTable();

void sendList(struct tokenList* curr1);
struct StackTreeNode* initialize_TreeStack(int array_capacity);
void pushTreeStack(struct TreeNode* value_to_push,struct StackTreeNode* stack);
void popTreeStack(struct StackTreeNode* stack);
int emptyTreeStack(struct StackTreeNode* stack);
struct TreeNode* topTreeStack(struct StackTreeNode* stack);
void StackandParseTreeImplementation(int flag);
void printTreeInorder(struct TreeNode* startTreeNode);
int getSizeOfTree();
int getCountOfTree();
#endif
/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef PARSERDEF_H
#define PARSERDEF_H
#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lexerdef.h"

#define nonTerminalCount 75
#define terminalCount 57
#define ruleCount 200
#define sizeofRHS 20
#define sizeofFF 50
#define MAX_SIZE 10000

int grammar[ruleCount][sizeofRHS];
int first[nonTerminalCount][sizeofFF];
int follow[nonTerminalCount][sizeofFF];
int parseTable[nonTerminalCount][terminalCount+1];
int isFirstCalculated[nonTerminalCount];
int isFollowCalculated[nonTerminalCount];

struct TreeNode
{
    struct tokenInfo NodeTokenInfo;
    struct TreeNode** child;
    struct TreeNode*  parent;
    int ruleNum;
};

struct StackTreeNode
{
    int top;
    int size;
    struct TreeNode** array;
};

#endif
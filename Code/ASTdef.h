/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef ASTDEF_H
#define ASTDEF_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"AST.h"
#include"parserdef.h"
#include"lexerdef.h"

struct ASTnode
{
    enum SYMBOL label;
    struct tokenInfo ASTtokenInfo;
    struct ASTnode* parent;
    struct ASTnode* children;
    struct ASTnode* next;
    struct symbolTable* scopedST;
};

#endif //ASTDEF_H
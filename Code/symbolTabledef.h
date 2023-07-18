/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef SYMBOLTABLEDEF_H
#define SYMBOLTABLEDEF_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"lexer.h"
#include"lexerdef.h"
#include"parser.h"
#include"parserdef.h"
#include"AST.h"
#include"ASTdef.h"
#include"semanticAnalyzer.h"
#include"semanticAnalyzerdef.h"
#define symbolTableSize 29

char* hashType[100];

struct entry
{
    char *name;
    struct Type type;

    struct symbolTable* parentST;

    int valueIfInt;
    double valueIfReal;
    bool valueIfBool;

    int width;
    int offset;
    int entryNestingLevel;

    struct entry* next;
};

struct symbolTable
{
    struct entry* hash_index[symbolTableSize];
    char* stName;
    int scope_start;
    int scope_end;
    int nestingLevel;
    struct symbolTable* next;
    struct symbolTable* children;
    struct symbolTable* parent;
};

#endif
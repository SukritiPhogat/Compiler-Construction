/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef SYMBOLTABLE
#define SYMBOLTABLE
#include<stdio.h>
#include"symbolTabledef.h"

void sendASTroot(struct ASTnode* curr1);
void initializeST(struct symbolTable* st);
int hashIndexST(char * name);
void insertInST(struct symbolTable* st, struct entry* newEntry);
void updateInST(struct entry* currEntry, struct entry* newEntry);
void addChildST(struct symbolTable* par, struct symbolTable* child);
struct entry *findInST(struct symbolTable* st,char * nameTofind);
void deleteST(struct symbolTable* st);
void symbolTableImplementation(struct symbolTable* st, struct ASTnode* root);
void printSymbolTable(struct symbolTable* st,int offset);
void initializeHashType();
void printArrayCase(struct symbolTable* st);


#endif
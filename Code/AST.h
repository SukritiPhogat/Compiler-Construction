/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef AST
#define AST

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ASTdef.h"
#include"lexerdef.h"
#include"parserdef.h"


struct ASTnode* newASTnode(enum SYMBOL ASTlabel);
struct ASTnode* makeLeaf(struct TreeNode* node);


void addChild(struct ASTnode* par, struct ASTnode* child);
void addChildList(struct ASTnode* par, struct ASTnode* child);
struct ASTnode* insertAtHead(struct ASTnode* head, struct ASTnode* nextNode);
struct ASTnode* insertAtEnd(struct ASTnode* head, struct ASTnode* nextNode);

void deleteParseTree(struct TreeNode* root);
struct ASTnode* buildAST(struct TreeNode* root,struct ASTnode* inherited);
int getSizeOfAST();
int getCountOfAST();
void printPreorderAST(struct ASTnode* root);

#endif



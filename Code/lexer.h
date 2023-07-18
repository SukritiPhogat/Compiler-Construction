/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef LEXER
#define LEXER
#include<stdio.h>
#include"lexerdef.h"

void loadBuffer();
void getNextToken();
void removeComments();
void initializeBuffer();
char getNextCharacter();
void initializeHashEnum();
void initializeHashTable();
void searchKeywordTable(char * lexeme);

#endif 
/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef semanticAnalyzer
#define semanticAnalyzer
#include"lexerdef.h"
#include "semanticAnalyzerdef.h"
#include "symbolTabledef.h"



struct Type initializeType();

struct Type typeCheck(struct ASTnode* root);





#endif
/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H
#include "lexerdef.h"


enum TYPE{integer,real,boolean,array,function,no_type,error};

struct Type
{
    enum TYPE type;
    //For arrays
    enum TYPE array_type;
    int isDynamic; 
    int start_idx;
    int end_idx;
};

#endif 


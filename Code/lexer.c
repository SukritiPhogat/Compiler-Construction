/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"lexerdef.h"
#include"lexer.h"
#define BUFFER_SIZE 16384

FILE *newfp;
int begin=0;
int forward=0;
int state=1;
int num_keys=10;
unsigned int lineNumber=1;
int currentBufferIndex=0;
int beginBufferIndex=0;

void initializeHashEnum()
{
    hashEnum[ID]="ID",
    hashEnum[parameter]="parameter",
    hashEnum[NUM]="NUM",
    hashEnum[RNUM] = "RNUM",
    hashEnum[RANGEOP] = "RANGEOP",
    hashEnum[PLUS] = "PLUS",
    hashEnum[MINUS] = "MINUS",
    hashEnum[MUL] = "MUL",
    hashEnum[DIV] = "DIV",
    hashEnum[LT] = "LT",
    hashEnum[DEF] = "DEF",
    hashEnum[DRIVERDEF] = "DRIVERDEF",
    hashEnum[LE] = "LE",
    hashEnum[GT]="GT",
    hashEnum[ENDDEF]="ENDDEF",
    hashEnum[WHILE]="WHILE",
    hashEnum[DEFAULT]="DEFAULT",
    hashEnum[BREAK]="BREAK",
    hashEnum[CASE]="CASE",
    hashEnum[SWITCH]="SWITCH",
    hashEnum[IN]="IN",
    hashEnum[FOR]="FOR",
    hashEnum[RETURNS]="RETURNS",
    hashEnum[INPUT]="INPUT",
    hashEnum[TAKES]="TAKES",
    hashEnum[PARAMETERS]="PARAMETERS",
    hashEnum[WITH]="WITH",
    hashEnum[USE]="USE",
    hashEnum[PRINT]="PRINT",
    hashEnum[GET_VALUE]="GET_VALUE",
    hashEnum[PROGRAM]="PROGRAM",
    hashEnum[MODULE]="MODULE",
    hashEnum[DRIVER]="DRIVER",
    hashEnum[DECLARE]="DECLARE",
    hashEnum[END]="END",
    hashEnum[START]="START",
    hashEnum[ARRAY]="ARRAY",
    hashEnum[OF]="OF",
    hashEnum[BOOLEAN]="BOOLEAN",
    hashEnum[REAL]="REAL",
    hashEnum[INTEGER]="INTEGER",
    hashEnum[FALSE]="FALSE",
    hashEnum[TRUE]="TRUE",
    hashEnum[OR]="OR",
    hashEnum[AND]="AND",
    hashEnum[SQBC]="SQBC",
    hashEnum[SQBO]="SQBO",
    hashEnum[BC]="BC",
    hashEnum[BO]="BO",
    hashEnum[SEMICOL]="SEMICOL",
    hashEnum[COMMA]="COMMA",
    hashEnum[ASSIGNOP]="ASSIGNOP",
    hashEnum[COLON]="COLON",
    hashEnum[EQ]="EQ",
    hashEnum[NE]="NE",
    hashEnum[GE]="GE",
    hashEnum[DRIVERENDDEF]="DRIVERENDDEF",

    hashEnum[EPSILON]="EPSILON", 
    hashEnum[DOLLAR]="DOLLAR" ,

    //NON TERMINALS
    hashEnum[kkk]="kkk",
    hashEnum[n_11]="n_11",
    hashEnum[new_index_for_loop]="new_index_for_loop",
    hashEnum[sign_for_loop]="sign_for_loop",
    hashEnum[index_for_loop]="index_for_loop",
    hashEnum[range_for_loop]="range_for_loop",
    hashEnum[new_caseStmt]="new_caseStmt",
    hashEnum[value]="value",
    hashEnum[def]="def",
    hashEnum[caseStmts]="caseStmts",
    hashEnum[arr_N5]="arr_N5",
    hashEnum[arrFactor]="arrFactor",
    hashEnum[arr_N4]="arr_N4",
    hashEnum[arrTerm]="arrTerm",
    hashEnum[arrExpr]="arrExpr",
    hashEnum[newExpr]="newExpr",
    hashEnum[new_factor]="new_factor",
    hashEnum[term_new]="term_new",
    hashEnum[factor]="factor",
    hashEnum[op2]="op2",
    hashEnum[term]="term",
    hashEnum[op1]="op1",
    hashEnum[newarithmeticExpr]="newarithmeticExpr",
    hashEnum[relationalOp]="relationalOp",
    hashEnum[new_Term2]="new_Term2",
    hashEnum[logicalOp]="logicalOp",
    hashEnum[new_Term]="new_Term",
    hashEnum[anyTerm]="anyTerm",
    hashEnum[var_id_num]="var_id_num",
    hashEnum[arithmeticExpr]="arithmeticExpr",
    hashEnum[new_NT]="new_NT",
    hashEnum[unary_op]="unary_op",
    hashEnum[unary]="unary",
    hashEnum[arithmeticOrBooleanExpr]="arithmeticOrBooleanExpr",
    hashEnum[new_idList]="new_idList",
    hashEnum[idList]="idList",
    hashEnum[new_actual_para_list]="new_actual_para_list",
    hashEnum[actual_para_list]="actual_para_list",
    hashEnum[optional]="optional",
    hashEnum[sign]="sign",
    hashEnum[eee]="eee",
    hashEnum[expression]="expression",
    hashEnum[lvalueIDStmt]="lvalueIDStmt",
    hashEnum[lvalueARRStmt]="lvalueARRStmt",
    hashEnum[whichStmt]="whichStmt",
    hashEnum[moduleReuseStmt]="moduleReuseStmt",
    hashEnum[assignmentStmt]="assignmentStmt",
    hashEnum[new_index]="new_index",
    hashEnum[new_P1]="new_P1",
    hashEnum[boolConstt]="boolConstt",
    hashEnum[var_print]="var_print",
    hashEnum[iterativeStmt]="iterativeStmt",
    hashEnum[conditionalStmt]="conditionalStmt",
    hashEnum[declareStmt]="declareStmt",
    hashEnum[simpleStmt]="simpleStmt",
    hashEnum[ioStmt]="ioStmt",
    hashEnum[statements]="statements",
    hashEnum[statement]="statement",
    hashEnum[index_arr]="index_arr",
    hashEnum[range_arrays]="range_arrays",
    hashEnum[type]="type",
    hashEnum[new_output_plist]="new_output_plist",
    hashEnum[dataType]="dataType",
    hashEnum[new_input_plist]="new_input_plist",
    hashEnum[output_plist]="output_plist",
    hashEnum[ret]="ret",
    hashEnum[input_plist]="input_plist",
    hashEnum[moduleDef]="moduleDef",
    hashEnum[module]="module",
    hashEnum[moduleDeclaration]="moduleDeclaration",
    hashEnum[driverModule]="driverModule",
    hashEnum[otherModules]="otherModules",
    hashEnum[moduleDeclarations]="moduleDeclarations",
    hashEnum[program]="program",
    hashEnum[start]="start";
}

struct tokenInfo currToken;
struct keylist KeyTable[26];

void copyLexeme(char* lexeme)
{
    int i=0;
    for(;i<strlen(lexeme);i++)
    {
        currToken.nameOfID[i]=lexeme[i];
    }
    currToken.nameOfID[i] = '\0';
}

void initializeBuffer(FILE *fp)
{
    newfp=fp;
    Buffer[0] = (char*)malloc(BUFFER_SIZE*sizeof(char));
    Buffer[1] = (char*)malloc(BUFFER_SIZE*sizeof(char));
    for(int i=0;i<BUFFER_SIZE;i++)
    {
      Buffer[0][i]=Buffer[1][i]=6;
    }
}

void loadBuffer()
{
     int reloadingBufferIndex=1-currentBufferIndex;
     memset(Buffer[reloadingBufferIndex],6,BUFFER_SIZE);
    // 6 is a non printable ASCII character used as BUFFER end marker
     int x = fread(Buffer[reloadingBufferIndex],BUFFER_SIZE,1,newfp);
    currentBufferIndex = 1 - currentBufferIndex;
}

char getNextCharacter()
{
  char c;
  if(forward==BUFFER_SIZE)
  {
     loadBuffer();
     forward=0;
     c=Buffer[currentBufferIndex][forward];
    return c;
  }
  c=Buffer[currentBufferIndex][forward];
  if(c==6)
  {
    loadBuffer();
     forward=0;
     c=Buffer[currentBufferIndex][forward];
    return c;
  }
  return c;
}

void initializeHashTable()
{
    for(int i=0;i<26;i++)
    {
        KeyTable[i].num_tokens=0;
    }
    //Keytable[i] stores keywords starting with 'a'+i
    //Hashing is done based on first character
        KeyTable[0].num_tokens=2;
        KeyTable[0].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[0].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[0].token_list[0]="array";
        KeyTable[0].token_list[1]="and";
        KeyTable[0].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[0].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[0].enum_list[0]=  ARRAY;                  
        KeyTable[0].enum_list[1]= AND;

        KeyTable[1].num_tokens=2;
        KeyTable[1].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[1].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[1].token_list[0]="boolean";
        KeyTable[1].token_list[1]="break";
        KeyTable[1].enum_list[0]= (enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[1].enum_list[1]= (enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[1].enum_list[0]=  BOOLEAN;                   
        KeyTable[1].enum_list[1]=  BREAK;

        KeyTable[2].num_tokens=1;
        KeyTable[2].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[2].token_list[0]="case";
        KeyTable[2].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[2].enum_list[0]=  CASE;                   

        KeyTable[3].num_tokens=3;
        KeyTable[3].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[3].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[3].token_list[2]=(char*)malloc(10*sizeof(char));
        KeyTable[3].token_list[0]="declare";
        KeyTable[3].token_list[1]="default";
        KeyTable[3].token_list[2]="driver";
        KeyTable[3].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[3].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[3].enum_list[2]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[3].enum_list[0]=  DECLARE;                   
        KeyTable[3].enum_list[1]=  DEFAULT;
        KeyTable[3].enum_list[2]=  DRIVER;

        KeyTable[4].num_tokens=1;
        KeyTable[4].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[4].token_list[0]="end";
        KeyTable[4].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[4].enum_list[0]=  END;                  

        KeyTable[5].num_tokens=2;
        KeyTable[5].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[5].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[5].token_list[0]="for";
        KeyTable[5].token_list[1]="false";
        KeyTable[5].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[5].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[5].enum_list[0]=   FOR;                 
        KeyTable[5].enum_list[1]=  FALSE;

        KeyTable[6].num_tokens=1;
        KeyTable[6].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[6].token_list[0]="get_value";
        KeyTable[6].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[6].enum_list[0]=  GET_VALUE;

        KeyTable[8].num_tokens=3;
        KeyTable[8].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[8].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[8].token_list[2]=(char*)malloc(10*sizeof(char));
        KeyTable[8].token_list[0]="input";
        KeyTable[8].token_list[1]="in";
        KeyTable[8].token_list[2]="integer";
        KeyTable[8].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[8].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[8].enum_list[2]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[8].enum_list[0]=  INPUT;                 
        KeyTable[8].enum_list[1]=  IN;
        KeyTable[8].enum_list[2]=  INTEGER;

        KeyTable[12].num_tokens=1;
        KeyTable[12].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[12].token_list[0]="module";
        KeyTable[12].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[12].enum_list[0]=  MODULE;

        KeyTable[14].num_tokens=2;
        KeyTable[14].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[14].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[14].token_list[0]="of";
        KeyTable[14].token_list[1]="or";
        KeyTable[14].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[14].enum_list[0]=  OF;
        KeyTable[14].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[14].enum_list[1]=  OR;

        KeyTable[15].num_tokens=3;
        KeyTable[15].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[15].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[15].token_list[2]=(char*)malloc(10*sizeof(char));
        KeyTable[15].token_list[0]="program";
        KeyTable[15].token_list[1]="print";
        KeyTable[15].token_list[2]="parameters";
        KeyTable[15].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[15].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[15].enum_list[2]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[15].enum_list[0]=  PROGRAM;                  
        KeyTable[15].enum_list[1]=  PRINT;
        KeyTable[15].enum_list[2]=  PARAMETERS;

        KeyTable[17].num_tokens=2;
        KeyTable[17].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[17].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[17].token_list[0]="real";
        KeyTable[17].token_list[1]="returns";
        KeyTable[17].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[17].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[17].enum_list[0]=  REAL;                   
        KeyTable[17].enum_list[1]=  RETURNS;

        KeyTable[18].num_tokens=2;
        KeyTable[18].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[18].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[18].token_list[0]="switch";
        KeyTable[18].token_list[1]="start";
        KeyTable[18].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[18].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[18].enum_list[0]=  SWITCH;
        KeyTable[18].enum_list[1]=  START;

        KeyTable[19].num_tokens=2;
        KeyTable[19].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[19].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[19].token_list[0]="true";
        KeyTable[19].token_list[1]="takes";
        KeyTable[19].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[19].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[19].enum_list[0]= TRUE;                   
        KeyTable[19].enum_list[1]=  TAKES;

        KeyTable[20].num_tokens=1;
        KeyTable[20].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[20].token_list[0]="use";
        KeyTable[20].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[20].enum_list[0]=  USE;                  

        KeyTable[22].num_tokens=2;
        KeyTable[22].token_list[0]=(char*)malloc(10*sizeof(char));
        KeyTable[22].token_list[1]=(char*)malloc(10*sizeof(char));
        KeyTable[22].token_list[0]="while";
        KeyTable[22].token_list[1]="with";
        KeyTable[22].enum_list[0]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[22].enum_list[1]=(enum SYMBOL)malloc(10*sizeof(enum SYMBOL));
        KeyTable[22].enum_list[0]= WHILE;                   
        KeyTable[22].enum_list[1]=  WITH;
}

// FUNCTION FOR SEARCHING WHETHER A STRING BELONGS TO THE KEYWORD TABLE OR NOT
void searchKeywordTable(char * lexeme)
{
    char* token;
    int key=lexeme[0]-'a';

    if(key<0)
    {
        if(!strcmp(lexeme,"AND"))
        {
            struct tokenInfo currToken;
            currToken.token =  AND;
            currToken.lineNo =lineNumber;
            int i=0;
            for(;i<strlen(lexeme);i++)
            {
                currToken.nameOfID[i]=lexeme[i];
            }
            currToken.nameOfID[i] = '\0';
                //--addding in linked list--//
            struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
            newNode->next = NULL;
            newNode->tokenValue = currToken;
            currentIndex->next = newNode;
            currentIndex=newNode;
        }

        else if (!strcmp(lexeme,"OR"))
        {
            struct tokenInfo currToken;
            currToken.token =  OR;
            currToken.lineNo=lineNumber;
            int i=0;
            for(;i<strlen(lexeme);i++)
            {
                currToken.nameOfID[i]=lexeme[i];
            }
            currToken.nameOfID[i] = '\0';
            //--addding in linked list--//
            struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
           newNode->next = NULL;
            newNode->tokenValue = currToken;
            currentIndex->next = newNode;
            currentIndex=newNode;
        }

        else 
        {
            struct tokenInfo currToken;
            currToken.token =  ID;
            currToken.lineNo=lineNumber;
            int i=0;
            for(;i<strlen(lexeme);i++)
            {
                currToken.nameOfID[i]=lexeme[i];
            }
            currToken.nameOfID[i] = '\0';
            //--addding in linked list--//
            struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
            newNode->next = NULL;
            newNode->tokenValue = currToken;
            currentIndex->next = newNode;
            currentIndex=newNode;
        }
    }

    else if(KeyTable[key].num_tokens>0){

        int list_size=KeyTable[key].num_tokens;
        int i;

        for( i=0;i<list_size;i++)
        {

            char * stored_val=KeyTable[key].token_list[i];

            if(!strcmp(lexeme,stored_val))
            {
                struct tokenInfo currToken ;
                currToken.token = KeyTable[key].enum_list[i];
                currToken.lineNo=lineNumber;
                 int i=0;
                for(;i<strlen(lexeme);i++)
                {
                currToken.nameOfID[i]=lexeme[i];
                }
                currToken.nameOfID[i] = '\0';

                struct tokenList* newNode = (struct tokenList*)malloc(sizeof(struct tokenList));
                newNode->next = NULL;
                newNode->tokenValue = currToken;

                currentIndex->next = newNode;
                currentIndex = newNode;
                break;
            }
        }

        if(i>=list_size)
        {
            struct tokenInfo currToken;
                    currToken.token =  ID;
                    currToken.lineNo=lineNumber;
                    int i=0;
                    for(;i<strlen(lexeme);i++)
                    {
                        currToken.nameOfID[i]=lexeme[i];
                    }
                    currToken.nameOfID[i] = '\0';
                    
                    struct tokenList* newNode = (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex=newNode;
        }
    }
    else{
                    struct tokenInfo currToken ;
                    currToken.token =  ID;
                    currToken.lineNo=lineNumber;
                    int i=0;
                    for(;i<strlen(lexeme);i++)
                    {
                        currToken.nameOfID[i]=lexeme[i];
                    }
                    currToken.nameOfID[i] = '\0';
                    
                    struct tokenList* newNode = (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex=newNode;
    }
    return;
}

void getNextToken() 
{
    while(c!=6)
    {
        switch(state)
        {
            case 1: //START STATE
            {
                c=getNextCharacter();
                if(c==' ' || c=='\t')  // WHITE SPACES HAVE TO BE JUST IGNORED AND MOVE AHEAD
                {
                    forward = forward + 1;
                    begin = begin + 1;
                    state = 1;
                }
                else if(c=='\n')
                {
                    forward = forward + 1;
                    begin = begin + 1;
                    lineNumber=lineNumber+1;
                    state = 1;
                }
                else if((c-'0')>=0 && (c-'0')<=9)
                {
                    state = 3;
                    forward = forward + 1;
                }
                else if(c=='.')
                {
                    state = 9;
                    forward = forward + 1;
                }
                else if(c=='+')
                {
                    forward = forward + 1;
                    state = 11;
                }
                else if(c=='-')
                {
                    forward = forward + 1;
                    state = 12;
                }
                else if(c=='*')
                {
                    forward = forward + 1;
                    state = 13;
                }
                else if(c=='/')
                {
                    forward = forward + 1;
                    state = 17;
                }
                else if(c=='<')
                {
                    forward = forward + 1;
                    state = 18;
                }
                else if(c=='>')
                {
                    forward = forward + 1;
                    state = 22;
                }
                else if(c=='!')
                {
                    forward = forward + 1;
                    state = 26;
                }
                else if(c=='=')
                {
                    forward = forward + 1;
                    state = 28;
                }
                else if(c==':')
                {
                    forward = forward + 1;
                    state = 30;
                }
                else if(c==',')
                {
                    forward = forward + 1;
                    state = 32;
                }
                else if(c==';')
                {
                    forward = forward + 1;
                    state = 33;
                }
                else if((c>=65 && c<=90) || (c>=97 && c<=122) || (c=='_')) // Remember that --> _abc is allowed
                {
                    forward = forward + 1;
                    state = 2;
                }
                else if(c=='(')
                {
                    state = 34;
                    forward = forward + 1;
                }
                else if(c==')')
                {
                    state = 35;
                    forward = forward + 1;
                }
                else if(c=='[')
                {
                    state = 36;
                    forward = forward + 1;
                }
                else if(c==']')
                {
                    state = 37;
                    forward = forward + 1;
                }
                else
                {
                    state = 100;
                }
                break;
            }
            case 2:
            {
                c=getNextCharacter();
                if((c>=65 && c<=90) || (c>=97 && c<=122) || (c=='_') || (c>=48 && c<=57))
                {
                    forward = forward + 1;
                    state = 2;
                }
                else
                {
                         // TOKENIZE HERE AND THEN SEND TO STATE 1
                      char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        if(start > (20))
                        {
                            state = 101;
                            forward--;
                            begin=forward;// THIS IS THE STATE FOR THE ERROR OF SIZE OF VARIABLE
                            break;
                        }
                      
                        searchKeywordTable(toSend);
                        char newToSend[100] = "";
                        state = 1;
                        
                        begin=forward;
                        beginBufferIndex=currentBufferIndex;
                        break;
                }
                break;
            }
            case 3:
            {
                c=getNextCharacter();
                //check to tokenize
                if((c-'0')<=9 && (c-'0'>=0))
                {
                    state=3;
                    forward=forward+1;
                }
                else if(c=='.')
                {
                    state=4;
                    forward=forward+1;
                }
                else if(!isalpha(c))
                {
                    // // TOKENIZE THIS
                    currToken.token =  NUM;
                    currToken.lineNo = lineNumber;
                     char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        int k=begin;
                        while(k!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][k];
                            toSend[start+1] = '\0';
                            start++;
                            if(k==BUFFER_SIZE-1)
                            {
                                k=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            k++;
                        }
                        copyLexeme(toSend);
                    // calculating value of integer --> start from "begin" and end at "forward-1"
                    int integerValue = 0;
                    
                    while(begin!=forward)
                    {
                        integerValue = integerValue*10 + (Buffer[beginBufferIndex][begin]-'0');

                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                            beginBufferIndex=1-beginBufferIndex;
                        }
                        else begin++;
                    }
                    currToken.valueOfInteger = integerValue;
                   struct tokenList* newNode=(struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                }
                else
                {
                    state=100;
                }
                break;
            }

            case 4:
            {
                c=getNextCharacter();
                if((c-'0')<=9 && (c-'0'>=0))
                {
                    state=5;
                    forward=forward+1;
                }
                else if(c=='.')
                {
                    forward--;
                    currToken.token =  NUM;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        int k=begin;
                        while(k!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][k];
                            toSend[start+1] = '\0';
                            start++;
                            if(k==BUFFER_SIZE-1)
                            {
                                k=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            k++;
                        }
                        copyLexeme(toSend);
                    // calculating value of integer --> start from "begin" and end at "forward-1"
                    int integerValue = 0;

                    while(begin!=forward)
                    {
                        integerValue = integerValue*10 + (Buffer[beginBufferIndex][begin]-'0');
                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                            beginBufferIndex=1-beginBufferIndex;
                        }
                        else begin++;
                    }
                    currToken.valueOfInteger = integerValue;
                    beginBufferIndex=currentBufferIndex;

                    // CREATING A NEW NODE && ADDING IT TO THE LINKEDLIST
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;

                    // tokenize  NUM till forward-1
                    state=1;
                    begin=forward;
                }
                else
                {
                    state=100;
                }
                break;
             }
            case 5:
            {
              c=getNextCharacter();
                 //check to tokenize
                if((c-'0')<=9 && (c-'0'>=0))
                {
                    state=5;
                    forward=forward+1;
                    break;
                }
                else if(c=='E'||c=='e')
                {
                    state=6;
                    forward=forward+1;
                    break;
                 }
                else 
                {
                    // TOKENIZE THIS
                    currToken.token =  RNUM;
                    currToken.lineNo = lineNumber;
                    
                        char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        int k=begin;
                        while(k!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][k];
                            toSend[start+1] = '\0';
                            start++;
                            if(k==BUFFER_SIZE-1)
                            {
                                k=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            k++;
                        }
                        copyLexeme(toSend);
                    float multiplier=10.0;
                    // calculating value of integer --> start from "begin" and end at "forward-1"
                    double realValue = 0.00;

                    while(Buffer[beginBufferIndex][begin]!='.')
                    {
                        realValue = realValue*10 + (Buffer[beginBufferIndex][begin]-'0');
                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                              beginBufferIndex=1-beginBufferIndex;
                        }
                        else begin++;
                    }

                        begin++;
                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                              beginBufferIndex=1-beginBufferIndex;
                        }
                    while(begin!=forward)
                    {
                        realValue = realValue + (1.0*(Buffer[beginBufferIndex][begin]-'0'))/multiplier;
                        multiplier*=10.0;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else begin++;

                    }

                    currToken.valueOfReal = realValue;
                    // CREATING A NEW NODE && ADDING IT TO THE LINKEDLIST
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;
                    currentIndex->next = newNode;
                    currentIndex = newNode;

                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
                }
            }
            case 6:
            {
              c=getNextCharacter();
                if((c-'0')<=9 && (c-'0'>=0))
                {
                    state=8;
                    forward=forward+1;
                    break;
                }
                else if(c=='+'||c=='-')
                {
                    state=7;
                    forward=forward+1;
                    break;
                }
                else
                {
                    state=100;
                    break;
                }
            }
            case 7:
            {
              c=getNextCharacter();
                if((c-'0')<=9 && (c-'0'>=0))
                {
                    state=8;
                    forward=forward+1;
                    break;
                }

                else
                {
                    state=100;
                    break;
                }
            }
            case 8:
            {
              c=getNextCharacter();

                if((c-'0')<=9 && (c-'0'>=0))
                {
                    state=8;
                    forward=forward+1;
                    break;
                }
                else
                {
                    currToken.token =  RNUM;
                    currToken.lineNo = lineNumber;
                   char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        int k=begin;
                        while(k!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][k];
                            toSend[start+1] = '\0';
                            start++;
                            if(k==BUFFER_SIZE-1)
                            {
                                k=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            k++;
                        }
                        copyLexeme(toSend);
                    float multiplier=10.0;
                    int realValue=0.0;

                    while(Buffer[beginBufferIndex][begin]!='.')
                    {
                        realValue = realValue*10 + (Buffer[beginBufferIndex][begin]-'0');
                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                            beginBufferIndex=1-beginBufferIndex;
                        }
                        else begin++;
                    }

                    // DEALING WITH '.'
                    if(begin==BUFFER_SIZE-1)
                    {
                        begin=0;
                        beginBufferIndex=1-beginBufferIndex;
                    }
                    else
                    begin++;
                  
                    // DEALING WITH THE FRACTIONAL PART
                    while(Buffer[beginBufferIndex][begin]!='E' && Buffer[beginBufferIndex][begin]!='e')
                    {
                        realValue = realValue + (1.0*(Buffer[beginBufferIndex][begin]-'0'))/multiplier;
                        //printf("The real value is %lf", realValue);
                        multiplier=multiplier*10.0;
                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                            beginBufferIndex=1-beginBufferIndex;
                        }
                        else
                        begin++;
                    }

                    if(begin==BUFFER_SIZE-1)
                    {
                        begin=0;
                        beginBufferIndex=1-beginBufferIndex;
                    }
                    else
                    begin++;

                    int ispos=1; //POSITIVE OR NEGATIVE
                    if(Buffer[beginBufferIndex][begin]=='+')
                    begin++;
                    else if(Buffer[beginBufferIndex][begin]=='-')
                    {
                        ispos=0;
                        begin++;
                    }

                    if(begin==BUFFER_SIZE)
                    {
                        begin=0;
                        beginBufferIndex=1-beginBufferIndex;
                    }

                    int factor=0;
                    int integerValue = 0;

                    while(begin!=forward)
                    {
                        integerValue = integerValue*10 + (Buffer[beginBufferIndex][begin]-'0');
                        if(begin==BUFFER_SIZE-1)
                        {
                            begin=0;
                            beginBufferIndex=1-beginBufferIndex;
                        }
                        else begin++;
                    }

                    if(ispos)
                    {
                        while(integerValue--)
                        realValue=realValue*10.0;
                    }
                    else
                    {
                        while(integerValue--)
                        realValue=realValue/10.0;
                    }

                    currToken.valueOfReal = realValue;
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;
                    currentIndex->next = newNode;
                    currentIndex = newNode;

                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
                }
            }
            case 9:
            {
              c=getNextCharacter();
                if(c=='.')
                {
                    state=10;
                    forward=forward+1;
                    break;
                }
                else
                {
                    state=100;
                    break;
                 }
            }
            case 10:
            {
                // RANGE FOR ARRAY --> for ex) 5..10 *TOKENIZE HERE*
                currToken.token =  RANGEOP;
                currToken.lineNo = lineNumber;
                char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                newNode->next = NULL;
                newNode->tokenValue = currToken;
                currentIndex->next = newNode;
                currentIndex = newNode;

                begin=forward;
                beginBufferIndex=currentBufferIndex;
                state=1;
                break;
            }
            case 11:
            {
                // TOKENIZE HERE  "+"
                currToken.token =  PLUS;
                currToken.lineNo = lineNumber;
                char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;
                    currentIndex->next = newNode;
                    currentIndex = newNode;
                begin=forward;
                beginBufferIndex=currentBufferIndex;
                state = 1;
                break;
            }
            case 12:
            {
                // TOKENIZE HERE "-"
                // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                currToken.token =  MINUS;
                currToken.lineNo = lineNumber;
                char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                begin=forward;
                beginBufferIndex=currentBufferIndex;
                state = 1;
                break;
            }
            case 13:
            {
                c=getNextCharacter();
                if(c=='*')
                {
                    state = 14;
                    forward = forward + 1;
                    begin=forward;
                }
                else
                {
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  MUL;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                }
                break;
            }
            case 14:
            {
                c=getNextCharacter();
                if(c=='\n')
                {
                    lineNumber++;
                }
                 if(c=='*')
                {

                    state = 15;
                    forward = forward + 1;
                }
                else
                {
                    state=14;
                    forward = forward + 1;
                }
                begin=begin+1;
                break;
            }
            case 15:
            {
                 c=getNextCharacter();
                 if(c=='\n')
                {
                    lineNumber++;
                }
                 if(c=='*')
                {

                    state = 16;
                    forward = forward + 1;
                }
                else
                {
                    state=14;
                    forward=forward+1;
                }
                begin++;
                break;
            }
            case 16:
            {
                state = 1;
                break;
            }
            case 17:
            {
                // for tokenizing  DIV
                // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                currToken.token =  DIV;
                currToken.lineNo = lineNumber;
                char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                begin=forward;
                beginBufferIndex=currentBufferIndex;
                state=1;
                break;
            }
            case 18:
            {
              c=getNextCharacter();
                if(c=='<')
                {
                    state = 19;
                    forward = forward + 1;
                }
                else if(c=='=')
                {
                    state = 21;
                    forward = forward + 1;
                }
                else
                {
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  LT;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                }
                break;
            }
            case 19:
            {
              c=getNextCharacter();
                if(c=='<')
                {
                    state = 20;
                    forward = forward + 1;
                }
                else
                {
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  DEF;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                }
                break;
            }
            case 20:
            {
              // for tokenizing  DRIVERDEF
                // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  DRIVERDEF;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
               state=1;
               break;
            }
            case 21:{
                 // for tokenizing  LE
                // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  LE;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
               state=1;
               break;
            }
            case 22:
            {
              c=getNextCharacter();
                if(c=='>')
                {
                    state = 23;
                    forward = forward + 1;
                }
                else if(c=='=')
                {
                    state = 25;
                    forward = forward + 1;
                }
                else
                {
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  GT;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                }
                break;
            }
            case 23:{
                c=getNextCharacter();
                 if(c=='>')
                {
                    state = 24;
                    forward = forward + 1;
                }
                else
                {
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  ENDDEF;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;

                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                }
                break;
            }
            case 24:
            {
                // for tokenizing  DRIVERENDF
                // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  DRIVERENDDEF;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;

                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                state =1;
                break;
            }
            case 25:
            {
                // for tokenizing  GE
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  GE;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        int k=begin-1;
                        while(k!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][k];
                            toSend[start+1] = '\0';
                            start++;
                            if(k==BUFFER_SIZE-1)
                            {
                                k=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            k++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                break;
            }
            case 26:
            {
               c=getNextCharacter();
                if(c=='!')
                {
                    state = 27;
                    forward = forward + 1;
                }

                break;

            }
            case 27:
            {
                 // for tokenizing  NE
                    // TOKENIZE HERE  --> YOU HAVE CHANGE THE BEGIN POINTER
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  NE;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;

                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state = 1;
                break;
            }
            case 28:
            {
                c=getNextCharacter();
                if(c=='=')
                {
                    state=29;
                    forward=forward+1;
                }
                else
                {
                    state=100;
                }
                break;
            }
            case 29:
            {       
                    //for tokenizing  EQ
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  EQ;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
            }
            case 30:
            {
                c=getNextCharacter();
               if(c=='=')
               {
                    forward=forward+1;
                    state=31;
               }
               else
               {
                    //TOKENIZE  COLON
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  COLON;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
               }
               break;
            }
            case 31:
            {
                //TOKENIZE  ASSIGNOP
                //forward=begin;
                // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  ASSIGNOP;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                state=1;
                break;
            }
            case 32:
            {
                    //TOKENIZE  COMMA
                    //change begin pointer
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  COMMA;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
            }
            case 33:
            {
                    //TOKENIZE  SEMICOL
                    //Change begin pointer
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  SEMICOL;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
            }
            case 34:
            {
                    //TOKENIZE  BO
                    //Change begin pointer
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  BO;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
            }
            case 35:
            {
                    //TOKENIZE  BC//
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  BC;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;

            }
            case 36:
            {
                    //TOKENIZE  SQBO//
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  SQBO;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;

            }
            case 37:

            {
                    //TOKENIZE  SQBC//
                    // struct tokenInfo currToken= (struct tokenInfo)malloc(sizeof(struct tokenInfo));
                    currToken.token =  SQBC;
                    currToken.lineNo = lineNumber;
                    char toSend[100] = "";
                        int len = 0;
                        int start = 0;
                        while(begin!=forward)
                        {
                            toSend[start] = Buffer[currentBufferIndex][begin];
                            toSend[start+1] = '\0';
                            start++;
                            if(begin==BUFFER_SIZE-1)
                            {
                                begin=0;
                                beginBufferIndex=1-beginBufferIndex;
                            }
                            else
                            begin++;
                        }
                        copyLexeme(toSend);
                    struct tokenList* newNode= (struct tokenList*)malloc(sizeof(struct tokenList));
                    newNode->next = NULL;
                    newNode->tokenValue = currToken;

                    currentIndex->next = newNode;
                    currentIndex = newNode;
                    begin=forward;
                    beginBufferIndex=currentBufferIndex;
                    state=1;
                    break;
            }
            case 100:
                {
                    printf("%d Lexical Error! Illegal Character\n",lineNumber);
                    state=1;
                    // forward++;
                    begin=forward;
                    // forward++;
                    break;
                }
            case 101:
                {
                    printf("%d Error! Identifier size limit exceeded\n",lineNumber);
                    state=1;
                    forward++;
                    begin=forward;
                    break;
                }
        }
        // END OF SWITCH STATEMENT
    }
    // END OF WHILE LOOP
}
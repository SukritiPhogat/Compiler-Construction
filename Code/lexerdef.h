/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#ifndef LEXERDEF_H
#define LEXERDEF_H
#include<stdio.h>
#define BUFFER_SIZE 16384
#define sizeofdummy 10
char c;
char* Buffer[2];
char* hashEnum[140];

enum SYMBOL
{
    //TERMINALS
    ID=1, NUM, RNUM, RANGEOP, PLUS, MINUS, MUL, DIV, LT, DEF, DRIVERDEF, LE, GT, ENDDEF, DRIVERENDDEF, GE, NE, EQ, COLON, ASSIGNOP, COMMA, SEMICOL,
    BO, BC, SQBO, SQBC, AND, OR, TRUE, FALSE, INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, 
    WITH, PARAMETERS, TAKES, INPUT, RETURNS, FOR, IN, SWITCH, CASE, BREAK, DEFAULT, WHILE,

    DOLLAR,//STACK END MARKER
    EPSILON,//EPSILON

    //NON TERMINALS
    start, program, factor, moduleDeclarations, otherModules, driverModule, moduleDeclaration, module, moduleDef, input_plist, ret, output_plist,
    new_input_plist, dataType, new_output_plist, type, conditionalStmt, range_arrays, index_arr, statements, statement, ioStmt, simpleStmt, declareStmt,
    iterativeStmt, var_print, boolConstt, new_P1, new_index, assignmentStmt, moduleReuseStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, expression, eee,
    sign, optional, actual_para_list, new_actual_para_list, idList, new_idList, arithmeticOrBooleanExpr, unary, unary_op, new_NT, arithmeticExpr,
    var_id_num, anyTerm, new_Term, logicalOp, new_Term2, relationalOp, newarithmeticExpr, op1, term, op2, term_new, new_factor, newExpr, arrExpr, arrTerm,
    arr_N4, arrFactor, arr_N5, caseStmts, def, value, new_caseStmt, range_for_loop, index_for_loop, sign_for_loop, new_index_for_loop, kkk, n_11,parameter
 };

struct tokenInfo
{
    enum SYMBOL token;
    int lineNo;
    unsigned int valueOfInteger;
    double valueOfReal;
    char nameOfID[20];
    // ADD MORE IF ANY
};

struct tokenList
{
    struct tokenList* next;
    struct tokenInfo tokenValue;
};

struct tokenList* dummy;
struct tokenList* currentIndex;

struct keylist
{
    int num_tokens;
    char *token_list[40];     //array of words corresponding to token
    enum SYMBOL enum_list[40]; //make an array of enum corresponding to token        (***YUGAL***)
};

#endif 
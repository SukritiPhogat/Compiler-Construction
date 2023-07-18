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
#include"ASTdef.h"
#include"AST.h"
#include"parserdef.h"
#include"lexerdef.h"
#include"symbolTable.h"
#include"symbolTabledef.h"
#include"semanticAnalyzer.h"
#include"semanticAnalyzerdef.h"

struct Type initializeType()
{
    struct Type returnType;
    returnType.type=no_type;
    returnType.array_type=no_type;
    return returnType;
}
// struct ASTnode* ASTroot;
// struct symbolTable* st;
// void sendRootAndTable(struct ASTnode* root,struct symbolTable* st1)
// {
//     ASTroot=root;
//     st=st1;
// }


struct Type typeCheck(struct ASTnode* root)
{
    struct Type returnType=initializeType();

    if(root==NULL)
    {
        return returnType;
    }

    int rootLabel=root->label;

    switch(rootLabel)
    {
        case RANGEOP:
        {
            int l=typeCheck(root->children).type;
            int r=typeCheck(root->children->next).type;
            if(l!=NUM || r!=NUM)
            {
                printf("Semantic error in line number %d - Range indices are not integer type.\n",root->ASTtokenInfo.lineNo);
            }
            break;
        }
        case caseStmts:
        case def:
        case statements:
        case program:
        case driverModule:
        case otherModules: 
        {
            struct ASTnode* temp=root->children;
            while(temp)
            {
                int x=typeCheck(temp).type;
                temp=temp->next;
            }
            break;
        }
          
        case WHILE:
        {
            enum TYPE controlExp=typeCheck(root->children).type;
            enum TYPE stmtType=typeCheck(root->children->next).type;
            if(controlExp!=boolean)
                printf("Semantic error in line number %d - Control expression of WHILE not of boolean type.\n",root->ASTtokenInfo.lineNo);
            break;
        }
        case FOR:
        {
            enum TYPE varType=typeCheck(root->children).type;
            enum TYPE rangeType=typeCheck(root->children->next).type;
            enum TYPE stmtType=typeCheck(root->children->next).type;
            if(varType!=NUM)
                printf("Semantic error in line number %d - Control variable of FOR not of integer type.\n",root->ASTtokenInfo.lineNo);
            break;

        }
        case unary:
        {
            enum TYPE x=typeCheck(root->children->next).type;
            if(x==integer || x==real)
                returnType.type=x;
            else
            {
             printf("Semantic error in line number %d - Operand to unary operator is not of numeric type.\n",root->children->ASTtokenInfo.lineNo);   
             returnType.type=integer;
            }
            break;
        }
        case relationalOp:
        {
            enum TYPE l=typeCheck(root->children).type;
            enum TYPE r=typeCheck(root->children->next).type;
            if((l==real && r==real) || (l==integer && r==integer))
                returnType.type=boolean;
            else 
            {
                returnType.type=boolean;
                printf("Semantic error in line number %d - Operands to relational operator are not of numeric type.\n",root->ASTtokenInfo.lineNo);  
            }
            break;
        }
        case logicalOp:
        {
            enum TYPE l=typeCheck(root->children).type;
            enum TYPE r=typeCheck(root->children->next).type;
            if(l!=boolean || r!=boolean)
                printf("Semantic error in line number %d - Operands to logical operator are not of boolean type.\n",root->ASTtokenInfo.lineNo);
            returnType.type=boolean;
            break;
        }
        case ARRAY:
        {
            enum TYPE x=typeCheck(root->children->next).type;
            break;
        }
        case PRINT:
        case GET_VALUE:
        {
            enum TYPE x=typeCheck(root->children).type;
            if(x!=integer && x!=real && x!=boolean)
                printf("Semantic error in line number %d - Argument to IO statement is not of printable type.\n",root->ASTtokenInfo.lineNo);
            break;
        }
        case assignmentStmt:
        {
            enum TYPE l=typeCheck(root->children).type;
            enum TYPE r=typeCheck(root->children->next).type;
            //if(l!=r)
              // printf("Semantic error in line number %d - Type mismatch in assignment statement.\n",root->ASTtokenInfo.lineNo);
            break;
        }
         case module://module -> ID input_plist ret stmts END
        {
            enum TYPE stmtsType=typeCheck(root->children->next->next->next).type;
            break;
        }
        case op1:
        {
            enum TYPE l=typeCheck(root->children).type;
            enum TYPE r=typeCheck(root->children->next).type;

            if((l==real && r==real) || (l==integer && r==integer))
                returnType.type=l;
            else returnType.type=integer;

            if(l!=r)
                printf("Semantic error in line number %d - op1(+ or -) can't be applied on operands of different type.\n",root->ASTtokenInfo.lineNo);
            break;
        }
        case op2:
        {
            enum TYPE l=typeCheck(root->children).type;
            enum TYPE r=typeCheck(root->children->next).type;

            if(root->ASTtokenInfo.token==MUL)
            {
                if((l==real && r==real) || (l==integer && r==integer))
                    returnType.type=l;
                else 
                    returnType.type=integer;

                if(l!=r)
                    printf("Semantic error in line number %d - op MUL can't be applied on operands of different type.\n",root->ASTtokenInfo.lineNo);
            }
            else //DIV
            {
                returnType.type=real;
                if((l!=real && l!=integer) || (r!=real && r!=integer))
                    printf("Semantic error in line number %d - Invalid operand types to DIV.\n",root->ASTtokenInfo.lineNo);
            }
            break;
        }
        case SWITCH:
        {
            enum TYPE idType=typeCheck(root->children).type;
            if(idType==boolean)
            {
                if(root->children->next->next !=NULL) //default should be NULL
                    printf("Semantic error in SWITCH - If id is boolean, deafault should be NULL.\n",root->ASTtokenInfo.lineNo);

                struct ASTnode* temp=(struct ASTnode*)malloc(sizeof(struct ASTnode));
                temp=root->children->next->children;//caseStmts

                while(temp!=NULL)
                {
                    int x= typeCheck(temp->children).type;
                    if(x!=boolean)
                        printf("Semantic error in CASE - case value type mismatch with SWITCH id type.\n",root->ASTtokenInfo.lineNo);
                    int y=typeCheck(temp->children->next).type;
                    temp=temp->next;
                }
            }
            else if(idType==integer)
            {
                struct ASTnode* temp=(struct ASTnode*)malloc(sizeof(struct ASTnode));
                temp=root->children->next->children;//caseStmts

                while(temp!=NULL)
                {
                    int x= typeCheck(temp->children).type;
                    if(x!=integer)
                        printf("Semantic error in CASE - case value type mismatch with SWITCH id type.\n",root->ASTtokenInfo.lineNo);
                    int y=typeCheck(temp->children->next).type;
                    temp=temp->next;
                }

                enum TYPE d=typeCheck(root->children->next->next).type;
            }
            else
            {
                printf("Semantic error in line number %d - Invalid identifier type in SWITCH.\n",root->ASTtokenInfo.lineNo);
                enum TYPE x=typeCheck(root->children->next).type;//caseStmts
                enum TYPE y=typeCheck(root->children->next->next).type;//def
            }
            break;
        }
        // Check Bounds ---------- as well
        case arrExpr:
        {
            returnType.type=typeCheck(root->children).type;

            enum TYPE idx=typeCheck(root->children->next).type;
            if(idx!=integer)
                printf("Semantic error in line number %d - Array index is not of integer type.\n",root->children->ASTtokenInfo.lineNo);
            
            break;
        }    







        case ID:
        {
            struct symbolTable* temp;
            temp=(struct symbolTable*)malloc(sizeof(struct symbolTable));
            temp=root->scopedST;


            int flag=0;
            while(temp!=NULL)
            {
                struct entry* x=findInST(temp, root->ASTtokenInfo.nameOfID);
                if(x!=NULL) flag=1;
                temp=temp->parent;
                if(flag)
                {
                    enum TYPE temp_type=x->type.type;
                    if(temp_type != array)
                        returnType.type=temp_type;
                    else returnType.type=x->type.array_type;
                    break;
                }
            }
            if(flag==0)
                returnType.type=integer;
        }














        case NUM:
        {
            returnType.type=integer;
            break;
        }
        case RNUM:
        {
            returnType.type=real;
            break;
        }
        case TRUE:
        case FALSE:
        {
            returnType.type=boolean;
            break;
        }
        case MINUS:
        case PLUS:
        case INTEGER:
        case REAL:
        case BOOLEAN:
        case START:
        case END:
        case DECLARE:
        case moduleDeclarations:
        case parameter:
        case input_plist:
        case ret:
        case moduleReuseStmt:
        case optional:
        case PARAMETERS: 
        case CASE:
        default:
        {
            break;
        }}
        printf("%s %s\n",hashEnum[rootLabel],returnType.type);
        return returnType;
}
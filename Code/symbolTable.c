/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"lexer.h"
#include"lexerdef.h"
#include"parser.h"
#include"parserdef.h"
#include"AST.h"
#include"ASTdef.h"
#include"symbolTable.h"
#include"symbolTabledef.h"
#include"semanticAnalyzer.h"
#include"semanticAnalyzerdef.h"

struct ASTnode* curr;
void sendASTroot(struct ASTnode* curr1)
{
    curr = curr1;
}
void initializeST(struct symbolTable* st)
{
    //set all to NULL
    // st = (struct entry*)(malloc(sizeof(struct entry) * symbolTableSize));
    for(int i=0;i<symbolTableSize;i++)
        st->hash_index[i] = NULL;

    st->stName=NULL;
    st->next=NULL;
    st->parent=NULL;
    st->children=NULL;
}

int hashIndexST(char* name)
{
    int sum=0;
    int i=0;
    while(name[i]!='\0')
    {
        sum=sum+name[i];
        i++;
    }
    return sum % symbolTableSize;
}

void insertInST(struct symbolTable* st, struct entry* newEntry)
{
    //Find hash index and insert at head or end of corresponding index
    //printf("Inserting entry %s in symbol table %s\n",newEntry->name,st->stName);
    int index=hashIndexST(newEntry->name);
    // printf("%d\n",index);
    struct entry* temp = (struct entry*) malloc(sizeof(struct entry*));
    temp=st->hash_index[index];

    if(temp==NULL)
    {
        st->hash_index[index]=newEntry;
        newEntry->next=NULL;
        return;
    }
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=newEntry;
    newEntry->next=NULL;    

    return;
}



void updateInST(struct entry* currEntry, struct entry* newEntry)
{
    // currEntry->name = newEntry->name;
    // TYPE CHECKING --> CONFIRM WITH SUKRITI
    //  printf("Updating entry %s \n",newEntry->name);
    currEntry->valueIfInt = newEntry->valueIfInt;
    currEntry->valueIfReal = newEntry->valueIfReal;
    currEntry->valueIfBool = newEntry->valueIfBool;
    
    // currEntry->offset = newEntry->offset;
}

void addChildST(struct symbolTable* par, struct symbolTable* child)
{
    if(child==NULL) return;
    // printf("Adding child %s to %s-------------------------\n",child->stName,par->stName);
    // printf("Adding child - %s to %s\n",hashEnum[child->stName],hashEnum[par->stName]);
    if(par->children==NULL)
    {
        child->parent=par;
        par->children=child;
        child->next=NULL;
        return;
    }
    //ELSE
    struct symbolTable* temp=par->children;
    while(temp->next !=NULL)
    {
        temp=temp->next;
    }
    temp->next=child;
    child->parent=par;
    child->next=NULL;
    return;
}

struct entry *findInST(struct symbolTable* st,char* nameTofind)
{
    // printf("Finding entry %s in symbol table %s\n",nameTofind,st->stName);
    int index=hashIndexST(nameTofind);
    struct entry* temp = st->hash_index[index];
    while(temp!=NULL && strcmp(nameTofind,temp->name))
        temp=temp->next;
    return temp;
}




void deleteST(struct symbolTable* st)
{
    int currIndex = 0;
    while(currIndex<symbolTableSize)
    {
        struct entry* currEntry = st->hash_index[currIndex];
        struct entry* prevEntry = NULL;
        while(currEntry!=NULL)
        {
            prevEntry = currEntry;
            currEntry = currEntry->next;
            free(prevEntry);
        }

        currIndex++;
    }
}

struct entry* makeEntry(struct ASTnode* astnode, struct Type* curType, struct symbolTable *st, int curWidth)
{
    // printf("Making entry %s in symbol table %s\n",nameOfID,st->stName);
    astnode->scopedST=st;
    char * nameOfID=astnode->ASTtokenInfo.nameOfID;
    struct entry* newEntry = (struct entry*)malloc(sizeof(struct entry));
    newEntry->name = nameOfID;
    newEntry->type.type = curType->type;

    if(curType->type == array)
    {
        newEntry->type.array_type = curType->array_type;
        newEntry->type.end_idx= curType->end_idx;
        newEntry->type.start_idx=curType->start_idx;
        
    }

    newEntry->width = curWidth;
    newEntry->parentST = st;

    // UPDATE THE SCOPE -- SAMYAK ASK SUKRITI
    newEntry->next = NULL;
    return newEntry;
}

void symbolTableImplementation(struct symbolTable* st, struct ASTnode* root)
{
   // printf("start....\n");
    if(root==NULL)
        return;

    int rootLabel=root->label;
   // printf("%s\n",hashEnum[rootLabel]);

    switch(rootLabel)
    {
        case RANGEOP: 
        case caseStmts:
        case SWITCH:    
        case def:
        case unary:
        case op2:
        case op1:
        case relationalOp:
        case logicalOp:
        case arrExpr:
        case optional: 
        case assignmentStmt:
        case PARAMETERS:
        case PRINT:
        case GET_VALUE:
        case program:
        case otherModules:
        case input_plist:
        case ret:
        case statements:
        {
            struct ASTnode* temp= root->children;
            while(temp!=NULL)
            {
                symbolTableImplementation(st,temp);
                temp=temp->next;
            }
            return;
            break;
        }
        case moduleReuseStmt:
        {
            struct ASTnode* temp= root->children->next;
            while(temp!=NULL)
            {
                symbolTableImplementation(st,temp);
                temp=temp->next;
            }
            return;
            break;
        }

        case FOR:
        case CASE:
        case WHILE:
        {
            struct symbolTable* childTable= (struct symbolTable*)malloc(sizeof(struct symbolTable));
            initializeST(childTable);
            childTable->stName=hashEnum[root->ASTtokenInfo.token];
            addChildST(st,childTable);
            
            childTable->nestingLevel=st->nestingLevel+1;
            childTable->scope_start=root->ASTtokenInfo.lineNo;
            struct ASTnode* temp= root->children;
            while(temp!=NULL)
            {
                symbolTableImplementation(childTable,temp);
                temp=temp->next;
            }
            return;
            break;
        }
        case driverModule:
        {
            struct symbolTable* newTable= (struct symbolTable*)malloc(sizeof(struct symbolTable));
            initializeST(newTable);
            newTable->stName = root->ASTtokenInfo.nameOfID;
            addChildST(st,newTable);

            newTable->nestingLevel=st->nestingLevel+1;
            newTable->scope_start=root->ASTtokenInfo.lineNo;
            
            symbolTableImplementation(newTable,root->children);
            return;
            break;
        }
        case module:
        {
            struct symbolTable* newTable= (struct symbolTable*)malloc(sizeof(struct symbolTable));
            initializeST(newTable);
            newTable->stName = root->children->ASTtokenInfo.nameOfID;
            addChildST(st,newTable);

            newTable->nestingLevel=0;
            newTable->scope_start=root->ASTtokenInfo.lineNo;

            struct symbolTable* nested= (struct symbolTable*)malloc(sizeof(struct symbolTable));
            initializeST(nested);
            nested->stName = root->children->ASTtokenInfo.nameOfID;
            addChildST(newTable,nested);

            nested->nestingLevel=st->nestingLevel+1;
            nested->scope_start=root->ASTtokenInfo.lineNo;
            
            //ID-0 inp-1 ret-2 stmts-3 end-4
            symbolTableImplementation(newTable,root->children->next);
            symbolTableImplementation(newTable,root->children->next->next);

            symbolTableImplementation(nested,root->children->next->next->next);
            symbolTableImplementation(newTable,root->children->next->next->next->next);
            symbolTableImplementation(nested,root->children->next->next->next->next);


            // struct ASTnode* temp= root->children->next;
            // while(temp!=NULL)
            // {
            //     symbolTableImplementation(nested,temp);
            //     temp=temp->next;
            // }
            return;
            break;
        }

        case parameter:
        case DECLARE:
        {
            struct ASTnode* temp= root->children;
            struct Type* curType;
            curType= (struct Type*)malloc(sizeof(struct Type) );
            // struct Type* curArrayType;
            int curWidth=0;
            int curArrayWidth=0;
            if(temp->label==INTEGER)
            {
                curType->type=integer;
                curWidth=2;
            }
            if(temp->label==REAL)
            {
                curType->type=real;
                curWidth=4;
            }
            if(temp->label==BOOLEAN)
            {
                curType->type=boolean;
                curWidth=1;
            }
            if(temp->label==ARRAY)
            {
                curType->type=array;
                struct ASTnode* temp1= temp->children;
                 if(temp1->label==INTEGER)
                {
                    curType->array_type=integer;
                    curArrayWidth=2;
                }
                if(temp1->label==REAL)
                 {
                    curType->array_type=real;
                    curArrayWidth=4;
                }
                 if(temp1->label==BOOLEAN)
                {
                    curType->array_type=boolean;
                    curArrayWidth=1;
                }

                temp1=temp1->next;
                temp1=temp1->children;
                if(temp1->label !=NUM || temp1->next->label!=NUM)
                {
                    curType->isDynamic=1;
                }
                else
                {
                    curType->start_idx=temp1->ASTtokenInfo.valueOfInteger;
                    temp1=temp1->next;
                    curType->end_idx=temp1->ASTtokenInfo.valueOfInteger;
                // curType->start_idx=startIdx;
                // curType->end_idx=endIdx;
                }
                curWidth=curArrayWidth*(curType->end_idx - curType->start_idx+1)+1;
            }
    
            temp=temp->next;
            while(temp!=NULL)
            {
                if(findInST(st,temp->ASTtokenInfo.nameOfID))
                {
                    printf("Semantic error in line number %d - Redeclarartion of identifier %s.\n",temp->ASTtokenInfo.lineNo,temp->ASTtokenInfo.nameOfID);
                }
                else
                {
                    struct entry* newEntry=makeEntry(temp, curType,st,curWidth);
                    insertInST(st,newEntry);
                    if(temp->parent->label==parameter)
                        newEntry->entryNestingLevel=0;
                    else 
                        newEntry->entryNestingLevel=st->nestingLevel;
                }
                temp=temp->next;
            }
            return;
            break;
        }
       
        case ID:
        {

            struct symbolTable* temp;
            temp=(struct symbolTable*)malloc(sizeof(struct symbolTable));
            temp=st;
            int flag=0;
            while(temp!=NULL)
            {
                if(findInST(temp, root->ASTtokenInfo.nameOfID)!=NULL)
                {
                    flag=1;
                }
                temp=temp->parent;
                if(flag)
                    break;
            }

            if(!flag) printf("Semantic error in line number %d - Identifier %s must be declared before use.\n",root->ASTtokenInfo.lineNo,root->ASTtokenInfo.nameOfID);;
            return;
            break;
        }
        

        // SAMYAK
        case END:
        {
            st->scope_end=root->ASTtokenInfo.lineNo;
            return;
            break;
        }

        case REAL:
        case INTEGER:
        case TRUE:
        case FALSE:
        case START:
        case RNUM:
        case PLUS:
        case MINUS:
        case NUM:
        case BOOLEAN:
        case moduleDeclarations:
        {
            return;
        }
        default:
        {
            return;
        }
    }
}

void initializeHashType()
{
    hashType[integer] = "integer";
    hashType[real] = "real";
    hashType[boolean] = "boolean";
    hashType[array] = "array";
    hashType[function] = "function";
    hashType[no_type] = "no_type";
    hashType[error] = "error";
}
void printSymbolTable(struct symbolTable* st,int offset)
{
    


    for(int i=0;i<symbolTableSize;i++)
    {
        struct entry* currEntry=st->hash_index[i];

        while(currEntry!=NULL)
        {
            // if(currEntry->type.type == 31)
            // {
            //     currEntry=currEntry->next;
            //     continue;
                
            // }

            // currEntry->type.type = currEntry->type.type - 31;

        //    printf("%s \t %s \t %d \n",currEntry->name,st->stName);
            
            if(currEntry->type.type==array)
         {   
            if(currEntry->type.isDynamic==1)
            printf("%-15s\t %-20s [%-3d-%-3d]\t              %-15s\t  yes \t     dynamic \t      [%d-%d] \t      %-7d %-10d %d \n",currEntry->name,st->stName,st->scope_start,st->scope_end,hashType[currEntry->type.array_type], currEntry->type.start_idx , currEntry->type.end_idx, currEntry->width, offset, currEntry->parentST->nestingLevel);

            else             printf("%-15s\t %-20s [%-3d-%-3d]\t              %-15s\t  yes \t      static \t      [%d-%d] \t      %-7d %-10d %d \n",currEntry->name,st->stName,st->scope_start,st->scope_end,hashType[currEntry->type.array_type], currEntry->type.start_idx , currEntry->type.end_idx, currEntry->width, offset, currEntry->parentST->nestingLevel);

        }
            else
            printf("%-15s\t %-20s [%-3d-%-3d]\t              %-15s\t  no \t      * \t      * \t      %-7d %-10d %d \n",currEntry->name,st->stName,st->scope_start,st->scope_end,hashType[currEntry->type.type], currEntry->width, offset, currEntry->parentST->nestingLevel);
            // printf("type of element enum is %d /n", currEntry->type.type);

            offset=offset+currEntry->width;
            currEntry=currEntry->next;
            
        }
    }
    

    struct symbolTable* tempst=st->children;
    
    while(tempst!=NULL)
    {
        printSymbolTable(tempst,offset);
        tempst=tempst->next;
    }
    
}

void printArrayCase(struct symbolTable* st)
{
    for(int i=0;i<symbolTableSize;i++)
    {
        struct entry* currEntry=st->hash_index[i];

        while(currEntry!=NULL)
        {
            // if(currEntry->type.type == 31)
            // {
            //     currEntry=currEntry->next;
            //     continue;
                
            // }

            // currEntry->type.type = currEntry->type.type - 31;

        //    printf("%s \t %s \t %d \n",currEntry->name,st->stName);
            
            if(currEntry->type.type==array)
            printf("%-20s  [%-3d-%-3d] \t          %-15s\t** \t      [%-3d-%-3d]       %-15s\n",st->stName, st->scope_start,st->scope_end,currEntry->name, currEntry->type.start_idx , currEntry->type.end_idx,hashType[currEntry->type.array_type]);
            
            currEntry=currEntry->next;
            
        }
    }
    

    struct symbolTable* tempst=st->children;
    
    while(tempst!=NULL)
    {
        printArrayCase(tempst);
        tempst=tempst->next;
    }
}
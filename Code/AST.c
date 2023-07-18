/* 
ID: 2020A7PS0002P 			     Name: Yugal Joshi
ID: 2020A7PS0054P			     Name: Kartik Kumar Pawar
ID:	2020A7PS0071P			     Name: Sukriti Phogat
ID:	2020A7PS0104P 		         Name: Samyak Bakliwal
ID: 2020A7PS0988P			     Name: Vraj Patel
*/
#include<stdio.h>
#include<stdlib.h>
#include"lexer.h"
#include"lexerdef.h"
#include"parser.h"
#include"parserdef.h"
#include"AST.h"
#include"ASTdef.h"

// struct ASTnode
// {
//     enum SYMBOL label;
//     struct tokenInfo ASTtokenInfo;
//     struct ASTnode* parent;
//     struct ASTnode* children;
//     struct ASTnode* next;
// };
struct ASTnode* newASTnode(enum SYMBOL ASTlabel)
{
    // printf("Making new AST node %s\n",hashEnum[ASTlabel]);
    struct ASTnode* newNode = (struct ASTnode*)malloc(sizeof(struct ASTnode));

    newNode->label = ASTlabel;
    newNode->children = NULL;   
    newNode->next = NULL;
    newNode->parent = NULL;
    newNode->scopedST=NULL;
   // printf("Done\n");
    return newNode;
}


//Copy tokenInfo and set label= name of token of Parse Tree node
struct ASTnode* makeLeaf(struct TreeNode* node)
{
    // printf("Making LEAF node %s\n",hashEnum[node->NodeTokenInfo.token]);
    struct ASTnode* newNode = (struct ASTnode*)malloc(sizeof(struct ASTnode));

    newNode->label = node->NodeTokenInfo.token;
    newNode->children=NULL;
    newNode->next = NULL;
    newNode->parent = NULL;

    newNode->ASTtokenInfo=node->NodeTokenInfo;
    newNode->scopedST=NULL;
    //printf("Done\n");
    return newNode;
}

//Add to parent->children
void addChild(struct ASTnode* par, struct ASTnode* child)
{
    if(child==NULL) return;

    // printf("Adding child - %s to %s\n",hashEnum[child->label],hashEnum[par->label]);
    if(par->children==NULL)
    {
        child->parent=par;
        par->children=child;
        child->next=NULL;
        return;
    }
    //ELSE
    struct ASTnode*temp=par->children;
    while(temp->next !=NULL)
    {
        temp=temp->next;
    }
    temp->next=child;
    child->parent=par;
    child->next=NULL;
    return;
}


//Head of linked list is given(child), Add all its elements as children of parent.
void addChildList(struct ASTnode* par, struct ASTnode* child)
{
    if(child==NULL) return;
    // printf("Adding childList to %s : ",hashEnum[par->label]);

    if(par->children==NULL)
    {
        // printf("If--- ");
        par->children=child;
        while(child!=NULL)
        {
            // printf(" %s",hashEnum[child->label]);
            child->parent=par;
            child=child->next;
        }
        // printf("\n");
        return;
    }
    //ELSE
    // printf("E/lse--- ");
    struct ASTnode*temp=par->children;
    while(temp->next !=NULL)
    {
        temp=temp->next;
    }
    temp->next=child;
     while(child!=NULL)
    {
        // printf(" %s",hashEnum[child->label]);

         child->parent=par;
        child=child->next;
    }
    // printf("\n");
        return;
}

//Linked List is used in passing inherited attributes, not in tree.
//It will be done by the addChildList function
struct ASTnode* insertAtHead(struct ASTnode* head, struct ASTnode* nextNode)
{
    if(head==NULL)
        return nextNode;
    nextNode->next=head;
    return nextNode;
}
struct ASTnode* insertAtEnd(struct ASTnode* head, struct ASTnode* nextNode)
{
    if(head==NULL)
        return nextNode;
    struct ASTnode* temp=head;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=nextNode;
    return head;
}

void deleteParseTree(struct TreeNode* root){
    if(root==NULL)
    return;

    for(int i=0;root->child[i]!=NULL;i++)
    {
        deleteParseTree(root->child[i]);
    }
    free(root);
}

struct ASTnode* buildAST(struct TreeNode* root,struct ASTnode* inherited)
{
    int rule=root->ruleNum;
    rule=rule+1; // To convert from 0-based to 1-based indexing
    //printf("Rule %d\n",rule);
    switch(rule)
    {
      case 2:
            {
                struct ASTnode* node=newASTnode(program);
                struct ASTnode* mds=newASTnode(moduleDeclarations);
                addChildList(mds,buildAST(root->child[0],NULL));
                addChild(node,mds);

                struct ASTnode* omds=newASTnode(otherModules);
                addChildList(omds,buildAST(root->child[1],NULL));
                addChild(node,omds);
                addChild(node,buildAST(root->child[2],NULL));

                struct ASTnode* mds2=newASTnode(otherModules);
                addChildList(mds2,buildAST(root->child[3],NULL));
                addChild(node,mds2);

                return node;
                break;
            }
        case 5:
            {
                return makeLeaf(root->child[2]);
                break;
            }
        case 3:
        case 6:
        case 27:
            {
                return insertAtHead(buildAST(root->child[1],NULL),buildAST(root->child[0],NULL));
                break;
            }
        case 8://driverModule DRIVERDEF DRIVER PROGRAM DRIVERENDDEF moduleDef
            {
                struct ASTnode* node=newASTnode(driverModule);
                node->ASTtokenInfo=root->child[1]->NodeTokenInfo;
                addChild(node,buildAST(root->child[4],NULL));
                addChild(node,makeLeaf(root->child[4]->child[2]));
                return node;
                break;
            }
        case 9://module DEF MODULE ID ENDDEF TAKES INPUT SQBO input_plist SQBC SEMICOL ret moduleDef
            {
                struct ASTnode* node=newASTnode(module);
                node->ASTtokenInfo=root->child[1]->NodeTokenInfo;
                addChild(node,makeLeaf(root->child[2]));

                struct ASTnode* input_node=newASTnode(input_plist);
                addChildList(input_node,buildAST(root->child[7],NULL));
                addChild(node,input_node);

                addChild(node,buildAST(root->child[10],NULL));
                addChild(node,buildAST(root->child[11],NULL));
                addChild(node,makeLeaf(root->child[11]->child[2]));
                return node;
                break;
            }
        case 10:
            {
                struct ASTnode* node= newASTnode(ret);
                addChildList(node,buildAST(root->child[2],NULL));
                return node;
                break;
            }
        case 11:
            {
                return newASTnode(ret);
                break;
            }
        case 12:
        case 15: //output_plist ID COLON type new_output_plist
            {
                struct ASTnode* node=newASTnode(parameter);
                addChild(node,buildAST(root->child[2],NULL));
                addChild(node,makeLeaf(root->child[0]));

                return insertAtHead(buildAST(root->child[3],NULL),node);
                break;
            }
        case 13: //new_input_plist COMMA ID COLON dataType new_input_plist
        case 16: //new_output_plist COMMA ID COLON type new_output_plist
            {
                struct ASTnode* node=newASTnode(parameter);
                addChild(node,buildAST(root->child[3],NULL));
                addChild(node,makeLeaf(root->child[1]));

                return insertAtHead(buildAST(root->child[4],NULL),node);
                break;
            }
        case 18:
            {
                struct ASTnode* dataType=newASTnode(ARRAY);
                addChild(dataType,buildAST(root->child[5],NULL));
                addChild(dataType,buildAST(root->child[2],NULL));
                return dataType;
                break;
            }
        case 26://moduleDef START statements END
            {
                struct ASTnode* stmts=newASTnode(statements);
                addChildList(stmts,buildAST(root->child[1],NULL));
                return stmts;
                break;
            }
        case 34:
            {
                struct ASTnode* ioStmt_node=newASTnode(GET_VALUE);
                ioStmt_node->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(ioStmt_node,makeLeaf(root->child[2]));
                return ioStmt_node;
                break;
            }
        case 35:
            {
                struct ASTnode* ioStmt_node=newASTnode(PRINT);
                ioStmt_node->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(ioStmt_node,(struct ASTnode*)buildAST(root->child[2],NULL));
                return ioStmt_node;
                break;
            }
        case 38:
        case 46:
        case 64:
        case 69:
        case 98:
            {
                struct ASTnode* inh_id=makeLeaf(root->child[0]);
                return buildAST(root->child[1],inh_id);
                break;
            }
        case 42:
        case 65:
        case 99:
            {
                struct ASTnode* node=newASTnode(arrExpr);
                addChild(node,inherited);
                addChild(node,(struct ASTnode*)buildAST(root->child[1],NULL));
                return node;
                break;
            }
        case 57://moduleReuseStmt optional USE MODULE ID WITH PARAMETERS actual_para_list SEMICOL
            {
                struct ASTnode* node=newASTnode(moduleReuseStmt);
                addChild(node,makeLeaf(root->child[3]));

                struct ASTnode* option=newASTnode(optional);
                addChildList(option,(struct ASTnode*)buildAST(root->child[0],NULL));
                addChild(node,option);

                struct ASTnode* params=newASTnode(PARAMETERS);
                addChildList(params,(struct ASTnode*)buildAST(root->child[6],NULL));
                addChild(node,params);

                return node;
                break;
            }
        case 58://actual_para_list-> sign kkk n_11
            {
                struct ASTnode* sign=buildAST(root->child[0],NULL);
                struct ASTnode* kkk=buildAST(root->child[1],NULL);
                struct ASTnode* n_11_inh;

                if(sign==NULL)
                    n_11_inh=kkk;
                else
                {
                    n_11_inh=newASTnode(unary);
                    addChild(n_11_inh,sign);
                    addChild(n_11_inh,kkk);
                }
                return buildAST(root->child[2],n_11_inh);
                break;
            }
        case 59://n_11-> COMMA sign kkk n_11
            {
                struct ASTnode* sign=buildAST(root->child[1],NULL);
                struct ASTnode* kkk=buildAST(root->child[2],NULL);
                struct ASTnode* node;

                if(sign==NULL)
                    node=kkk;
                else
                {
                    node=newASTnode(unary);
                    addChild(node,sign);
                    addChild(node,kkk);
                }
                struct ASTnode* n_11_inh=insertAtEnd(inherited,node);
                return buildAST(root->child[3],n_11_inh);
                break;
            }
        case 70:
            {
                return buildAST(root->child[2], insertAtEnd(inherited,makeLeaf(root->child[1])));
                break;
            }
        case 47:
        case 48:
            {
                return buildAST(root->child[0],inherited);
                break;
            }
        case 49://lvalueIDStmt ASSIGNOP expression SEMICOL
            {
                struct ASTnode* node=newASTnode(assignmentStmt);
                node->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(node,inherited);
                addChild(node,(struct ASTnode*)buildAST(root->child[1],NULL));
                return node;
                break;
            }
        case 50://lvalueARRStmt SQBO eee SQBC ASSIGNOP expression SEMICOL
            {
                struct ASTnode* node=newASTnode(assignmentStmt);
                node->ASTtokenInfo=root->child[3]->NodeTokenInfo;
                struct ASTnode* array_node=newASTnode(arrExpr);
                addChild(array_node,inherited);
                addChild(array_node,(struct ASTnode*)buildAST(root->child[1],NULL));

                addChild(node,array_node);
                addChild(node,(struct ASTnode*)buildAST(root->child[4],NULL));

                return node;
                break;
            }
        case 51: //index_arr-> sign new_index
        case 140:
            {
                struct ASTnode* sign=buildAST(root->child[0],NULL);
                if(sign==NULL)
                    return buildAST(root->child[1],NULL);
                else
                {
                    struct ASTnode* node=newASTnode(unary);
                    addChild(node,sign);
                    addChild(node,(struct ASTnode*)buildAST(root->child[1],NULL));
                    return node;
                }
                break;
            }
        case 74:
        case 82: //arithmeticOrBooleanExpr -> anyTerm new_Term
        case 85:
        case 88:
        case 91:
        case 101:
        case 105:
        case 108:
            {
                return buildAST(root->child[1],buildAST(root->child[0],NULL));
                break;
            }
        case 83:
            {
                struct ASTnode* new_Term_inh=newASTnode(logicalOp);
                //new_Term_inh->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                new_Term_inh->ASTtokenInfo=buildAST(root->child[0],NULL)->ASTtokenInfo;
                addChild(new_Term_inh,inherited);
                addChild(new_Term_inh,(struct ASTnode*)buildAST(root->child[1],NULL));

                return buildAST(root->child[2],new_Term_inh);
                break;
            }
        case 86:
            {
                struct ASTnode* new_Term_inh=newASTnode(relationalOp);
                new_Term_inh->ASTtokenInfo=buildAST(root->child[0],NULL)->ASTtokenInfo;
                //new_Term_inh->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(new_Term_inh,inherited);
                addChild(new_Term_inh,(struct ASTnode*)buildAST(root->child[1],NULL));

                return buildAST(root->child[2],new_Term_inh);
                break;
            }
        case 89:
        case 106://arr_N4 op1 arrTerm arr_N4
            {
                struct ASTnode* new_Term_inh=newASTnode(op1);
                
                new_Term_inh->ASTtokenInfo=buildAST(root->child[0],NULL)->ASTtokenInfo;

                addChild(new_Term_inh,inherited);
                addChild(new_Term_inh,(struct ASTnode*)buildAST(root->child[1],NULL));

                return buildAST(root->child[2],new_Term_inh);
                break;
            }
        case 92:
        case 109:
            {
                struct ASTnode* new_Term_inh=newASTnode(op2);
                new_Term_inh->ASTtokenInfo=buildAST(root->child[0],NULL)->ASTtokenInfo;
                //new_Term_inh->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(new_Term_inh,inherited);
                addChild(new_Term_inh,(struct ASTnode*)buildAST(root->child[1],NULL));

                return buildAST(root->child[2],new_Term_inh);
                break;
            }
        case 67:
        case 94:
        case 114:
            {
                return buildAST(root->child[1],NULL);
                break;
            }
        case 77:
        case 103:
            {
                struct ASTnode* newExpr=newASTnode(unary);
                addChild(newExpr,inherited);
                addChild(newExpr,(struct ASTnode*)buildAST(root->child[1],NULL));
                return newExpr;
                break;
            }
        case 78:
        case 104:
            {
                struct ASTnode* newExpr=newASTnode(unary);
                addChild(newExpr,inherited);
                addChild(newExpr,(struct ASTnode*)buildAST(root->child[0],NULL));
                return newExpr;
                break;
            }
        case 127:
            {
                struct ASTnode* dec=newASTnode(DECLARE);
                addChild(dec,(struct ASTnode*)buildAST(root->child[3],NULL));
                addChildList(dec,(struct ASTnode*)buildAST(root->child[1],NULL));
                return dec;
                break;
            }
        case 128://conditionalStmt SWITCH BO ID BC START caseStmts def END
            {
                struct ASTnode* switch_stmt=newASTnode(SWITCH);
                switch_stmt->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(switch_stmt,makeLeaf(root->child[2]));

                struct ASTnode* case_stmts=newASTnode(caseStmts);
                addChildList(case_stmts,buildAST(root->child[5],NULL));
                addChild(switch_stmt,case_stmts);

                addChild(switch_stmt,buildAST(root->child[6],NULL));
                return switch_stmt;
                break;
            }
        case 129://caseStmts CASE value COLON statements BREAK SEMICOL new_caseStmt
        case 130:
            {
                struct ASTnode* node=newASTnode(CASE);
                node->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(node,buildAST(root->child[1],NULL));

                struct ASTnode* stmts=newASTnode(statements);
                addChildList(stmts,buildAST(root->child[3],NULL));
                addChild(node,stmts);

                //Break
                struct ASTnode* b=makeLeaf(root->child[4]);
                b->label=END;
                addChild(node,b);

                return insertAtHead(buildAST(root->child[6],NULL),node);
                break;
            }
        case 135://def DEFAULT COLON statements BREAK SEMICOL
            {
                struct ASTnode* d=newASTnode(def);
                d->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                struct ASTnode* stmts=newASTnode(statements);
                addChildList(stmts,buildAST(root->child[2],NULL));
                addChild(d,stmts);

                //Break
                struct ASTnode* b=makeLeaf(root->child[3]);
                b->label=END;
                addChild(d,b);
                
                return d;
                break;
            }
        case 136:
            {
                return newASTnode(def);
                break;
            }
        case 137://iterativeStmt FOR BO ID IN range_for_loop BC START statements END
            {
                struct ASTnode* iterative=newASTnode(FOR);
                iterative->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(iterative,makeLeaf(root->child[6]));
                addChild(iterative,makeLeaf(root->child[2]));
                addChild(iterative,buildAST(root->child[4],NULL));

                struct ASTnode* stmts=newASTnode(statements);
                addChildList(stmts,buildAST(root->child[7],NULL));
                addChild(iterative,stmts);
                addChild(iterative,makeLeaf(root->child[8]));
                return iterative;
                break;
            }
        case 138://iterativeStmt WHILE BO arithmeticOrBooleanExpr BC START statements END
            {
                struct ASTnode* iterative=newASTnode(WHILE);
                iterative->ASTtokenInfo=root->child[0]->NodeTokenInfo;
                addChild(iterative,makeLeaf(root->child[4]));
                addChild(iterative,buildAST(root->child[2],NULL));

                struct ASTnode* stmts=newASTnode(statements);
                addChildList(stmts,buildAST(root->child[5],NULL));
                addChild(iterative,stmts);
                addChild(iterative,makeLeaf(root->child[6]));
                return iterative;
                break;
            }
        case 22:
        case 139:
            {
                struct ASTnode* range=newASTnode(RANGEOP);
                range->ASTtokenInfo=root->child[1]->NodeTokenInfo;
                addChild(range,buildAST(root->child[0],NULL));
                addChild(range,buildAST(root->child[2],NULL));
                return range;
                break;
            }

        case 19: //dataType -> INTEGER
        case 20:
        case 21:

        case 23:
        case 24:
        case 25:

        case 36:
        case 37:

        case 39:
        case 40:

        case 52:
        case 53:
        case 54:
        case 55:

        case 61:
        case 62:

        case 75:
        case 76:

        case 79:
        case 80:
        case 81:

        case 95:
        case 96:

        case 111:
        case 112:

        case 115:
        case 116:
        case 117:
        case 118:
        case 119:
        case 120:
        case 121:
        case 122:
        case 123:
        case 124:
        case 125:
        case 126:

        case 132:
        case 133:
        case 134:

        case 141:
            {
                return makeLeaf(root->child[0]);
                break;
            }
        case 4:
        case 7:
        case 14:
        case 17:
        case 28: //statements -> EPSILON
        case 56:
        case 68:
        case 131:
            {
                return NULL;
                break;
            }
        case 1:
        case 29: // statement->ioStmt
        case 30:
        case 31:
        case 32:
        case 33:
        case 41:
        case 44:
        case 45:
        case 63:
        case 72:
        case 73:
        case 97:
        case 102:
        case 113:
            {
                return buildAST(root->child[0],NULL);
                break;
            }
        case 43:
        case 60:
        case 66:
        case 71: //new_idList-> EPSILON
        case 84:
        case 87:
        case 90:
        case 93:
        case 100:
        case 107:
        case 110:
            {
                return inherited;
                break;
            }
        default:
            {
                return NULL;
                break;
            }
    }
}



void helper(struct ASTnode* temp)
{
    if(temp->label == NUM)
    {
        // printf()
        // *flag = 1;
        printf("%-15d  ",temp->ASTtokenInfo.valueOfInteger);
    }
    else if(temp->label == RNUM)
    {
        // *flag = 1;
        printf("%-15f  ", temp->ASTtokenInfo.valueOfReal);
    }
    else if(temp->label == ID)
    {
        // *flag = 1;
        printf("%-15s  ",temp->ASTtokenInfo.nameOfID);
    }
    else
    {
        // *flag = 1;
        printf("%-15s  ", hashEnum[temp->label]);
    }

}



int countOfAST = 0;
int sizeOfAST = 0;

int getSizeOfAST()
{
    return sizeOfAST;
}
int getCountOfAST()
{
    return countOfAST;
}

void printPreorderAST(struct ASTnode* root)
{
    if(root==NULL || root->children==NULL)
        return;
    // int flag = 0;
    helper(root);
    sizeOfAST += sizeof(struct ASTnode);
    countOfAST++;

    

    // if(flag == 1)
    printf(" ->   ");

    struct ASTnode *temp=root->children;
    while(temp!=NULL)
    {
        
        helper(temp);
        sizeOfAST += sizeof(struct ASTnode);
        countOfAST++;
        temp=temp->next;
    }
    printf("\n");

    temp=root->children;
    while(temp!=NULL)
    {
        printPreorderAST(temp);
        temp=temp->next;
    }
    return;
}

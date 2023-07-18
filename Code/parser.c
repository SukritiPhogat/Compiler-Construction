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
#include"lexerdef.h"
#include"parser.h"
#include"parserdef.h"

FILE* fin; //Text file having grammar rules

//---- HELPER FUNCTIONS ----



int findEnum(char *input)
{
    for(int i=1;i<140 && hashEnum[i]!=NULL;i++)
        if(!strcmp(input,hashEnum[i]))
            return i;
    return -1; // NOT FOUND
}

int contains(int *a,int n)
{
    for(int i=0;a[i]!=-1;i++)
        if(a[i]==n)
            return 1;
    return 0;
}

int isTerminal(int x)
{
    return x<59;
}

int nonTerminalIndex(int nt)
{
    return nt-59;
}

int terminalIndex(int t)
{
    if(t==58) return 56;
    else return t-1;
}

// STACK-TREE Structure and functions

struct tokenList* curr;
void sendList(struct tokenList* curr1)
{
    curr = curr1->next;
}

struct StackTreeNode* initialize_TreeStack(int array_capacity)
{
    struct StackTreeNode* stack = (struct StackTreeNode*)malloc(sizeof(struct StackTreeNode ));
    stack->array =(struct TreeNode**) malloc(array_capacity* sizeof(struct TreeNode));
    stack->size = 0;
    stack->top = -1;
    return stack;
}

void pushTreeStack(struct TreeNode* value_to_push,struct StackTreeNode* stack)
{
    if((stack->size)>=MAX_SIZE){
        printf("Stack Overflow occurred.\n");
        return ;
    }
    stack->top++;
    stack->array[stack->top] = value_to_push;
    stack->size++;
}

void popTreeStack(struct StackTreeNode* stack)
{
    stack->size--;
    stack->top--;
    // printf("Pop executed successfully\n");
}

int emptyTreeStack(struct StackTreeNode* stack){
    if(stack->size==0) return 1;
    else return 0;
}

struct TreeNode* topTreeStack(struct StackTreeNode* stack)
{   
    return stack->array[stack->top];
}

// Functions for printing

void printFirstAndFollow()
{
    printf("\n\n----First Sets osf NonTerminals----\n\n");
    for(int i=0;i<nonTerminalCount;i++)
    {
        printf("%s : ",hashEnum[i+59]);
        for(int j=0;first[i][j]!=-1;j++)
            printf("%s ",hashEnum[first[i][j]]);
        printf("\n");
    }
    printf("\n\n----Follow Sets of NonTerminals----\n\n");
    for(int i=0;i<nonTerminalCount;i++)
    {
        printf("%s : ",hashEnum[i+59]);
        for(int j=0;follow[i][j]!=-1;j++)
            printf("%s ",hashEnum[follow[i][j]]);
        printf("\n");
    }
}

void printParseTable()
{
    printf("\n\n----Printing Parse Table, Value denotes Rule number, -1 means no such rule----\n\n");
    for(int i=0;i<nonTerminalCount;i++)
    {
        printf("%s ",hashEnum[i+59]);
        for(int j=0;j<terminalCount+1;j++)
            printf("%d ",parseTable[i][j]);
        printf("\n");
    }
}


//---- FUNCTIONS FOR READING GRAMMAR, FIRST-FOLLOW CALCULATION AND PARSE TABLE FILLING ----

void populateGrammar()
{
    //Initialize to -1
    memset(grammar,-1,sizeof (grammar));

    //Open File
    fin = fopen("Grammar.txt","r");
    if(fin == NULL)
    {
        printf("Can't open file");
        return;
    }
    //Read Line by Line
    char line[200];
    memset(line,' ',sizeof(line));
    for(int i=0;fgets(line,sizeof(line),fin);i++)
    {
        char* mysymbol ;
        mysymbol= strtok(line," ");
        //Use strtok for extracting Terminals or Non terminals
        for(int j=0;mysymbol != NULL;j++)
           {
               int len = strlen(mysymbol);
                if(mysymbol[len-1] == '\n' || mysymbol[len-1] == ' ' )
                mysymbol[len-1]= 0;
               grammar[i][j]=findEnum(mysymbol);//enumValue(mysymbol);
               mysymbol = strtok(NULL," ");
            }
        memset(line,' ',sizeof(line));
    }
    fclose(fin);
}

// First set calculation for given non terminal nt
void calculateFirst(int nt)
{
    int ntIdx =nonTerminalIndex(nt);
    if(isFirstCalculated[ntIdx]) return;

    int index=0;
    for(int i=0;i<ruleCount;i++)  //i=rule Number
    {
        if(grammar[i][0]!=nt)
            continue; //Rule doesnt start with given nt, ignore

        for(int j=1; grammar[i][j]!=-1;j++)
        {
            int curr=grammar[i][j];
            if(isTerminal(curr) || curr==EPSILON)//is terminal or eps
            {
                if(!contains(first[ntIdx],curr))
                first[ntIdx][index++]=curr;
                break;
            }
            int currIdx=nonTerminalIndex(curr);
            if(!isFirstCalculated[currIdx])
                calculateFirst(curr);

            int haveEpsilon = 0;
            for(int copy = 0; first[currIdx][copy]!=-1;copy++)
            {
                if(first[currIdx][copy]==EPSILON)
                    haveEpsilon = 1;
                else if(!contains(first[ntIdx],first[currIdx][copy]))   //copy elements of firstOfNext to first if !contains that element,
                    {
                        first[ntIdx][index++] = first[currIdx][copy];
                    }
            }

            if(haveEpsilon==0)
            break;

            if(haveEpsilon==1 && grammar[i][j+1]==-1) // IF YOU HAVE EPSILON AND YOU ARE THE LAST PERSON THEN INSERT EPSILON
                first[ntIdx][index++] = EPSILON;
            }
    }//End of i(rule) for loop
    isFirstCalculated[ntIdx]=1;
}//End of function

// Follow set calculation for given non terminal nt
void calculateFollow(int nt)
{
    if(nt==0) return;
   
    int ntIdx=nonTerminalIndex(nt);
    if(isFollowCalculated[ntIdx])
        return;

    int index=0;
    if(nt==59) //start symbol
    {
        follow[ntIdx][0]=DOLLAR;
        isFollowCalculated[ntIdx]=1;
        index++;
    }

    //Search for given nt on rhs
    for(int i=0;i<ruleCount;i++)
        for(int j=1;grammar[i][j]!=-1;j++)
        {
            if(grammar[i][j]!=nt) continue;
            else  if(grammar[i][j+1]==-1 && nt!=grammar[i][0]) // IF YOU YOU ARE THE LAST PERSON THEN INCLUDE FOLLOW
            {
                int x=grammar[i][0];
                int xIdx=nonTerminalIndex(x);
                if(!isFollowCalculated[xIdx])
                    calculateFollow(x);
                for(int copy = 0; follow[xIdx][copy]!=-1;copy++)
                {
                    int t=follow[xIdx][copy];//terminal
                    if(t==0) break;
                    if(!contains(follow[ntIdx],t))
                        follow[ntIdx][index++]=t;
                }
                continue;
            }

            int k;
            for(k=j+1;grammar[i][k]!=-1;k++)
            {
                int curr=grammar[i][k];
                if(isTerminal(curr))//is terminal
                {
                    if(curr==0) break;
                    if(!contains(follow[ntIdx],curr))
                        follow[ntIdx][index++]=curr;
                        break;
                }
                else//non terminal, find its first
                {
                    int haveEpsilon = 0;
                    int currIdx=nonTerminalIndex(curr);
                    for(int copy = 0; first[currIdx][copy]!=-1;copy++)
                    {
                        int t=first[currIdx][copy];
                        if(t==0) break;
                        if(t==EPSILON)
                            haveEpsilon = 1;
                        else if(!contains(follow[ntIdx],t))   //copy elements if !contains that element,
                            follow[ntIdx][index++] = t;
                    }
                    if(haveEpsilon==0)
                        break;
                    if(haveEpsilon==1 && grammar[i][k+1]==-1 && nt!=grammar[i][0]) // IF YOU HAVE EPSILON AND YOU ARE THE LAST PERSON THEN INCLUDE FOLLOW
                    {
                        int x=grammar[i][0];
                        int xIdx=nonTerminalIndex(x);
                        if(!isFollowCalculated[xIdx])
                            calculateFollow(x);
                        for(int copy = 0; follow[xIdx][copy]!=-1;copy++)
                        {
                            int t=follow[xIdx][copy];//terminal
                            if(!contains(follow[ntIdx],t))
                                follow[ntIdx][index++]=t;
                        }
                    }
                }
            }
    }
    isFollowCalculated[ntIdx]=1;
}//End of function

void findFirstAndFollow()
{
   //Initialize first and follow to -1
    memset(first,-1,sizeof (first));
    memset(follow,-1,sizeof (follow));
    memset(isFirstCalculated,0,sizeof (isFirstCalculated));
    memset(isFollowCalculated,0,sizeof (isFollowCalculated));
    
    // call the above functions for each non terminal
   for(int i=0;i<nonTerminalCount;i++)
        if(!isFirstCalculated[i])
            calculateFirst(i+59);
   
   
   for(int i=0;i<nonTerminalCount;i++)
        if(!isFollowCalculated[i])
            calculateFollow(i+59);
   
}

void fillParseTable()
{
    memset(parseTable,-1,sizeof (parseTable));

    for(int i=0;i<ruleCount;i++)
    {
        int nt=grammar[i][0];
        int ntIdx=nonTerminalIndex(nt);
        for(int j=1;grammar[i][j]!=-1;j++)
        {
            int curr=grammar[i][j];
            if(curr==EPSILON)
            {
                //Include Follow
                for(int copy = 0; follow[ntIdx][copy]!=-1;copy++)
                    {
                        int t=follow[ntIdx][copy];//terminal,follow cant't have epsilon so no need to check
                        int tIdx=terminalIndex(t);
                        if(parseTable[ntIdx][tIdx]!=-1)
                            printf("------------NOT LL 1 %d\n--------------",i);
                        parseTable[ntIdx][tIdx]=i;
                    }
                break;
            }
            else if(isTerminal(curr))//terminal
            {
                int currIdx=terminalIndex(curr);
                if(parseTable[ntIdx][currIdx]!=-1)
                            printf("------------NOT LL 1 %d\n--------------",i);
                parseTable[ntIdx][currIdx]=i;//i=rule number
                break;
            }
            else
            {
                //Find first of curr
                int haveEpsilon = 0;
                int currIdx=nonTerminalIndex(curr);
                for(int copy = 0; first[currIdx][copy]!=-1;copy++)
                {
                    int t=first[currIdx][copy];//terminal
                    int tIdx=terminalIndex(t);
                    if(t==EPSILON)
                        haveEpsilon = 1;
                    else
                    {
                         if(parseTable[ntIdx][tIdx]!=-1)
                            printf("------------NOT LL 1 %d\n--------------",i);
                        parseTable[ntIdx][tIdx]=i;
                    }
                }
                if(haveEpsilon==0)
                    break;
                if(haveEpsilon==1 && grammar[i][j+1]==-1) // IF YOU HAVE EPSILON AND YOU ARE THE LAST PERSON THEN INCLUDE FOLLOW
                {
                    for(int copy = 0; follow[ntIdx][copy]!=-1;copy++)
                    {
                        int t=follow[ntIdx][copy];//terminal
                        int tIdx=terminalIndex(t);
                        if(parseTable[ntIdx][tIdx]!=-1)
                            printf("------------NOT LL 1 %d\n--------------",i);
                        parseTable[ntIdx][tIdx]=i;
                    }
                }
            }
        }//End of j for loop
    }//End of i for loop
}//End of function

// STACK TREE IMPLEMENTATION FUNCTIONS

struct TreeNode* startTreeNode;
FILE *outfile;
void StackandParseTreeImplementation(int flag) 
{
    // if(flag == 1)
    // return;
    // printf("You have entered the tree function\n");
    startTreeNode = (struct TreeNode*)(malloc(sizeof(struct TreeNode)));
    startTreeNode->NodeTokenInfo.token = start;
    
    outfile = fopen("outfile.txt", "w"); // write only
    if(outfile==NULL)
    {
        printf("could not open file \n");

    }
  
    struct StackTreeNode* parseTreeStack = initialize_TreeStack(MAX_SIZE); // INITIALIZE THIS IN THE MAIN FUNCTION
    // printf("stack is intiliazed\n");
    struct tokenList* temp = curr;
    struct tokenList* prev = curr;
    struct tokenList* head = curr;

    while(temp!= NULL)
    {
        prev = temp;
        temp=temp->next;
    }
    struct tokenInfo dollarToken;
    dollarToken.token =  DOLLAR;
    dollarToken.lineNo = 0;
    struct tokenList* dollarListNode= (struct tokenList*)malloc(sizeof(struct tokenList));
    dollarListNode->next = NULL;
    dollarListNode->tokenValue = dollarToken;
    prev->next = dollarListNode;

    //INITIALIZE THE STACKS IN THE MAIN FUNCTION

    struct TreeNode* dollar = (struct TreeNode*)(malloc(sizeof(struct TreeNode)));
    dollar->NodeTokenInfo.token = DOLLAR;
    pushTreeStack(dollar, parseTreeStack); // ASSUMING DOLLAR IS ALSO A TOKEN
    pushTreeStack(startTreeNode, parseTreeStack);

    // printf("pushed in stack\n");
    // printf(" curr is %s and stack is %s \n", curr->tokenValue.nameOfID, topTreeStack(parseTreeStack)->NodeTokenInfo.nameOfID);

    while(curr!=NULL  && emptyTreeStack(parseTreeStack)==0)
    {
        // CONDITIONS FOR ERROR
        // printf("entered the loop \n");
        struct TreeNode* currNode = topTreeStack(parseTreeStack);
        int row = currNode->NodeTokenInfo.token;
        int col = curr->tokenValue.token;
        row = nonTerminalIndex(row);
        col = terminalIndex(col);

        if(emptyTreeStack(parseTreeStack)==0 && curr!=NULL && isTerminal(topTreeStack(parseTreeStack)->NodeTokenInfo.token)==1 && curr->tokenValue.token != topTreeStack(parseTreeStack)->NodeTokenInfo.token ) // CHANGE THIS LINE --> FEED IN THE VALUE OF TERMINAL NUMBERS ACCORDINGLY
        {
                printf("SYNTAX ERROR at line %d\n", curr->tokenValue.lineNo);
                popTreeStack(parseTreeStack);
                // continue;
                return;

                // sendList(curr);
                // break;
        }
        else if(parseTable[row][col]>=0)
        {
            int ruleNumber = parseTable[row][col];
            currNode->ruleNum=ruleNumber;
            struct TreeNode** children = (struct TreeNode**)malloc(1000*sizeof(struct TreeNode));
            int size = 0;
            
            for(int i=1;grammar[ruleNumber][i]!=-1;i++)
            {
                struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                newNode->NodeTokenInfo.token = grammar[ruleNumber][i];
                newNode->NodeTokenInfo.lineNo=0;

                char ran[20]="---";
                int i=0;
                for(;i<strlen(ran);i++)
                {
                    newNode->NodeTokenInfo.nameOfID[i]=ran[i];
                }
                newNode->NodeTokenInfo.nameOfID[i] = '\0';
                newNode->parent = currNode;
                children[size++] = newNode;
            }

            currNode->child = children;
            currNode->child[size] = NULL;
            popTreeStack(parseTreeStack);
            
            for(int i=size-1;i>=0;i--)
            {
                struct TreeNode* temp = currNode->child[i];
                if(temp->NodeTokenInfo.token != EPSILON)
                pushTreeStack(temp, parseTreeStack);
            }

            while(emptyTreeStack(parseTreeStack)==0 && curr!=NULL &&  curr->tokenValue.token == topTreeStack(parseTreeStack)->NodeTokenInfo.token)
            {
                topTreeStack(parseTreeStack)->NodeTokenInfo.lineNo=curr->tokenValue.lineNo;
                 int i=0;
                 topTreeStack(parseTreeStack)->NodeTokenInfo.valueOfInteger=curr->tokenValue.valueOfInteger;
                 topTreeStack(parseTreeStack)->NodeTokenInfo.valueOfReal=curr->tokenValue.valueOfReal;
                for(;i<strlen(curr->tokenValue.nameOfID);i++)
                {
                    topTreeStack(parseTreeStack)->NodeTokenInfo.nameOfID[i]=curr->tokenValue.nameOfID[i];
                }
                topTreeStack(parseTreeStack)->NodeTokenInfo.nameOfID[i] = '\0';
                sendList(curr);
                popTreeStack(parseTreeStack);
            }

            // 10th March code changes x-x-x-x-x-x-x-x
            
            if(emptyTreeStack(parseTreeStack)==0 && curr!=NULL && isTerminal(topTreeStack(parseTreeStack)->NodeTokenInfo.token)==1 && curr->tokenValue.token != topTreeStack(parseTreeStack)->NodeTokenInfo.token ) // CHANGE THIS LINE --> FEED IN THE VALUE OF TERMINAL NUMBERS ACCORDINGLY
            {
                printf("SYNTAX ERROR at line  %d \n", curr->tokenValue.lineNo);
                // flag = 1;
                return;
            }
        }
        else
        {
            // flag = 1;/

        //    printf("SYNTAX ERROR at line %d , and curr is: %s , and stack is %s \n", curr->tokenValue.lineNo, hashEnum[curr->tokenValue.token], hashEnum[topTreeStack(parseTreeStack)->NodeTokenInfo.token]);
          printf("SYNTAX ERROR at line  %d \n", curr->tokenValue.lineNo);











          
           return;
        //    for(int i=0;i<ruleCount && grammar[i][0]!=-1;i++)
        //    {
        //         if(nonTerminalIndex(grammar[i][0]==row )&& grammar[i][1]==EPSILON)
        //         {yes=1;
        //         break;}
        //    }
        //    if(yes)
        //    {
        //     popTreeStack(parseTreeStack);
        //     break;
        //    }
        //    if(contains(follow[row],col)==0)
        //    {    
        //         sendList(curr);
        //         col = terminalIndex(curr->tokenValue.token);
        //         if(curr==NULL)
        //         break;
        //    }
        //    struct TreeNode** children = (struct TreeNode**)malloc(1000*sizeof(struct TreeNode));
        //     int size = 0;
        //     currNode->child = children;
        //     currNode->child[size] = NULL;
        //    if(curr==NULL)
        //    {

        //     printTreeInorder(startTreeNode);
        //     return;
        //    }
        //    popTreeStack(parseTreeStack);
        }
    }

    if(emptyTreeStack(parseTreeStack)==0 && curr==NULL)
    {
        printf(" %d SYNTACTICAL ERROR !!!  \n", topTreeStack(parseTreeStack)->NodeTokenInfo.lineNo);
        return;
    }
    else if(emptyTreeStack(parseTreeStack)==1 && curr!=NULL)
    {
        // printf("Stack is empty\n");
        printf(" %d SYNTACTICAL ERROR !!!  \n", curr->tokenValue.lineNo);
        return;
    }
    printf("NOTE: LINE NUMBER = 0 FOR NON-TERMINALS \n \n");
    printf("NAME \t\t\t CURRENT_NODE \t\t LINE_NUMBER \t VALUE_IF_NUM \n");

    // free(parseTreeStack);
    curr = head;
    // int flag = 0;
    if(flag == 1)
    printTreeInorder(startTreeNode);
}

 struct TreeNode* getRoot()
{
    return startTreeNode;
}


int countOfTreeNodes = 0;
int sizeOfTree = 0;



int getSizeOfTree()
{
    return sizeOfTree;
}
int getCountOfTree()
{
    return countOfTreeNodes;
}

void printTreeInorder(struct TreeNode* startTreeNode)
{
    if(startTreeNode==NULL)
    {
        printf("Error in printing \n");
        return;
    }
    if(startTreeNode->NodeTokenInfo.token >=1 && startTreeNode->NodeTokenInfo.token <=58)
    {
        countOfTreeNodes++;
        sizeOfTree += sizeof(struct TreeNode);
        if(startTreeNode->NodeTokenInfo.token == NUM)
        printf("%s %30s \t %10d \t %20d\n",startTreeNode->NodeTokenInfo.nameOfID, hashEnum[startTreeNode->NodeTokenInfo.token], startTreeNode->NodeTokenInfo.lineNo,startTreeNode->NodeTokenInfo.valueOfInteger );
        else if(startTreeNode->NodeTokenInfo.token == RNUM)
        printf("%s %30s \t %10d \t %20lf\n",startTreeNode->NodeTokenInfo.nameOfID, hashEnum[startTreeNode->NodeTokenInfo.token], startTreeNode->NodeTokenInfo.lineNo,startTreeNode->NodeTokenInfo.valueOfReal );
        else
        printf("%s %30s \t %20d \t \n",startTreeNode->NodeTokenInfo.nameOfID, hashEnum[startTreeNode->NodeTokenInfo.token], startTreeNode->NodeTokenInfo.lineNo);
        // lexeme CurrentNode lineno tokenName valueIfNumber  parentNodeSymbol isLeafNode(yes/no) NodeSymbol, 
        return;
        
    }

    struct TreeNode** children = startTreeNode->child;
    int i=1;
    printTreeInorder(startTreeNode->child[0]);
    countOfTreeNodes++;
    sizeOfTree += sizeof(struct TreeNode);
    
        if(startTreeNode->NodeTokenInfo.token == NUM)
        printf("%s %30s \t %10d \t %20d\n",startTreeNode->NodeTokenInfo.nameOfID, hashEnum[startTreeNode->NodeTokenInfo.token], startTreeNode->NodeTokenInfo.lineNo,startTreeNode->NodeTokenInfo.valueOfInteger );
        else if(startTreeNode->NodeTokenInfo.token == RNUM)
        printf( "%s %30s \t %10d \t %20lf\n",startTreeNode->NodeTokenInfo.nameOfID, hashEnum[startTreeNode->NodeTokenInfo.token], startTreeNode->NodeTokenInfo.lineNo,startTreeNode->NodeTokenInfo.valueOfReal );
        else
        printf("%s %30s \t %20d \t \n",startTreeNode->NodeTokenInfo.nameOfID, hashEnum[startTreeNode->NodeTokenInfo.token], startTreeNode->NodeTokenInfo.lineNo);

    while(startTreeNode->child[i]!=NULL)
    {
        printTreeInorder(startTreeNode->child[i]);
        i++;
    }

    if(startTreeNode->child[i]!=NULL)
    {
        printTreeInorder(startTreeNode->child[i]);
    }   
}
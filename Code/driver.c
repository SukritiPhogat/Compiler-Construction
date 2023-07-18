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
#include<time.h>
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
struct tokenList* dummy;
struct tokenList* currentIndex;
FILE *fp;

void removeComments(char* file)
{
    FILE* srcFile;
    srcFile = fopen(file, "r");
    char nextFileChar;
    char tempChar;
    nextFileChar=fgetc(srcFile);
    
// A comment starts with ** and ends with **. 
    while(nextFileChar!=EOF){
        tempChar=nextFileChar;
    nextFileChar=fgetc(srcFile);
            
        if((tempChar=='*') && (nextFileChar=='*')){
            nextFileChar=fgetc(srcFile);
            if(nextFileChar=='\n')printf("\n");
            tempChar=fgetc(srcFile);
            if(tempChar=='\n')printf("\n");
            
            //keep on incrementing file pointer until end of comments reached;
            while((tempChar!='*') || (nextFileChar!='*')){
                tempChar=nextFileChar;
                nextFileChar=fgetc(srcFile);
                if(nextFileChar=='\n')printf("\n");    
            }

                nextFileChar=fgetc(srcFile);
                tempChar=nextFileChar;
                nextFileChar=fgetc(srcFile);
        }
        if((tempChar=='*') && (nextFileChar=='*'))continue;
        printf("%c",tempChar);
    }
}

void printTokens()
{
    printf("Line Number     Lexeme      Token Name\n");
    struct tokenList* temp=dummy->next;
    while(temp!= NULL)
    {
        enum SYMBOL temp2=temp->tokenValue.token;
        
        if(temp->tokenValue.lineNo)
        {
        printf("%d %20s %14s \n",temp->tokenValue.lineNo,temp->tokenValue.nameOfID,hashEnum[temp2]);             
        } 
        temp=temp->next;
    }
}

int main(/*int argc, char *argv[] */)
{
//      if(argc < 2){  
//       printf("No argument passed through command line.\n");  
//    }  
//    else{  
//       printf("First argument is: %s\n", argv[1]);  
//    }  
    int loop=1;
    int input;

     char file[100];
    printf("Enter File Location: ");
    gets(file);
    fp = fopen(file, "a+");
    if(fp==NULL)
    {
      printf("OOPS! File can't be opened.");
      return 0;
    }


    // char file[100];
    // // file=argv[1];
    // printf("Enter File Location: ");
    // geek(fp,0,SEEK_SET);
    // if(fpets(argv[1]);
    // fp = fopen(file, "a+");
    // fp==NULL)
    // {
    //   printf("OOPS! File can't be opened.");
    //   return 0;
    // }
    
     dummy  = (struct tokenList*)malloc(sizeofdummy);
    currentIndex = dummy;
    //Lexer
    initializeBuffer(fp);
   initializeHashTable();
    initializeHashEnum();
    getNextToken();
    fclose(fp);
    struct ASTnode* astroot;
                struct symbolTable* mainST= (struct symbolTable*)malloc(sizeof(struct symbolTable));
    int flag_parserRun=0;
    int flag_ASTRun=0;
    int flag_SymbolTableRun=0;
    while(loop)
    {
        printf("Press 0 to exit\n");
        printf("Press 1 to run the lexer and print the token list\n");
        printf("Press 2 to run the parser and generate parse tree\n");
        printf("Press 3 to print the Abstract Syntax Tree \n");
        printf("Press 4 to display the allocated memory and number of nodes (Run case 2 and 3 before running case 4\n");
        printf("Press 5 to to print The Symbol Table\n");
        printf("Press 6 to display the total memory requirement for each function\n");
        printf("Press 7 to print the type expression and width of array variable\n");
        printf("Press 8 to display Errors and to show total compiling time\n");
        printf("Press 9 to generate assembly code\n");
        
        scanf("%d",&input);
        switch(input)
    {
        case 0: 
        {
            loop=0;
            break;
        }
        // case 1:
        // {
        //    removeComments(file);
        //     break;
        // }
        case 1:
        {
            printTokens();
            break;
        }
        case 2:
        {
            if(!flag_parserRun)
            {
                sendList(dummy);
                populateGrammar();
                findFirstAndFollow();
                fillParseTable();
                StackandParseTreeImplementation(1);

            }
            //initialize_TreeStack();
            else
            {
            flag_parserRun=1;
                            StackandParseTreeImplementation(1);

            }
            break;
        }
        // case 4:
        // {
        //     clock_t start_time, end_time;
        //     double total_CPU_time, total_CPU_time_in_seconds;
        //     start_time = clock();

        //      sendList(dummy);
        //      populateGrammar();
        //     findFirstAndFollow();
        //     fillParseTable();
        //      StackandParseTreeImplementation();

        //     end_time = clock();
        //     total_CPU_time = (double) (end_time - start_time);
        //     total_CPU_time_in_seconds = total_CPU_time /CLOCKS_PER_SEC;

        // printf("Total CPU time: %lf\nTotal CPU time in seconds: %lf\n",total_CPU_time,total_CPU_time_in_seconds);
        //     break;    
        // }
        case 3:
        {   
            if(!flag_parserRun){
                sendList(dummy);
                populateGrammar();
                findFirstAndFollow();
                fillParseTable();
                StackandParseTreeImplementation(0);
               flag_parserRun=1;
            }
               
                struct TreeNode* treeRoot= (struct TreeNode*)(malloc(sizeof(struct TreeNode)));
                treeRoot= getRoot();
                astroot=buildAST(treeRoot,NULL);
                printf("\n\n");
                printf("PRINTING AST --- PREORDER TRAVERSAL \n");
                printf("currentNode   --->  Children \n");
                printPreorderAST(astroot);
                // flag_ASTRun=1;
                break;
            
        }


        case 4:
        {
            // printing the number of nodes of AST and parse tree
            // printf("Ki")
            int sizeOfAST = getSizeOfAST();
            int countOfAST = getCountOfAST();

            int sizeOfTree = getSizeOfTree();
            int countOfTree = getCountOfTree();
            printf("size of Tree : %d \n", sizeOfTree);
            printf("size of AST : %d \n", sizeOfAST);

            printf("count of Tree : %d \n", countOfTree);
            printf("count of AST : %d \n \n", countOfAST);
            printf("CALCULATING COMPRESSION PERCENTAGE \n");
            
            float percen = (sizeOfTree - sizeOfAST ) * 100.00 / (sizeOfTree);
            printf(" ---> %f %% \n", percen);
            // printf("%)
            break;
            
        }
       
        case 5:
        {
            if(!flag_ASTRun){
           if(!flag_parserRun){
                sendList(dummy);
                populateGrammar();
                findFirstAndFollow();
                fillParseTable();
                StackandParseTreeImplementation(0);
               flag_parserRun=1;
            }
               
                struct TreeNode* treeRoot= (struct TreeNode*)(malloc(sizeof(struct TreeNode)));
                treeRoot= getRoot();
                astroot=buildAST(treeRoot,NULL);
                printf("\n\n");
                printPreorderAST(astroot);
                flag_ASTRun=1;
            }
            initializeST(mainST);
            mainST->stName="Global";
            mainST->scope_start=0;
            mainST->scope_end=0;
            mainST->nestingLevel=0;
            // sendASTroot(astroot);
            printf("Starting Symbol Table Implementation\n");
            symbolTableImplementation(mainST,astroot);
            printf("Printing Symbol Table\n");
            initializeHashType();
            printf("Printing Symbol table %s ==========\n",mainST->stName);
    // int offset = 0;
    printf("Variable name   scope (module name)   scope (line numbers)    type of element     is_array    Static/dynamic  array range     width   offset     nesting level\n");
            printSymbolTable(mainST,0);
            flag_SymbolTableRun=1;
            break;
        }
        case 7:
        {
                if(!flag_SymbolTableRun){
                        if(!flag_ASTRun){
           if(!flag_parserRun){
                sendList(dummy);
                populateGrammar();
                findFirstAndFollow();
                fillParseTable();
                StackandParseTreeImplementation(0);
               flag_parserRun=1;
            }
               
                struct TreeNode* treeRoot= (struct TreeNode*)(malloc(sizeof(struct TreeNode)));
                treeRoot= getRoot();
                astroot=buildAST(treeRoot,NULL);
                printf("\n\n");
                printPreorderAST(astroot);
                flag_ASTRun=1;
            }
            initializeST(mainST);
            mainST->stName="Global";
            mainST->scope_start=0;
            mainST->scope_end=0;
            mainST->nestingLevel=0;
            // sendASTroot(astroot);
            printf("Starting Symbol Table Implementation\n");
            symbolTableImplementation(mainST,astroot);
            printf("Printing Symbol Table\n");
            initializeHashType();
            printf("Printing Symbol table %s ==========\n",mainST->stName);
    // int offset = 0;
    printf("Variable name   scope (module name)   scope (line numbers)    type of element     is_array    Static/dynamic  array range     width   offset     nesting level\n");
            printSymbolTable(mainST,0);
            flag_SymbolTableRun=1;


                }
                
                printf("scope (module name)   scope (line numbers)        Variable name       Static/dynamic  array range     type of element\n");
                printArrayCase(mainST);
                break;
        }   

        case 8:
        {

            clock_t start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
            struct TreeNode* treeRoot= (struct TreeNode*)(malloc(sizeof(struct TreeNode)));
                treeRoot= getRoot();
                astroot=buildAST(treeRoot,NULL);
             initializeST(mainST);
            mainST->stName="Global";
            mainST->scope_start=0;
            mainST->scope_end=0;
            mainST->nestingLevel=0;
            symbolTableImplementation(mainST,astroot);

            end_time = clock();
            total_CPU_time = (double) (end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time /CLOCKS_PER_SEC;

        printf("Total CPU time: %lf\nTotal CPU time in seconds: %lf\n",total_CPU_time,total_CPU_time_in_seconds);
                


            

        //    typeCheck(astroot);
            break;
        }

        case 6:
        case 9:
        {
            printf("We couldn't implement this part.\n");
            break;
        }
        default:
        {
            printf("Please enter valid number!");
            break;
        }
    }
    }
    return 0;
}
#include <iostream>
#include<stdio.h>
#include "../include/node.h"
#include "../include/Module.h"
#include "../include/Pass.h"

extern FILE* yyin;
extern int yyparse();
extern NCompUnit* CompUnit;
// this come from parser.y

void PrintAST(NCompUnit& root);

int main(int argc, char* argv[])
{
    FILE* fp = NULL;
    fp = fopen(argv[1], "r");
    if (!fp)
    {
        printf("couldn't open file for reading\n");
        exit(-1);
    }
    yyin = fp;
    int parseErr = yyparse();
    if (parseErr != 0) {
        printf("couldn't complete lex parse\n");
        exit(-1);
    }
    fclose(fp);
    Module p;
    loopDetection pass;
    p.ASTTranslate(CompUnit);
    //pass.setModule(p);
    //pass.run();
    p.debugPrint();
    return 0;
}

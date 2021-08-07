#include <iostream>
#include <fstream>

#include "parser/node.h"
#include "utils/Error.h"
#include "ir/Module.h"
#include "assembly/AsmTranslate.h"

using namespace std;

extern FILE *yyin;
extern int yyparse();
extern NCompUnit *CompUnit;
// this come from parser.y

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    fp = fopen(argv[1], "r");
    if (!fp)
        Error::exit("couldn't open file for reading");

    yyin = fp;
    int parseErr = yyparse();
    if (parseErr != 0)
        Error::exit("couldn't complete lex parse");
    fclose(fp);

    std::string fileName(argv[1]);

    Module module;
    module.ASTTranslate(CompUnit);
    module.debugPrint();

    Assembly::AsmTranslator asmTranslator(module, fileName);
    asmTranslator.translate();

    auto code = asmTranslator.getCode();
    std::cout << code << "\n";

    return 0;
}
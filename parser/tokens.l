%{
#include <string>
#include<cstdlib>
#include "node.h"
#include "parser.hpp"
//don't use "using namespace std;" in flex

#define STRING_TOKEN        yylval.string = new std::string(yytext, yyleng)
#define STRING_INT			yylval.token = atoi(yytext)
#define KEYWORD_TOKEN(t)    yylval.token = t
%}

%option noyywrap
%option yylineno

%%

[ \t\r\n]

"const"		{ STRING_TOKEN; return CONST; }

"int"		{ STRING_TOKEN; return INT; }

"void"		{ STRING_TOKEN; return VOID; }

"if"		{ STRING_TOKEN; return IF; }

"else"		{ STRING_TOKEN; return ELSE; }

"while"		{ STRING_TOKEN; return WHILE; }

"break"		{ STRING_TOKEN; return BREAK; }

"continue"	{ STRING_TOKEN; return CONTINUE; }

"return"	{ STRING_TOKEN; return RETURN; }

"=="		{ KEYWORD_TOKEN(EQ); return EQ; }

"!="		{ KEYWORD_TOKEN(NE); return NE; }

"<"			{ KEYWORD_TOKEN(LT); return LT; }

">"			{ KEYWORD_TOKEN(GT); return GT; }

">="		{ KEYWORD_TOKEN(GE); return GE; }

"<="		{ KEYWORD_TOKEN(LE); return LE; }

"!"			{ KEYWORD_TOKEN(NOT); return NOT; }

"&&"		{ KEYWORD_TOKEN(AND); return AND; }

"||"		{ KEYWORD_TOKEN(OR); return OR; }

"+"			{ KEYWORD_TOKEN(ADD); return ADD; }

"-"			{ KEYWORD_TOKEN(SUB); return SUB; }

"*"			{ KEYWORD_TOKEN(MUL); return MUL; }

"/"			{ KEYWORD_TOKEN(DIV); return DIV; }

"%"			{ KEYWORD_TOKEN(MOD); return MOD; }

[A-Za-z_][A-Za-z_0-9]* { 
							STRING_TOKEN;
							return Ident; 
						}

0[xX][0-9a-fA-F]*|0[0-7]*|[1-9][0-9]*		{
								// be careful for 'o
							 	//std::cout << "IntConst: " << yytext << std::endl;
								 STRING_INT;
								return IntConst; }

"//"[^\n]*	{}

"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"	{} 

.		{ //std::cout << "lex " << *yytext << " unknown at line:" << yylineno << std::std::endl; 
			return *yytext;}
%%
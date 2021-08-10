%{
#include "node.h"
#include <cstdio>
#include <cstdlib>
extern int yylineno;
extern char* yytext;
void yyerror(const char * msg) { printf("line %d : %s at %s\n", yylineno, msg, yytext); exit(0); }
extern int yylex();
//don't use "using namespace std" in yacc
NCompUnit * CompUnit;
// the top node of ast
%}

%union
{
	std::string* string;
	int token;//a number about sign
	NCompUnit* compunit;
	NFuncDecl* funcdecl;
	NVarDecl* vardecl;
	NStmt* stmt;
	NExp* exp;
	std::vector<NDecl*> *decllist;
	std::vector<NStmt*> *stmtlist;
	std::vector<NVarDecl*> *vardecllist;
	std::vector<NExp*> *explist;
	NIdentifier* ident;
	NInteger* integer;
}

%token <string>CONST INT VOID
%token <token>IF ELSE WHILE BREAK CONTINUE RETURN
%token <token>EQ NE LE GE LT GT NOT AND OR
%token <token>ADD SUB MUL DIV MOD
%token <string>Ident
%token <token>IntConst

%type <compunit>CompUnit
%type <decllist>Decl Declaration VarDecl ConstDecl
%type <funcdecl>FuncDef
%type <vardecllist>ConstDeclFoot VarDefFoot FuncFParams
%type <vardecl>ConstDef VarDef FuncFParam
%type <explist>ArrayDef ExpFoot InitValFoot
%type <stmtlist>BlockItems Block
%type <stmt>IfStmt Stmt BlockItem BlockStmt DeclStmt Statement
%type <exp>Exp LExp Integer InitVal
%type <ident>Identifier

%left OR
%left AND
%left NE EQ
%left LT GT LE GE
%left ADD SUB
%left MUL DIV MOD
%right UNIMUS

%nonassoc IFX
%nonassoc ELSE

%%

CompUnit : Decl
	 {
		CompUnit = new NCompUnit(*$1);
		delete $1;
	 }
;

Decl : Decl FuncDef
     {
		$1->push_back($2);
		$$ = $1;
     }
     | Decl Declaration
     {
		 $2->insert($2->begin(), $1->begin(), $1->end());
		 $$ = $2;
     }
     | 
     { 
	$$ = new NDeclList(); 
     }
;

Declaration : VarDecl
	    | ConstDecl
;

ConstDecl : CONST INT ConstDeclFoot ';'
	  {
		  $$ = $<decllist>3;
	  }
;

ConstDeclFoot : ConstDef
	      {
			$$ = new NVarDeclList();
			$1->setTypeforConst();
			$$->push_back($1);
	      }
	      | ConstDeclFoot ',' ConstDef
		  {
			$3->setTypeforConst();
			$1->push_back($3);
			$$ = $1;
		  }
;

ConstDef : Identifier ArrayDef '=' InitVal
	 {
		$$ = new NVarDecl(*$1, *$2, $4);
	 }
;

ArrayDef : ArrayDef '[' Exp ']'
	  {
		  
	  	$1->push_back($3);
		$$ = $1;
	  }
	  | 
	  {
		$$ = new NExpList();
	  }
;

VarDecl : INT VarDefFoot ';'
	{
		$$ = $<decllist>2;
	}
;

VarDefFoot : VarDef
	   {
		$$ = new NVarDeclList();
		$$->push_back($1);
	   }
	   | VarDefFoot ',' VarDef
	   {
		$1->push_back($3);
		$$ = $1;
	   }
;

VarDef : Identifier ArrayDef
       {
		$$ = new NVarDecl(*$1, *$2);
       }
       | Identifier ArrayDef '=' InitVal
       {
		$$ = new NVarDecl(*$1, *$2, $4);
       }	
;

InitVal : Exp
	| '{' InitValFoot '}'
	{
		$$ = new NInitListExp(*$2);
	}
        | '{' '}'
	{
		$$ = new NInitListExp();
	}
;

InitValFoot : InitVal
		{
			$$ = new NExpList();
			$$->push_back($1);
		}
	    | InitValFoot ',' InitVal
	    {
			$1->push_back($3);
			$$ = $1;
	    }
;

FuncDef : VOID Identifier '(' FuncFParams ')' Block
	{
		$$ = new NFuncDecl(*$1, *$2, *$4, *$6);
	}
	| VOID Identifier '(' ')' Block
	{
		$$ = new NFuncDecl(*$1, *$2, *$5);
	}
	| INT Identifier '(' FuncFParams ')' Block
	{
		$$ = new NFuncDecl(*$1, *$2, *$4, *$6);
	}
	| INT Identifier '(' ')' Block
	{
		$$ = new NFuncDecl(*$1, *$2, *$5);
	}
;

FuncFParams : FuncFParams ',' FuncFParam
	    {
		$1->push_back($3);
		$$ = $1;
	    }
	    | FuncFParam
	    {
		$$ = new NVarDeclList();
		$$->push_back($1);
	    }
;

FuncFParam : INT Identifier
	   {
		$$ = new NVarDecl(*$1, *$2);
	   }
	   | INT Identifier '[' ']' ArrayDef
	   {
		$$ = new NVarDecl(*$1, *$2, *$5);
	   }
;

Block : '{' BlockItems '}'
      {
	$$ = $2;
      }
;

BlockItems : BlockItems BlockItem
	   {
		   $1->push_back($2);
			$$ = $1;
	   }
	   | { $$ = new NStmtList(); }
;

BlockItem : DeclStmt
	  | Statement
;

Statement : Stmt
		  | BlockStmt
;

BlockStmt : Block
		{
			$$ = new NBlockStmt(*$1);
		}
;
DeclStmt : VarDecl
	 {
		 $$ = new NDeclStmt(*$1);
	 }
	 | ConstDecl
	 {
		 $$ = new NDeclStmt(*$1);
	 }
;

Stmt : Identifier ArrayDef '=' Exp ';'
	  {
		$$ = new NAssignStmt(*$1, *$2, *$4);
	  }
	  | Exp ';'
	  {
		$$ = new NExpStmt(*$1);
	  }
          | ';'
	  {
		$$ = new NNullStmt();
	  }
     | IfStmt
	 | WHILE '(' LExp ')' Statement
	 {
		$$ = new NWhileStmt(*$3, *$5);
	 }
	  | BREAK ';'
	  {
		$$ = new NBreakStmt();
	  }
	  | CONTINUE ';'
	  {
		$$ = new NContinueStmt();
	  }
	  | RETURN ';'
	  {	
		$$ = new NReturnStmt();
	  }
	  | RETURN Exp ';'
	  {	
		$$ = new NReturnStmt($2);
	  }
;

IfStmt : IF '(' LExp ')' Statement %prec IFX
       {
		$$ = new NIfStmt(*$3, *$5);
       }
       | IF '(' LExp ')' Statement ELSE Statement
       {
		$$ = new NIfStmt(*$3, *$5, $7);
       }
;

ExpFoot : Exp
	{
		$$ = new NExpList();
		$$->push_back($1);
	}
	| ExpFoot ',' Exp
	{
		$1->push_back($3);
		$$ = $1;
	}
;

LExp : LExp OR LExp 
	 {
	 	$$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp AND LExp
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp NE LExp 
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp EQ LExp 
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp LT LExp 
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp GT LExp 
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp LE LExp 
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | LExp GE LExp 
	 {
		 $$ = new NBinaryExp(*$1, $2, *$3);
	 }
     | Exp
;

Exp : Exp MUL Exp
	{
		$$ = new NBinaryExp(*$1, $2, *$3);
	}
    | Exp DIV Exp
	{
		$$ = new NBinaryExp(*$1, $2, *$3);
	}
    | Exp MOD Exp
	{
		$$ = new NBinaryExp(*$1, $2, *$3);
	}
    | Exp ADD Exp
	{
		$$ = new NBinaryExp(*$1, $2, *$3);
	}
    | Exp SUB Exp
	{
		$$ = new NBinaryExp(*$1, $2, *$3);
	}
    | ADD Exp %prec UNIMUS
	{
		$$ = new NUnaryExp($1, *$2);
	}
    | SUB Exp %prec UNIMUS
	{
		$$ = new NUnaryExp($1, *$2);
	}
    | NOT Exp %prec UNIMUS
	{
		$$ = new NUnaryExp($1, *$2);
	}
    | '(' Exp ')'
	{
		$$ = $2;
	}
    | Identifier ArrayDef
	{
		$$ = new NIdentifierExp(*$1, *$2);
	}
    | Integer
    | Identifier '(' ')'
	{
		$$ = new NCallExp(*$1);
	}
    | Identifier '(' ExpFoot ')'
	{
		$$ = new NCallExp(*$1, *$3);
	}
;

Identifier : Ident
	   {
		$$ = new NIdentifier(*$1);
	   }
;

Integer : IntConst
		{
			$$ = new NInteger($1);
		}
;

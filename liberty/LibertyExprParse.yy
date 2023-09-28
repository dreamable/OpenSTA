%{



// Liberty function expression parser.

#include "FuncExpr.hh"
#include "liberty/LibertyExpr.hh"
#include "liberty/LibertyExprPvt.hh"

int LibertyExprLex_lex();
#define LibertyExprParse_lex LibertyExprLex_lex

%}

%union {
  int int_val;
  const char *string;
  sta::FuncExpr *expr;
}

%token PORT
%left '+' '|'
%left '*' '&'
%left '^'
%left '!' '\''

%type <string> PORT
%type <expr> expr terminal terminal_expr implicit_and

%{
%}

%%

result_expr:
	expr	{ sta::libexpr_parser->setResult($1); }
|	expr ';'{ sta::libexpr_parser->setResult($1); }
;

terminal:
	PORT		{ $$ = sta::libexpr_parser->makeFuncExprPort($1); }
|	'0'		{ $$ = sta::FuncExpr::makeZero(); }
|	'1'		{ $$ = sta::FuncExpr::makeOne(); }
|	'(' expr ')'	{ $$ = $2; }
;

terminal_expr:
	terminal
|	'!' terminal	{ $$ = sta::libexpr_parser->makeFuncExprNot($2); }
|	terminal '\''	{ $$ = sta::libexpr_parser->makeFuncExprNot($1); }
;

implicit_and:
	terminal_expr terminal_expr
	{ $$ = sta::libexpr_parser->makeFuncExprAnd($1, $2); }
|	implicit_and terminal_expr
	{ $$ = sta::libexpr_parser->makeFuncExprAnd($1, $2); }
;

expr:
	terminal_expr
|	implicit_and
|	expr '+' expr	{ $$ = sta::libexpr_parser->makeFuncExprOr($1, $3); }
|	expr '|' expr	{ $$ = sta::libexpr_parser->makeFuncExprOr($1, $3); }
|	expr '*' expr   { $$ = sta::libexpr_parser->makeFuncExprAnd($1, $3); }
|	expr '&' expr   { $$ = sta::libexpr_parser->makeFuncExprAnd($1, $3); }
|	expr '^' expr	{ $$ = sta::libexpr_parser->makeFuncExprXor($1, $3); }
;

%%

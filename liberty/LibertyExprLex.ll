%{



// Liberty function expression lexical analyzer

#include "util/FlexDisableRegister.hh"
#include "Debug.hh"
#include "StringUtil.hh"
#include "liberty/LibertyExprPvt.hh"

using sta::libexpr_parser;
using sta::stringCopy;
using sta::FuncExpr;

#include "LibertyExprParse.hh"

#define YY_NO_INPUT

#define YY_INPUT(buf,result,max_size) \
  result = libexpr_parser->copyInput(buf, max_size)

void
libertyExprFlushBuffer()
{
  YY_FLUSH_BUFFER;
}

%}

/* %option debug */
%option noyywrap
%option nounput
%option never-interactive

%x ESCAPED_STRING

PORT	[A-Za-z_]([A-Za-z0-9_\.\[\]])*
OP	"'"|"!"|"^"|"*"|"&"|"+"|"|"|1|0
PAREN	"("|")"
BLANK	[ \t\r]
ESCAPE	\\
QUOTE	\"
EOL	\r?\n

%%

{OP}|{PAREN} { return ((int) LibertyExprLex_text[0]); }

{ESCAPE}{EOL} { /* I doubt that escaped returns get thru the parser */ }

{ESCAPE}{QUOTE}	{ BEGIN(ESCAPED_STRING); libexpr_parser->tokenErase(); }

<ESCAPED_STRING>. { libexpr_parser->tokenAppend(LibertyExprLex_text[0]); }

<ESCAPED_STRING>{ESCAPE}{QUOTE} {
	BEGIN(INITIAL);
	LibertyExprParse_lval.string = libexpr_parser->tokenCopy();
	return PORT;
	}

{PORT}	{
	LibertyExprParse_lval.string = stringCopy(LibertyExprLex_text);
	return PORT;
	}

{BLANK}	{}

	/* Send out of bound characters to parser. */
.	{ return (int) LibertyExprLex_text[0]; }

%%

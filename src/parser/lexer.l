%option yylineno

%{
#include "parser.hpp"
#include "parser.tab.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

void yyerror(const char *s);
%}

/* Define Tokens*/
INTEGER        -?(0|[1-9][0-9]*)
FLOAT          -?(0|[1-9][0-9]*)(\.[0-9]+)?(e-?(0|[1-9][0-9]*))?
ID             [a-zA-Z_][a-zA-Z0-9_]*
FULLSTRING     \'[^\']*\'|\"[^\"]*\"

%%

[ \t\r\n]+    { /* Ignore Whitespace*/ }

"CREATE"        { return CREATE; }

{ID}          { yylval.str = strdup(yytext); return ID; }
{INTEGER}      { yylval.num = atoll(yytext); return INTEGER; }
{FLOAT}      { yylval.flt = strtod(yytext, NULL); return FLOAT; }

"("           { return LPAREN; }
")"           { return RPAREN; }
"{"           { return LBRACE; }
"}"           { return RBRACE; }
"["           { return LBRACKET; }
"]"           { return RBRACKET; }
":"           { return COLON; }
";"           { return SEMICOLON; }
","           { return COMMA; }
"->"          { return ARROW; }
"-"           { return DASH; }

{FULLSTRING}      { yylval.str = strdup(yytext); return FULLSTRING; }

%%

int yywrap() { return 1; }

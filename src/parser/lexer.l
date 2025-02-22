%{
#include "parser.hpp"
#include "parser.tab.hpp"
#include <iostream>
#include <string>

void yyerror(const char *s);
%}

/*Define Tokens*/
DIGITS       [0-9]*
ID          [a-zA-Z_][a-zA-Z0-9_]*
FULLSTRING      \'[^\']*\'|\"[^\"]*\"

%%

[ \t\r\n]+    { /* Ignore Whitespace*/ }

CREATE        { return CREATE; }

{ID}          { yylval.str = strdup(yytext); return ID; }
{DIGITS}      { yylval.str = strdup(yytext); return DIGITS; }

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

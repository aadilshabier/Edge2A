%{
#include "parser.hpp"
#include "../graphdb.hpp"
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <unordered_set>

extern int yylex();
void yyerror(const char *s);

GraphDB *graphDB;

std::unordered_set<std::string> current_labels;
std::unordered_map<std::string, std::string> current_properties;
%}

%union {
    char* str;
}

// Token definitions
%token CREATE LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COLON SEMICOLON COMMA DASH ARROW
%token <str> DIGITS ID FULLSTRING
%type <str> STRING property_value item_list string_list number_list

%%

// Entry point
statements:
    create_statement
    | statements create_statement
    ;

create_statement:
    create_statement SEMICOLON
    | CREATE node_statements
    | CREATE edge_statements
    ;

node_statements:
    node_statement
    | node_statements COMMA node_statement
    ;

node_statement:
    LPAREN ID COLON ID properties RPAREN
    {
        current_labels.insert($4);
        NodePK node = graphDB->createNode(current_labels, current_properties, $2);
        current_labels.clear();
        current_properties.clear();
    }
    ;

edge_statements:
    edge_statement
    | edge_statements COMMA edge_statement
    ;

edge_statement:
    LPAREN ID RPAREN DASH LBRACKET COLON ID properties RBRACKET ARROW LPAREN ID RPAREN
    {
        graphDB->createEdgeByAlias($7, $2, $12, current_properties);
        current_properties.clear();
    }
    ;

properties:
    LBRACE property_list RBRACE
    | /* empty */ { current_properties.clear(); }
    ;

property_list:
    ID COLON property_value
    {
        current_properties[$1] = $3;
    }
    | property_list COMMA ID COLON property_value
    {
        current_properties[$3] = $5;
    }
    ;

property_value:
    STRING { $$ = $1; }
    | DIGITS { $$ = $1; }
    | LBRACKET item_list RBRACKET { $$ = $2; }
    ;

item_list:
    string_list { $$ = $1; }
    | number_list { $$ = $1; }
    ;

string_list:
    string_list COMMA STRING { $$ = $3; } // Return only final value for now
    | STRING { $$ = $1; }
    ;

number_list:
    number_list COMMA DIGITS { $$ = $3; } // Return only final value for now
    | DIGITS { $$ = $1; }
    ;

STRING:
    FULLSTRING { 
        /*Trimming first and last characters*/
        std::string str($1); 
        $$ = strdup((str.size() > 1) ? str.substr(1, str.size() - 2).c_str() : ""); 
    }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << std::endl;
}

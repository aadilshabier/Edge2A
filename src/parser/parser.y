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
Data current_value;
DataArrayType current_array;
std::unordered_map<std::string, Data> current_properties;
%}

%union {
    char* str;
	DataIntType num;
	DataRealType flt;
}

// Token definitions
%token CREATE LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COLON SEMICOLON COMMA DASH ARROW
%token <str> ID FULLSTRING
%token <num> INTEGER
%token <flt> FLOAT

%nterm <str> STRING
// %nterm <str> item_list string_list number_list
%%

// Entry point
statements:
    statements create_statement
    | %empty
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
    | %empty
    ;

property_list:
    property_item
    | property_list COMMA property_item
    ;

property_item:
    ID COLON property_value
    {
        current_properties[$1] = current_value;
    };

property_value:
    STRING { current_value = $1; }
    | INTEGER { current_value = $1; }
    | FLOAT { current_value = $1; }
    | LBRACKET item_list RBRACKET {
		  // NOTE: Doesn't support nested lists yet!
		  current_value = current_array;
		  current_array.clear();
	  }
    ;

item_list: item_list COMMA property_value { current_array.push_back(current_value); }
         | property_value { current_array.push_back(current_value); }
;

STRING:
    FULLSTRING { 
        /* Trimming first and last characters */
        std::string str($1); 
        $$ = strdup((str.size() > 1) ? str.substr(1, str.size() - 2).c_str() : ""); 
    }
    ;

%%
extern int yylineno;

void yyerror(const char *s) {
    std::cerr << "Parser error: " << s << " at " << yylineno << std::endl;
}

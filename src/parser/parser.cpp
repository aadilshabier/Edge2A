#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

extern int yyparse();
extern GraphDB *graphDB;
extern FILE *yyin;

void Parser::parseCypherScript(const std::string &filename, GraphDB &db) {
    yyin = fopen(filename.c_str(), "r");
    if (!yyin) {
        std::cerr << "ERROR: Could not open file: " << filename << std::endl;
        return;
    }

    graphDB = &db;
    yyparse();
    fclose(yyin);
}

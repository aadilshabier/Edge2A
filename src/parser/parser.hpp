#pragma once

#include "../graphdb.hpp"

class GraphDB;

class Parser {
public:
    void parseCypherScript(const std::string &filename, GraphDB &db);
};

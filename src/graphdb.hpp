#pragma once

#include "common.hpp"
#include "graph.hpp"
#include "match.hpp"
#include "parser/parser.hpp"

#include <vector>


class GraphDB
{
public:
	Graph graph;
	std::unordered_map<std::string, NodePK> aliasToNodePKMap;

public:

	explicit GraphDB() {}

	NodePK createNode(std::unordered_set<std::string> labels={},
					std::unordered_map<std::string, Data> properties={}, std::string alias="");
	
	NodePK getNodePKByAlias(std::string alias);
		
	EdgePK createEdge(std::string type, NodePK from, NodePK to,
					std::unordered_map<std::string, Data> properties={});

	EdgePK createEdgeByAlias(std::string type, std::string fromAlias, std::string toAlias,
					std::unordered_map<std::string, Data> properties={});

	MatchResults match(MatchPattern pattern, WhereExp where, MatchResultFmt resultFmt);

	void loadFromFile(const std::string &filename);
	void saveToFile(const std::string &filename) const;
	void getGraphAsStream(std::ostream &os) const;

	void loadCypherScript(const std::string &filename);
};

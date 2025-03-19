#pragma once

#include "common.hpp"
#include "graph.hpp"
#include "match.hpp"
#include "parser/parser.hpp"
#include "matcher.hpp"

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
	
	NodePK getNodePKByAlias(const std::string &alias) const;
		
	EdgePK createEdge(std::string type, NodePK from, NodePK to,
					std::unordered_map<std::string, Data> properties={});

	EdgePK createEdgeByAlias(const std::string &type, const std::string &fromAlias, const std::string &toAlias,
					std::unordered_map<std::string, Data> properties={});

	MatchResults match(MatchPattern pattern, WhereExp where, MatchResultFmt resultFmt);

	void loadFromFile(const std::string &filename);
	void saveToFile(const std::string &filename) const;
	void getGraphAsStream(std::ostream &os) const;

	void parseCypherScript(const std::string &filename);
};

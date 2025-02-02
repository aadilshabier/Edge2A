#pragma once

#include "common.hpp"
#include "graph.hpp"
#include "match.hpp"

#include <vector>

class GraphDB
{
	Graph graph;
public:

	explicit GraphDB() {}

	NodePK createNode(std::unordered_set<std::string> labels={},
					  std::unordered_map<std::string,std::string> properties={});

	EdgePK createEdge(std::string type, NodePK from, NodePK to,
					  std::unordered_map<std::string,std::string> properties={});

	MatchResults match(MatchPattern pattern, WhereExp where, MatchResultFmt resultFmt);

	void loadFromFile(const std::string &filename);
	void saveToFile(const std::string &filename) const;
	void getGraphAsStream(std::ostream &os) const;
};

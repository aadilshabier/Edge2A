#pragma once

#include "common.hpp"
#include "graph.hpp"

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

	void loadFromFile(const std::string &filename);
	void saveToFile(const std::string &filename) const;
	std::stringstream getGraphAsStringStream() const;
};

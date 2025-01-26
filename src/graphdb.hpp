#pragma once

#include "edge.hpp"
#include "node.hpp"

#include <vector>

class GraphDB
{
public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;

	explicit GraphDB() {}

	NodePK newNode(std::unordered_set<std::string> labels={},
				   std::unordered_map<std::string,std::string> properties={});

	EdgePK newEdge(std::string type, NodePK from, NodePK to,
				   std::unordered_map<std::string,std::string> properties={});

	void loadFromFile(const std::string &filename);
	void saveToFile(const std::string &filename) const;
	std::string getGraphAsStr() const;
};

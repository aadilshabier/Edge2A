#include "graphdb.hpp"

#include <iostream>

NodePK GraphDB::newNode(std::unordered_set<std::string> labels,
						std::unordered_map<std::string,std::string> properties)
{
	Node node;
	node.labels = labels;
	node.properties = properties;

	nodes.push_back(node);
	return nodes.size()-1;
}

EdgePK GraphDB::newEdge(std::string type, NodePK from, NodePK to,
						std::unordered_map<std::string,std::string> properties)
{
	if (from >= nodes.size() or to >= nodes.size()) {
		std::cerr << "ERROR: " << from << " or " << to << " is greater than " << nodes.size()-1 << std::endl;
		return 9999;
	}

	Edge edge;
	edge.from = from;
	edge.to = to;
	edge.properties = properties;
	edges.push_back(edge);

	auto edgeId = edges.size()-1;
	nodes[from].edges.push_back(edgeId);

	return edgeId;
}

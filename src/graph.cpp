#include "graph.hpp"

#include <iostream>

NodePK Graph::createNode(std::unordered_set<std::string> labels,
						 std::unordered_map<std::string, Data> properties)
{
	Node node;
	node.labels = labels;
	node.properties = properties;
	nodes.push_back(node);

	return nodes.size()-1;
}

EdgePK Graph::createEdge(std::string type, NodePK from, NodePK to,
						 std::unordered_map<std::string, Data> properties)
{
	if (from >= nodes.size() or to >= nodes.size()) {
		std::cerr << "ERROR: " << from << " or " << to << " is greater than " << nodes.size()-1 << std::endl;
		return -1;
	}

	Edge edge;
	edge.type = type;
	edge.from = from;
	edge.to = to;
	edge.properties = properties;
	edges.push_back(edge);

	auto edgeId = edges.size()-1;
	nodes[from].edges.push_back(edgeId);

	return edgeId;
}

EdgePK Graph::getEdgeByNodesAndType(NodePK from, NodePK to, std::string type)
{
	std::vector<EdgePK> edgePKs;
	for (auto edgePK : nodes[from].edges) {
		if (edges[edgePK].to == to and edges[edgePK].type == type) {
			return edgePK;
		}
	}

	// Edge not found
	std::cerr << "ERROR: Edge not found" << std::endl;
	return -1;
}

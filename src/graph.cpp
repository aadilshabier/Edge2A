#include "graph.hpp"

#include <iostream>

NodePK Graph::createNode(std::unordered_set<std::string> labels,
						 std::unordered_map<std::string, Data> properties)
{
	Node node;
	node.pk = nodePkCount++;
	node.labels = labels;
	node.properties = properties;
	nodes.insert(node.pk, node);

	return node.pk;
}

EdgePK Graph::createEdge(std::string type, NodePK from, NodePK to,
						 std::unordered_map<std::string, Data> properties)
{
	Edge edge;
	edge.pk = edgePkCount++;
	edge.type = type;
	edge.from = from;
	edge.to = to;
	edge.properties = properties;
	edges.insert(edge.pk, edge);

	nodes.search(from)->edges.push_back(edge.pk);

	return edge.pk;
}

EdgePK Graph::getEdgeByNodesAndType(NodePK from, NodePK to, std::string type)
{
	std::vector<EdgePK> edgePKs;
	for (auto edgePK : nodes.search(from)->edges) {
		Edge *currEdge = edges.search(edgePK);
		if (currEdge->to == to and currEdge->type == type) {
			return edgePK;
		}
	}

	// Edge not found
	std::cerr << "ERROR: Edge not found" << std::endl;
	return -1;
}

#include "graph.hpp"

#include <iostream>

NodePK Graph::createNode(std::unordered_set<std::string> labels,
						 std::unordered_map<std::string,std::string> properties, std::string alias)
{
	Node node;
	node.labels = labels;
	node.properties = properties;
	nodes.push_back(node);

	NodePK nodePK = nodes.size()-1;
	if (alias != "") {
		// Add alias to map if provided
		nodeIdMap[alias] = nodePK;
	}
	return nodePK;
}

NodePK Graph::getNodePKByAlias(std::string alias)
{
	// Search within map
	if (nodeIdMap.find(alias) != nodeIdMap.end()) {
		return nodeIdMap[alias];
	}

	// Node not found
	std::cerr << "ERROR: Node not found" << std::endl;
	return 9999;
}

EdgePK Graph::createEdge(std::string type, NodePK from, NodePK to,
						 std::unordered_map<std::string,std::string> properties)
{
	if (from >= nodes.size() or to >= nodes.size()) {
		std::cerr << "ERROR: " << from << " or " << to << " is greater than " << nodes.size()-1 << std::endl;
		return 9999;
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

EdgePK Graph::createEdgeByAlias(std::string type, std::string fromAlias, std::string toAlias,
						 std::unordered_map<std::string,std::string> properties)
{
	NodePK from = getNodePKByAlias(fromAlias);
	NodePK to = getNodePKByAlias(toAlias);

	return createEdge(type, from, to, properties);
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
	return 9999;
}

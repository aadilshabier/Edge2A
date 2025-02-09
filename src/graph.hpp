#pragma once

#include <vector>

#include "edge.hpp"
#include "node.hpp"

class Graph
{
public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::unordered_map<std::string, NodePK> nodeIdMap;

	NodePK createNode(std::unordered_set<std::string> labels={},
					  std::unordered_map<std::string,std::string> properties={}, std::string alias="");

	NodePK getNodePKByAlias(std::string alias);

	EdgePK createEdge(std::string type, NodePK from, NodePK to,
					  std::unordered_map<std::string,std::string> properties={});

	EdgePK createEdgeByAlias(std::string type, std::string fromAlias, std::string toAlias,
					  std::unordered_map<std::string,std::string> properties={});
	
	EdgePK getEdgeByNodesAndType(NodePK from, NodePK to, std::string type);

    size_t numNodes() const {
		return nodes.size();
	}

	size_t numEdges() const {
		return edges.size();
	}

public:
	// Utility functions
	void printNode(NodePK nodePK) const;
	void printEdge(EdgePK edgePK) const;
};

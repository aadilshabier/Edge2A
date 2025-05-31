#pragma once

#include <vector>

#include "edge.hpp"
#include "node.hpp"

class Graph
{
private:
	NodePK nodePkCount;
	EdgePK edgePkCount;
	
public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;

	Graph();

	NodePK createNode(std::unordered_set<std::string> labels={},
					  std::unordered_map<std::string, Data> properties={});

	EdgePK createEdge(std::string type, NodePK from, NodePK to,
					std::unordered_map<std::string, Data> properties={});
	
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

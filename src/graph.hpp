#pragma once

#include <vector>

#include "edge.hpp"
#include "node.hpp"
#include "bptree/bptree.hpp"

#define NODEKEYCOUNT 128
#define EDGEKEYCOUNT 128
#define NODELEAFCOUNT 16
#define EDGELEAFCOUNT 16

class Graph
{
private:
	NodePK nodePkCount;
	EdgePK edgePkCount;
	
public:
	BPlusTree<Node, NodePK> nodes;
	BPlusTree<Edge, EdgePK> edges;

	Graph(): nodes(NODEKEYCOUNT, NODELEAFCOUNT), edges(EDGEKEYCOUNT, EDGELEAFCOUNT),
			nodePkCount(0), edgePkCount(0) {};

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

	size_t getMaxNodePK() const {
		return nodes.getMaxKey();
	}

public:
	// Utility functions
	void printNode(NodePK nodePK) const;
	void printEdge(EdgePK edgePK) const;
};

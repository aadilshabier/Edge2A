#include "graph.hpp"

#include <iostream>

void Graph::printNode(NodePK nodePK) const
{
	std::cout << "NodePK: " << nodePK << std::endl;
	std::cout << "Labels: " << std::endl;
	for (const auto &label : nodes[nodePK].labels) {
		std::cout << label << " ";
	}
	std::cout << std::endl;

	std::cout << "Properties: " << std::endl;
	for (const auto &property : nodes[nodePK].properties) {
		std::cout << property.first << ": " << property.second << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Edges: ";
	for (const auto &edgePK : nodes[nodePK].edges) {
		std::cout << edgePK << " ";
	}
	std::cout << std::endl;
}

void Graph::printEdge(EdgePK edgePK) const
{
	std::cout << "EdgePK: " << edgePK << std::endl;
	std::cout << "Type: " << edges[edgePK].type << std::endl;
	std::cout << "From: " << edges[edgePK].from << std::endl;
	std::cout << "To: " << edges[edgePK].to << std::endl;

	std::cout << "Properties: " << std::endl;
	for (const auto &property : edges[edgePK].properties) {
		std::cout << property.first << ": " << property.second << std::endl;
	}
	std::cout << std::endl;
}
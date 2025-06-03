#include "graph.hpp"

#include <iostream>
#include <variant>
#include <string>

void Graph::printNode(NodePK nodePK) const
{
	// std::cout << "NodePK: " << nodePK << std::endl;
	// std::cout << "Labels: " << std::endl;
	// for (const auto &label : nodes.search(nodePK)->labels) {
	// 	std::cout << label << " ";
	// }
	// std::cout << std::endl;

	// std::cout << "Properties: " << std::endl;
	// for (const auto &property : nodes.search(nodePK)->properties) {
	// 	std::cout << property.first << ": " << property.second << std::endl;
	// }
	// std::cout << std::endl;

	// std::cout << "Edges: ";
	// for (const auto &edgePK : nodes.search(nodePK)->edges) {
	// 	std::cout << edgePK << " ";
	// }
	std::cout << std::endl;
}

void Graph::printEdge(EdgePK edgePK) const
{
	// std::cout << "EdgePK: " << edgePK << std::endl;
	// std::cout << "Type: " << edges.search(edgePK)->type << std::endl;
	// std::cout << "From: " << edges.search(edgePK)->from << std::endl;
	// std::cout << "To: " << edges.search(edgePK)->to << std::endl;

	// std::cout << "Properties: " << std::endl;
	// for (const auto &property : edges.search(edgePK)->properties) {
	// 	std::cout << property.first << ": " << property.second << std::endl;
	// }
	std::cout << std::endl;
}

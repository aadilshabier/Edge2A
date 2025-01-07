#include <iostream>

#include "graphdb.hpp"

int main()
{
	GraphDB graph;

	NodePK node1 = graph.newNode({"Person"}, {{"name", "Aadil"}});
	NodePK node2 = graph.newNode({"Person"}, {{"name", "Calvin"}});

	EdgePK edge1 = graph.newEdge("friends", node1, node2);

	graph.saveToFile("db.json");

	return 0;
}

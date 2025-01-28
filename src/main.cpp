#include <iostream>

#include "graphdb.hpp"

int main()
{
	GraphDB graph;

	NodePK node1 = graph.createNode({"Person"}, {{"name", "Aadil"}});
	NodePK node2 = graph.createNode({"Person"}, {{"name", "Calvin"}});
	NodePK node3 = graph.createNode({"Person"}, {{"name", "Rahul"}});
	NodePK node4 = graph.createNode({"Person"}, {{"name", "Rohith"}});
	NodePK node5 = graph.createNode({"Person"}, {{"name", "Devansh"}});

	EdgePK edge1 = graph.createEdge("follows", node1, node2);

	graph.saveToFile("db.json");

	return 0;
}

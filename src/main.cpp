#include <iostream>

#include "graphdb.hpp"

int main()
{
	GraphDB graph;

	auto node1 = graph.createNode({"Person"}, {{"name", "Aadil"}, {"age", 211}});
	auto node2 = graph.createNode({"Person"}, {{"name", "Calvin"}});
	auto node3 = graph.createNode({"Person"}, {{"name", "Rahul"}});
	auto node4 = graph.createNode({"Person"}, {{"name", "Rohith"}});
	auto node5 = graph.createNode({"Person"}, {{"name", "Devansh"}});
	std::vector<Data> ls = {"Hello", "World"};
	auto node6 = graph.createNode({"NotPerson"}, {{"id", 4122}, {"flt", -122.2f}, {"ls", ls}});
	auto edge1 = graph.createEdge("FOLLOWS", node1, node2);

	graph.saveToFile("db.json");

	return 0;
}

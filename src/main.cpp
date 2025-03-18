#include <iostream>
#include "graphdb.hpp"

int main()
{
	GraphDB graph;

	graph.parseCypherScript("../cypherScripts/movies.cypher");

	std::string personAlias = "TomH";
	NodePK personPK = graph.getNodePKByAlias(personAlias);

	std::cout << "PK: " << personPK << std::endl;
	std::cout << "Label: " << *graph.graph.nodes[personPK].labels.begin() << std::endl;
	std::cout << "Name: " << std::get<DataStringType>(graph.graph.nodes[personPK].properties["name"]) << std::endl;

	return 0;
}

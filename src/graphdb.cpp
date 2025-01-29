#include "graphdb.hpp"

NodePK GraphDB::createNode(std::unordered_set<std::string> labels,
						std::unordered_map<std::string,std::string> properties)
{
	return graph.createNode(labels, properties);
}

EdgePK GraphDB::createEdge(std::string type, NodePK from, NodePK to,
						std::unordered_map<std::string,std::string> properties)
{
	return graph.createEdge(type, from, to, properties);
}

#include "graphdb.hpp"

#include <cassert>
#include <iostream>

NodePK GraphDB::createNode(std::unordered_set<std::string> labels,
				std::unordered_map<std::string, Data> properties, std::string alias)
{
	NodePK nodePK = graph.createNode(labels, properties);
	if (alias != "") {
		aliasToNodePKMap[alias] = nodePK; // Add alias to map if provided
	}
	return nodePK;
}

NodePK GraphDB::getNodePKByAlias(const std::string &alias) const
{
	// Search within map
	if (const auto it = aliasToNodePKMap.find(alias); it != aliasToNodePKMap.end()) {
		return it->second;
	}

	// Node not found
	std::cerr << "ERROR: Node not found" << std::endl;
	return -1;
}

EdgePK GraphDB::createEdge(std::string type, NodePK from, NodePK to,
						std::unordered_map<std::string, Data> properties)
{
	return graph.createEdge(type, from, to, properties);
}

EdgePK GraphDB::createEdgeByAlias(const std::string &type, const std::string &fromAlias, const std::string &toAlias,
								  std::unordered_map<std::string, Data> properties)
{
	NodePK from = getNodePKByAlias(fromAlias);
	NodePK to = getNodePKByAlias(toAlias);
	if (from == -1 or to == -1) {
		return -1; // Node not found
	}
	return graph.createEdge(type, from, to, properties);
}

void GraphDB::parseCypherScript(const std::string &filename) {
	Parser parser;
	parser.parseCypherScript(filename, *this);
}

#include "graphdb.hpp"

#include <cassert>
#include <iostream>

NodePK GraphDB::createNode(std::unordered_set<std::string> labels,
						std::unordered_map<std::string,std::string> properties, std::string alias)
{
	NodePK nodePK = graph.createNode(labels, properties);
	if (alias != "") {
		aliasToNodePKMap[alias] = nodePK; // Add alias to map if provided
	}
	return nodePK;
}

NodePK GraphDB::getNodePKByAlias(std::string alias)
{
	// Search within map
	if (aliasToNodePKMap.find(alias) != aliasToNodePKMap.end()) {
		return aliasToNodePKMap[alias];
	}

	// Node not found
	std::cerr << "ERROR: Node not found" << std::endl;
	return -1;
}

EdgePK GraphDB::createEdge(std::string type, NodePK from, NodePK to,
						std::unordered_map<std::string,std::string> properties)
{
	return graph.createEdge(type, from, to, properties);
}

EdgePK GraphDB::createEdgeByAlias(std::string type, std::string fromAlias, std::string toAlias,
						std::unordered_map<std::string,std::string> properties)
{
	NodePK from = getNodePKByAlias(fromAlias);
	NodePK to = getNodePKByAlias(toAlias);
	if (from == -1 or to == -1) {
		return -1; // Node not found
	}
	return graph.createEdge(type, from, to, properties);
}

static bool matchNode(const MatchNode &nodeA, const Node &nodeB)
{
	assert(nodeA.edges.size() == 0);

	for (const auto &label : nodeA.labels) {
		if (not nodeB.labels.contains(label)) {
			return false;
		}
	}

	for (const auto &property : nodeA.properties) {
		auto it = nodeB.properties.find(property.first);
		if (it == nodeB.properties.end() or property.second != it->second) {
			return false;
		}
	}

	return true;
}

MatchResults GraphDB::match(MatchPattern pattern, WhereExp where, MatchResultFmt resultFmt)
{
	assert(pattern.numNodes()<2 && "Only single nodes supported");
	// assert(pattern.isConnected() && "Graph should be connected");

	MatchResults results;
	const auto &nodeA = pattern.nodes[0];
	for (const auto &nodeB : graph.nodes) {
		if (not matchNode(nodeA, nodeB)) {
			continue;
		}
		auto &result = results.emplace_back();
	    result.createNode(nodeB.labels, nodeB.properties);
	}

	return results;
}

void GraphDB::loadCypherScript(const std::string &filename) {
	Parser parser;
	parser.parseCypherScript(filename, *this);
}

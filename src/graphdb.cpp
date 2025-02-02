#include "graphdb.hpp"

#include <cassert>

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

#include "graphdb.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void GraphDB::loadFromFile(const std::string &filename)
{
	std::ifstream file(filename);
	auto j = json::parse(file);

	for (const auto &node : j["nodes"]) {
		createNode(node["labels"], node["properties"]);
	}

	for (const auto &edge : j["edges"]) {
		auto edgeId = createEdge(edge["type"], edge["properties"], edge["from"], edge["to"]);
	    graph.nodes[edge["from"]].edges.push_back(edgeId);
	}
}

void GraphDB::saveToFile(const std::string &filename) const
{
	std::string g = getGraphAsStr();

	std::ofstream file(filename);
	file << g;
}

std::string GraphDB::getGraphAsStr() const
{
	json j;

	auto &serNodes = j["nodes"] = json::array();
	for (const auto &node : graph.nodes) {
		json nodeJson;
		nodeJson["labels"] = node.labels;
		nodeJson["properties"] = node.properties;
		serNodes.push_back(nodeJson);
	}

	auto &serEdges = j["edges"] = json::array();
	for (const auto &edge : graph.edges) {
		json edgeJson;
		edgeJson["type"] = edge.type;
		edgeJson["properties"] = edge.properties;
		edgeJson["from"] = edge.from;
		edgeJson["to"] = edge.to;
		serEdges.push_back(edgeJson);
	}

	return j.dump(2);
}

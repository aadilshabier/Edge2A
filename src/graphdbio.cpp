#include "graphdb.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void GraphDB::loadFromFile(const std::string &filename)
{
	std::ifstream file(filename);
	auto j = json::parse(file);

	for (const auto &node : j["nodes"]) {
		newNode(node["labels"],
				node["properties"]);
	}

	for (const auto &edge : j["edges"]) {
		auto edgeId = newEdge(edge["type"], edge["properties"], edge["from"], edge["to"]);
	    nodes[edge["from"]].edges.push_back(edgeId);
	}
}

void GraphDB::saveToFile(const std::string &filename) const
{
	json j;

	auto &serNodes = j["nodes"] = json::array();
	for (const auto &node : nodes) {
		json nodeJson;
		nodeJson["labels"] = node.labels;
		nodeJson["properties"] = node.properties;
		serNodes.push_back(nodeJson);
	}

	auto &serEdges = j["edges"] = json::array();
	for (const auto &edge : edges) {
		json edgeJson;
		edgeJson["type"] = edge.type;
		edgeJson["properties"] = edge.properties;
		edgeJson["from"] = edge.from;
		edgeJson["to"] = edge.to;
		serEdges.push_back(edgeJson);
	}

	std::ofstream file(filename);
	file << j;
}

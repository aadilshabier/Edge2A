#include "graphdb.hpp"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// using std::variant in nlohmann::json as proposed by this magician: https://github.com/nlohmann/json/issues/1261#issuecomment-2048770747
namespace utils {
	namespace details {
		template <typename T>
		constexpr auto make_type_name();
		using namespace std::string_view_literals;

		template<> constexpr auto make_type_name<DataStringType>() { return "string"sv;}
		template<> constexpr auto make_type_name<DataIntType>() { return "int"sv;}
		template<> constexpr auto make_type_name<DataRealType>() { return "real"sv;}
		template<> constexpr auto make_type_name<DataArrayType>() { return "array"sv;}

	} // details

	/**
	 * Convert type T into constexpr string.
	 */
	template<typename T>
	constexpr auto type_name_sv = details::make_type_name<T>();
} // utils

namespace nlohmann
{
	namespace {
		template <typename T, typename... Ts>
		bool variant_from_json(const nlohmann::json& j, std::variant<Ts...>& data) {
			if (j.at("type").get<std::string_view>() != utils::type_name_sv<T>)
				return false;
			data = j.at("data").get<T>();
			return true;
		}
	} // namespace

	template <typename... Ts>
	struct adl_serializer<std::variant<Ts...>>
	{
		using Variant = std::variant<Ts...>;
		using Json = nlohmann::json;

		static void to_json(Json& j, const Variant& data) {
			std::visit(
					   [&j](const auto& v) {
						   using T = std::decay_t<decltype(v)>;
						   j["type"] = utils::type_name_sv<T>;
						   j["data"] = v;
					   },
					   data);
		}

		static void from_json(const Json& j, Variant& data) {
			// Call variant_from_json for all types, only one will succeed
			bool found = (variant_from_json<Ts>(j, data) || ...);
			if (!found)
				throw std::bad_variant_access();
		}
	};
} // nlohmann

// Holy hack!
void to_json(json& j, const Data& data) {
	auto v = static_cast<const DataVariant*>(&data); // upcast
	j = *v;
}

void from_json(const json& j, Data& data) {
	data = DataVariant(j);
}

void GraphDB::loadFromFile(const std::string &filename)
{
	std::ifstream file(filename);
	auto j = json::parse(file);

	for (const auto &node : j["nodes"]) {
		createNode(node["labels"], node["properties"]);
	}

	for (const auto &edge : j["edges"]) {
		auto edgeId = createEdge(edge["type"], edge["properties"], edge["from"], edge["to"]);
	    graph.nodes.search(edge["from"])->edges.push_back(edgeId);
	}
}

void GraphDB::saveToFile(const std::string &filename) const
{
	std::ofstream file(filename);
	getGraphAsStream(file);
}

void GraphDB::getGraphAsStream(std::ostream &os) const
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

	os << j.dump(2);
}

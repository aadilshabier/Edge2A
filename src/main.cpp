#include <iostream>
#include "graphdb.hpp"

#include "httplib.h"
#include <nlohmann/json.hpp>

// Operator "<<" overloading for Data
std::ostream& operator<<(std::ostream& os, const Data& data) {
    std::visit([&os](const auto& value) {
        using Type = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<Type, DataArrayType>) {
            os << "[ ";
            for (const auto& elem : value) {
                os << elem << " ";  // Recursively calls operator<<
            }
            os << "]";
        } else {
            os << value;
        }
    }, data);
    return os;
}

EdgePK buildEdge(MatchPattern &pattern, std::string role, NodePK from, NodePK to)
{
	if (role == "Any") {
		role = "";
	} else if (role == "Actor") {
		role = "ACTED_IN";
	} else if (role == "Director") {
		role = "DIRECTED";
	} else if (role == "Producer") {
		role = "PRODUCED";
	} else if (role == "Writer") {
		role = "WROTE";
	}
	return pattern.createEdge(role, from, to);
}

int main()
{
	GraphDB graph;
	httplib::Server svr;

	graph.parseCypherScript("../cypherScripts/movies.cypher");

	svr.Options("/.*", [](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204; // No Content
    });

	svr.Post("/movies", [&graph](const httplib::Request& req, httplib::Response& res) {
		MatchPattern pattern;
		NodePK n0 = pattern.createNode({"Movie"});

		auto names_roles = nlohmann::json::parse(req.body);
		for (const auto &name_role : names_roles) {
			const std::string name = name_role["name"];
			const std::string role = name_role["role"];

			auto n = pattern.createNode({"Person"}, {{"name", name}});
			auto e = buildEdge(pattern, role, n, n0);
		}
		auto matcher = VF2Matcher(graph.graph, pattern);
		auto mappings = matcher.match();

		auto results = nlohmann::json::array();
		for (const auto &mapping : mappings) {
			NodePK mappedNode = mapping[n0];
			auto title = std::get<DataStringType>(graph.graph.nodes[mappedNode]
												 .properties["title"]);
			auto year = std::get<DataIntType>(graph.graph.nodes[mappedNode]
											  .properties["released"]);
			auto tagline = std::get<DataStringType>(graph.graph.nodes[mappedNode]
												 .properties["tagline"]);
			auto result = nlohmann::json::object({{"title", title},{"year", year},
												  {"tagline", tagline}});
			results.push_back(result);
		}

        res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
		res.set_content(results.dump(), "application/json");
    });

	svr.listen("localhost", 3001);

	return 0;
}

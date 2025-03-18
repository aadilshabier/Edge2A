#include <gtest/gtest.h>

#include "graphdb.hpp"

namespace {
class GraphDBMatchingVF2Test : public testing::Test {
protected:
	GraphDB db;

	GraphDBMatchingVF2Test() {
		db.parseCypherScript("../..//cypherScripts/movies.cypher"); // Parses and loads movies.cypher
	}
};

TEST_F(GraphDBMatchingVF2Test, MatchNodeSimple) {
	MatchPattern pattern;
	NodePK n2 = pattern.createNode({"Person"}, {{"name", "Keanu Reeves"}});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	auto mappings = matcher.match();
	ASSERT_EQ(mappings.size(), 1) << "Incorrect number of mappings found";

	auto mapping = *mappings.begin();
	NodePK mappedNode = mapping[n2];
	auto born = std::get<DataIntType>(db.graph.nodes[mappedNode].properties["born"]);
	EXPECT_EQ(born, 1964) << "Incorrect year of birth";
}

TEST_F(GraphDBMatchingVF2Test, MatchNodesAndEdges) {
	// Tom Hanks has both directed and acted in only one movie
	MatchPattern pattern;
	NodePK tomHanks_2 = pattern.createNode({"Person"}, {{"name", "Tom Hanks"}});
	NodePK movie_2 = pattern.createNode({"Movie"}, {});
	EdgePK e1_2 = pattern.createEdge("ACTED_IN", tomHanks_2, movie_2, {});
	EdgePK e2_2 = pattern.createEdge("DIRECTED", tomHanks_2, movie_2, {});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	auto mappings = matcher.match();
	ASSERT_EQ(mappings.size(), 1) << "Incorrect number of mappings found";

	auto mapping = *mappings.begin();
	NodePK mappedMovie = mapping[movie_2];
	auto title = std::get<DataStringType>(db.graph.nodes[mappedMovie].properties["title"]);
	EXPECT_EQ(title, "That Thing You Do") << "Incorrect movie title";
}

TEST_F(GraphDBMatchingVF2Test, MatchNodeWithMultipleResults) {
	// Two people directed the movie: The Matrix
	MatchPattern pattern;
	NodePK person_2 = pattern.createNode({"Person"}, {});
	NodePK movie_2 = pattern.createNode({"Movie"}, {{"title", "The Matrix"}});
	EdgePK e2 = pattern.createEdge("DIRECTED", person_2, movie_2, {});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	auto mappings = matcher.match();
	ASSERT_EQ(mappings.size(), 2) << "Incorrect number of mappings found";

	std::unordered_set<std::string> names = {"Lana Wachowski", "Lilly Wachowski"};
	std::unordered_set<std::string> mappedNames;
	for (auto mapping : mappings) {
		NodePK mappedPerson = mapping[person_2];
		auto name = std::get<DataStringType>(db.graph.nodes[mappedPerson].properties["name"]);
		mappedNames.insert(name);
	}

	EXPECT_EQ(mappedNames, names) << "Incorrect names of directors";
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

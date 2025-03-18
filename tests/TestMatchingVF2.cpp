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

TEST_F(GraphDBMatchingVF2Test, MatchNode) {
	MatchPattern pattern;
	NodePK n2 = pattern.createNode({"Person"}, {{"name", "Keanu Reeves"}});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	ASSERT_EQ(matcher.match(), true) << "Match not found";

	NodePK mappedNode = matcher.getMapping(n2);
	auto born = std::get<DataIntType>(db.graph.nodes[mappedNode].properties["born"]);
	EXPECT_EQ(born, 1964) << "Incorrect year of birth";
}

TEST_F(GraphDBMatchingVF2Test, MatchNodeAndEdges) {
	// Tom Hanks has both directed and acted in only one movie
	MatchPattern pattern;
	NodePK tomHanks_2 = pattern.createNode({"Person"}, {{"name", "Tom Hanks"}});
	NodePK movie_2 = pattern.createNode({"Movie"}, {});
	EdgePK e1_2 = pattern.createEdge("ACTED_IN", tomHanks_2, movie_2, {});
	EdgePK e2_2 = pattern.createEdge("DIRECTED", tomHanks_2, movie_2, {});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	ASSERT_EQ(matcher.match(), true) << "Match not found";

	NodePK mappedMovie = matcher.getMapping(movie_2);
	auto title = std::get<DataStringType>(db.graph.nodes[mappedMovie].properties["title"]);
	EXPECT_EQ(title, "That Thing You Do") << "Incorrect movie title";
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

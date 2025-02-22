#include <gtest/gtest.h>

#include "graphdb.hpp"

namespace {
class GraphDBParsingTest : public testing::Test {
protected:
	GraphDB db;

	GraphDBParsingTest() {
		db.loadCypherScript("../../cypherScripts/movies.cypher"); // Parses and loads movies.cypher
	}
};

TEST_F(GraphDBParsingTest, ParseCypherNode) {
	std::string personAlias = "TomH";
	NodePK personPK = db.getNodePKByAlias(personAlias);
	ASSERT_NE(personPK, -1); // Check if the node exists
	int expectedYear = 1956;
	ASSERT_NE(db.graph.nodes[personPK].properties.find("born"), db.graph.nodes[personPK].properties.end()); // Check if the property exists
	int outputYear = std::stoi(std::get<DataStringType>(db.graph.nodes[personPK].properties["born"].variant));
	EXPECT_EQ(expectedYear, outputYear);
}

TEST_F(GraphDBParsingTest, ParseCypherEdge) {
	std::string personAlias = "TomH";
	NodePK personPK = db.getNodePKByAlias(personAlias);
	ASSERT_NE(personPK, -1); // Check if the node exists
	std::string moviesAlias = "TheGreenMile";
	NodePK moviePK = db.getNodePKByAlias(moviesAlias);
	ASSERT_NE(moviePK, -1); // Check if the node exists
	std::string edgeType = "ACTED_IN";
	EdgePK edgePK = db.graph.getEdgeByNodesAndType(personPK, moviePK, edgeType);
	ASSERT_NE(edgePK, -1); // Check if the edge exists
	
	std::string expectedRole = "Paul Edgecomb";
	ASSERT_NE(db.graph.edges[edgePK].properties.find("roles"), db.graph.edges[edgePK].properties.end()); // Check if the property exists
	std::string outputRole = std::get<DataStringType>(db.graph.edges[edgePK].properties["roles"].variant);
	EXPECT_EQ(expectedRole, outputRole);
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
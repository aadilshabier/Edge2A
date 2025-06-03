#include <gtest/gtest.h>

#include "graphdb.hpp"

namespace {
class GraphDBParsingTest : public testing::Test {
protected:
	GraphDB db;

	GraphDBParsingTest() {
		db.parseCypherScript("../..//cypherScripts/movies.cypher"); // Parses and loads movies.cypher
	}
};

TEST_F(GraphDBParsingTest, ParseCypherNode) {
	std::string personAlias = "TomH";
	NodePK personPK = db.getNodePKByAlias(personAlias);
	ASSERT_NE(personPK, -1) << "Node with id 'TomH' not found";
	int expectedYear = 1956;
	ASSERT_NE(db.graph.nodes.search(personPK)->properties.find("born"), db.graph.nodes.search(personPK)->properties.end()) << "Property 'born' was not found";
	auto outputYear = std::get<DataIntType>(db.graph.nodes.search(personPK)->properties["born"]);
	EXPECT_EQ(expectedYear, outputYear) << "Expected and actual birth year are different";
}

TEST_F(GraphDBParsingTest, ParseCypherEdge) {
	std::string personAlias = "TomH";
	NodePK personPK = db.getNodePKByAlias(personAlias);
	ASSERT_NE(personPK, -1) << "Node with id 'TomH' not found";
	std::string moviesAlias = "TheGreenMile";
	NodePK moviePK = db.getNodePKByAlias(moviesAlias);
	ASSERT_NE(moviePK, -1) << "Node with id 'TheGreenMile' not found";
	std::string edgeType = "ACTED_IN";
	EdgePK edgePK = db.graph.getEdgeByNodesAndType(personPK, moviePK, edgeType);
	ASSERT_NE(edgePK, -1) << "Edge was not found";
	
	DataArrayType expectedRoles{"Paul Edgecomb"};
	ASSERT_NE(db.graph.edges.search(edgePK)->properties.find("roles"), db.graph.edges.search(edgePK)->properties.end()) << "Property 'roles' does not exist";
	auto outputRoles = std::get<DataArrayType>(db.graph.edges.search(edgePK)->properties["roles"]);
	EXPECT_EQ(expectedRoles, outputRoles) << "Expected and output roles are different";
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

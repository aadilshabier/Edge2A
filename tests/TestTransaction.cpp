#include <gtest/gtest.h>

#include "graphdb.hpp"

namespace {
class GraphDBTransactionTest : public testing::Test {
protected:
	GraphDB db;
	
	GraphDBTransactionTest() {
		db.createNode({"Movie"}, {{"released", "1999"}, {"name", "The Matrix"}}, "TheMatrix");
		db.createNode({"Person"}, {{"born", "1964"}, {"name", "Keanu Reeves"}}, "Keanu");
		db.createEdgeByAlias("ACTED_IN", "Keanu", "TheMatrix", {{"roles", "Neo"}});
	}	
};

TEST_F(GraphDBTransactionTest, TxCommit) {
	db.beginTransaction();
	db.createNode({"Person"}, {{"born", "1964"}, {"name", "Carrie-Anne Moss"}}, "Carrie");
	db.createEdgeByAlias("ACTED_IN", "Carrie", "TheMatrix", {{"roles", "Trinity"}});
	db.commitTransaction();

	// Check if the number of node and edges is intact
	ASSERT_EQ(db.graph.numNodes(), 3) << "Incorrect number of nodes after transaction";
	ASSERT_EQ(db.graph.numEdges(), 2) << "Incorrect number of edges after transaction";

	// Check for graph consistency
	MatchPattern pattern;
	NodePK n1 = pattern.createNode({"Movie"}, {{"name", "The Matrix"}});
	NodePK n2 = pattern.createNode({"Person"}, {{"name", "Keanu Reeves"}});
	NodePK n3 = pattern.createNode({"Person"}, {{"name", "Carrie-Anne Moss"}});
	EdgePK e1 = pattern.createEdge("ACTED_IN", n2, n1, {{"roles", "Neo"}});
	EdgePK e2 = pattern.createEdge("ACTED_IN", n3, n1, {{"roles", "Trinity"}});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	auto mappings = matcher.match();
	ASSERT_EQ(mappings.size(), 1) << "Incorrect number of mappings found";	
}

TEST_F(GraphDBTransactionTest, TxRollback) {
	db.beginTransaction();
	db.createNode({"Person"}, {{"born", "1964"}, {"name", "Carrie-Anne Moss"}}, "Carrie");
	db.createEdgeByAlias("ACTED_IN", "Carrie", "TheMatrix", {{"roles", "Trinity"}});
	db.rollbackTransaction();

	// Check if the number of node and edges is intact
	ASSERT_EQ(db.graph.numNodes(), 2) << "Incorrect number of nodes after transaction";
	ASSERT_EQ(db.graph.numEdges(), 1) << "Incorrect number of edges after transaction";

	// Check for graph consistency
	MatchPattern pattern;
	NodePK n1 = pattern.createNode({"Movie"}, {{"name", "The Matrix"}});
	NodePK n2 = pattern.createNode({"Person"}, {{"name", "Keanu Reeves"}});
	EdgePK e1 = pattern.createEdge("ACTED_IN", n2, n1, {{"roles", "Neo"}});

	VF2Matcher matcher = VF2Matcher(db.graph, pattern);
	auto mappings = matcher.match();
	ASSERT_EQ(mappings.size(), 1) << "Incorrect number of mappings found";	
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

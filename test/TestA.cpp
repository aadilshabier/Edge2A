#include <gtest/gtest.h>
#include "graphdb.hpp"

TEST(ExpectedGraphStates, AddingNodesAndEdges) {
    GraphDB graph;

	NodePK node1 = graph.newNode({"Person"}, {{"name", "Aadil"}});
	NodePK node2 = graph.newNode({"Person"}, {{"name", "Calvin"}});
	EdgePK edge1 = graph.newEdge("friends", node1, node2);

	std::string g = graph.getGraphAsStr();
    std::string expected = "{\"edges\":[{\"from\":0,\"properties\":{},\"to\":1,\"type\":\"friends\"}],\"nodes\":[{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Aadil\"}},{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Calvin\"}}]}";
    EXPECT_EQ(g, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

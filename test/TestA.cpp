#include "graphdb.hpp"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(ExpectedGraphStates, AddingNodesAndEdges) {
    GraphDB graph;

	NodePK node1 = graph.createNode({"Person"}, {{"name", "Aadil"}});
	NodePK node2 = graph.createNode({"Person"}, {{"name", "Calvin"}});
	EdgePK edge1 = graph.createEdge("friends", node1, node2);

	std::string g = graph.getGraphAsStringStream().str();
    auto j = json::parse(g);
    
    std::string expected_g = "{\"edges\":[{\"from\":0,\"properties\":{},\"to\":1,\"type\":\"friends\"}],\"nodes\":[{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Aadil\"}},{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Calvin\"}}]}";
    auto expected_j = json::parse(expected_g);
    EXPECT_EQ(expected_j, j);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

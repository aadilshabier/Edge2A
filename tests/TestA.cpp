#include "graphdb.hpp"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

TEST(ExpectedGraphStates, AddingNodesAndEdges) {
    GraphDB graph;

	NodePK node1 = graph.createNode({"Person"}, {{"name", "Aadil"}});
	NodePK node2 = graph.createNode({"Person"}, {{"name", "Calvin"}});
	EdgePK edge1 = graph.createEdge("friends", node1, node2);

    std::stringstream ss;
	graph.getGraphAsStream(ss);
    auto j = json::parse(ss.str());
    
    std::string expectedGraph = "{\"edges\":[{\"from\":0,\"properties\":{},\"to\":1,\"type\":\"friends\"}],\"nodes\":[{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Aadil\"}},{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Calvin\"}}]}";
    auto expectedJson = json::parse(expectedGraph);
    EXPECT_EQ(expectedJson, j);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

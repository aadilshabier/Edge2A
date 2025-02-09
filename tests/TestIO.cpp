#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "graphdb.hpp"

namespace {
using json = nlohmann::json;

class GraphDBIOTest : public testing::Test {
protected:
	GraphDB graph;

	GraphDBIOTest() {
		NodePK node1 = graph.createNode({"Person"}, {{"name", "Aadil"}});
		NodePK node2 = graph.createNode({"Person"}, {{"name", "Calvin"}});
		graph.createEdge("friends", node1, node2);
	}
};

TEST_F(GraphDBIOTest, SerializeToJson) {
    std::string expectedGraph = "{\"edges\":[{\"from\":0,\"properties\":{},\"to\":1,\"type\":\"friends\"}],\"nodes\":[{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Aadil\"}},{\"labels\":[\"Person\"],\"properties\":{\"name\":\"Calvin\"}}]}";
    auto expectedJson = json::parse(expectedGraph);

	std::stringstream ss;
	graph.getGraphAsStream(ss);
    auto graphJson = json::parse(ss);

    EXPECT_EQ(expectedJson, graphJson);
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

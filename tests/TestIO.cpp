#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "graphdb.hpp"

namespace {
using json = nlohmann::json;

class GraphDBIOTest : public testing::Test {
protected:
	GraphDB graph;

	GraphDBIOTest() {
		NodePK node1 = graph.createNode({"Person"}, {{"name", "Aadil"}, {"age", 21.5f}});
		std::vector<Data> nicknames = {"Dom", "Callu"};
		NodePK node2 = graph.createNode({"Person"}, {{"name", "Calvin"}, {"legs", 2}, {"nicknames", nicknames}});
		graph.createEdge("friends", node1, node2);
	}
};

TEST_F(GraphDBIOTest, SerializeToJson) {
    std::string expectedGraph = R"""(
{"edges":
[{"from":0,"properties":{},"to":1,"type":"friends"}],
"nodes":[
{"labels":["Person"],"properties":{"age":{"data":21.5,"type":"real"},"name":{"data":"Aadil","type":"string"}}},
{"labels":["Person"],"properties":{"name":{"data":"Calvin","type":"string"},"nicknames":{"data":[{"data":"Dom","type":"string"},{"data":"Callu","type":"string"}],"type":"array"}, "legs": {"data": 2, "type": "int"}}}]})""";
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

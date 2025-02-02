#include <gtest/gtest.h>

#include "graphdb.hpp"

namespace {
class GraphDBMatchingTest : public testing::Test {
protected:
	GraphDB graph;
	MatchPattern pattern;

	GraphDBMatchingTest() {
		auto node1 = graph.createNode({"Person"}, {{"name", "Aadil"}});
		auto node2 = graph.createNode({"Person"}, {{"name", "Calvin"}});
		auto node3 = graph.createNode({"Person"}, {{"name", "Rahul"}});
		auto node4 = graph.createNode({"Person"}, {{"name", "Rohith"}});
		auto node5 = graph.createNode({"Person"}, {{"name", "Devansh"}});
		auto node6 = graph.createNode({"NotPerson"}, {{"name", "Aadil"}});
		auto node7 = graph.createNode({"NotPerson"}, {{"email", "example@gmail.com"}});
		auto edge1 = graph.createEdge("FOLLOWS", node1, node2);
	}
};

TEST_F(GraphDBMatchingTest, AllNodes) {
	pattern.createNode();

	auto res = graph.match(pattern, nullptr, nullptr);
	EXPECT_EQ(res.size(), 7) << "Wrong number of results recieved: " << res.size();
}

TEST_F(GraphDBMatchingTest, AllPersons) {
	pattern.createNode({"Person"});

	auto res = graph.match(pattern, nullptr, nullptr);
	EXPECT_EQ(res.size(), 5) << "Wrong number of results recieved: " << res.size();
}

TEST_F(GraphDBMatchingTest, PersonAadil) {
	pattern.createNode({"Person"}, {{"name", "Aadil"}});

	auto res = graph.match(pattern, nullptr, nullptr);
	EXPECT_EQ(res.size(), 1) << "Wrong number of results recieved: " << res.size();
}

TEST_F(GraphDBMatchingTest, PersonCalvin) {
	pattern.createNode({"Person"}, {{"name", "Calvin"}});

	auto res = graph.match(pattern, nullptr, nullptr);
	EXPECT_EQ(res.size(), 1) << "Wrong number of results recieved: " << res.size();
}

TEST_F(GraphDBMatchingTest, AnyAadil) {
	pattern.createNode({}, {{"name", "Aadil"}});

	auto res = graph.match(pattern, nullptr, nullptr);
	EXPECT_EQ(res.size(), 2) << "Wrong number of results recieved: " << res.size();
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

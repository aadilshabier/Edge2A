#include <gtest/gtest.h>

#include "bptree/bptree.hpp"
#include <vector>

namespace {
class BPTreeTest : public testing::Test {
protected:
	BPlusTree<int, int> bptree;
	std::vector<int> keys;

	BPTreeTest() : bptree(3, 3) {
		keys = {1, 4, 7, 10, 17, 21, 31, 25, 19, 20, 28, 42};

		// Add keys
		for (int key : keys) {
			bptree.insert(key, key);
		}
	}
};

TEST_F(BPTreeTest, Insertion) {
	// Checks for expected structure after insertions
	
	// Key / Value checks
	EXPECT_EQ(bptree.root->keys[0], 20);

	EXPECT_EQ(bptree.root->children[0]->keys[0], 7);
	EXPECT_EQ(bptree.root->children[0]->keys[1], 17);

	EXPECT_EQ(bptree.root->children[1]->keys[0], 25);
	EXPECT_EQ(bptree.root->children[1]->keys[1], 31);

	EXPECT_EQ(bptree.root->children[0]->children[2]->values[1], 19);
	EXPECT_EQ(bptree.root->children[1]->children[1]->values[0], 25);

	// Is leaf checks
	EXPECT_EQ(bptree.root->children[0]->children[1]->is_leaf, true);
	EXPECT_EQ(bptree.root->children[1]->is_leaf, false);

	// Size checks
	EXPECT_EQ(bptree.root->size, 1);
	EXPECT_EQ(bptree.root->children[0]->size, 2);

	// Parent checks
	EXPECT_EQ(bptree.root->children[0]->parent, bptree.root);
	EXPECT_EQ(bptree.root->children[0]->children[1]->parent, bptree.root->children[0]);

	// Next pointer checks
	EXPECT_EQ(bptree.root->children[0]->children[1]->next, bptree.root->children[0]->children[2]);
}

TEST_F(BPTreeTest, Search) {
	std::vector<int> keys_present = {20, 17, 28};
	std::vector<int> keys_absent = {5, 15};
	
	for (int key : keys_present) {
		EXPECT_EQ(*bptree.search(key), key);
	}

	for (int key : keys_absent) {
		EXPECT_EQ(bptree.search(key), nullptr);
	}
}

TEST_F(BPTreeTest, Iteration) {
	std::vector<int> expected_values = {1, 4, 7, 10, 17, 19, 20, 21, 25, 28, 31, 42};
	
	int idx = 0;
	for (auto it = bptree.begin(); it != bptree.end(); ++it) {
		EXPECT_EQ(*it, expected_values[idx++]);
	}
}

TEST_F(BPTreeTest, Deletion) {
	std::vector<int> keys_to_delete = {21, 31, 20, 10, 7, 25, 42, 17, 19};
	
	for (int key : keys_to_delete) {
		bptree.remove(key);
	}

	// Checks for expected structure after deletions

	// Key / Value & Size checks
	EXPECT_EQ(bptree.root->keys[0], 4);
	EXPECT_EQ(bptree.root->keys[1], 28);
	EXPECT_EQ(bptree.root->size, 2);

	EXPECT_EQ(bptree.root->children[0]->keys[0], 1);
	EXPECT_EQ(bptree.root->children[0]->size, 1);

	EXPECT_EQ(bptree.root->children[1]->keys[0], 4);
	EXPECT_EQ(bptree.root->children[1]->size, 1);
	
	EXPECT_EQ(bptree.root->children[2]->keys[0], 28);
	EXPECT_EQ(bptree.root->children[2]->size, 1);

	// Is leaf checks
	EXPECT_EQ(bptree.root->is_leaf, false);
	EXPECT_EQ(bptree.root->children[1]->is_leaf, true);

	// Parent checks
	EXPECT_EQ(bptree.root->children[0]->parent, bptree.root);
	EXPECT_EQ(bptree.root->children[2]->parent, bptree.root);

	// Next pointer checks
	EXPECT_EQ(bptree.root->children[1]->next, bptree.root->children[2]);
}
} // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#ifndef TreeNode_HPP
#define TreeNode_HPP

#include <cstddef>

template <typename T, typename K>
struct TreeNode {
    bool is_leaf;
    std::size_t size; // Current number of keys/values
    K* keys; // Array of keys for navigation
    T* values; // Array of corresponding data objects (in case of leaf node)
    TreeNode<T, K>** children; // Array of child pointers
    TreeNode<T, K>* parent; // Parent pointer
    TreeNode<T, K>* next; // Leaf-to-leaf pointer for iteration

    TreeNode(std::size_t degree_inner, std::size_t degree_leaf, bool is_leaf)
        : is_leaf(is_leaf), size(0), parent(nullptr), next(nullptr) {

        if (is_leaf) {
            keys = new K[degree_leaf];
            values = new T[degree_leaf];
            children = nullptr;
        } else {
            keys = new K[degree_inner];
            values = nullptr;
            children = new TreeNode<T, K>*[degree_inner + 1];
            for (std::size_t i = 0; i < (degree_inner + 1); i++)
                children[i] = nullptr;
        }
    }

    ~TreeNode() {
        delete[] keys;
        if (is_leaf) {
            delete[] values;
        } else {
            delete[] children;
        }
    }
};

#endif

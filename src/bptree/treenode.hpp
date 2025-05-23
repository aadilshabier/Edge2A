#ifndef TreeNode_HPP
#define TreeNode_HPP

#include <cstddef>

template <typename T, typename K>
struct TreeNode {
    bool is_leaf;
    std::size_t size; // Current number of keys/values
    K* keys; // Array of keys for navigation
    T* values; // Array of values (actual data objects)
    TreeNode<T, K>** children; // Array of child pointers
    TreeNode<T, K>* parent; // Parent pointer
    TreeNode<T, K>* next; // Leaf-to-leaf pointer

    TreeNode(std::size_t degree_k, std::size_t degree_t, bool leaf)
        : is_leaf(leaf), size(0), parent(nullptr), next(nullptr) {
        
        keys = new K[degree_k];

        if (is_leaf) {
            values = new T[degree_t];
            children = nullptr;
        } else {
            values = nullptr;
            children = new TreeNode<T, K>*[degree_k + 1];
            for (std::size_t i = 0; i < degree; ++i)
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

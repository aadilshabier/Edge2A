#ifndef BPlusTreeIterator_H
#define BPlusTreeIterator_H

#include "treenode.hpp"

template <typename T, typename K>
class BPlusTreeIterator {
    TreeNode<T, K>* current_node;
    std::size_t index;

public:
    BPlusTreeIterator(TreeNode<T, K>* node = nullptr, std::size_t idx = 0)
        : current_node(node), index(idx) {}

    T& operator*() {
        return current_node->values[index];
    }

    BPlusTreeIterator& operator++() {
        if (!current_node) return *this;

        index++;
        if (index >= current_node->size) {
            current_node = current_node->next;
            index = 0;
        }

        return *this;
    }

    bool operator==(const BPlusTreeIterator& other) const {
        return current_node == other.current_node && index == other.index;
    }

    bool operator!=(const BPlusTreeIterator& other) const {
        return current_node != other.current_node || index != other.index;
    }
};

#endif

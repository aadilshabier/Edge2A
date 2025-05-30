#ifndef BPlusTree_H
#define BPlusTree_H

#include "treenode.hpp"
#include "bptreeIterator.hpp"

template <typename T, typename K>
class BPlusTree {
public:
    TreeNode<T, K>* root;
    std::size_t degree_inner; // Max number of internal keys/values
    std::size_t degree_leaf; // Max number of leaf keys/values

    BPlusTree(std::size_t _degree_inner, std::size_t _degree_leaf)
        : degree_inner(_degree_inner), degree_leaf(_degree_leaf), root(nullptr) {}
    ~BPlusTree() { cleanup(root); }

private:
    TreeNode<T, K>* searchNode(K key); // Traverse to the node where key belongs
    int findIndex(K* arr, K key, int len); // Index based on internal key comparison
    void insertInternal(K* keys, TreeNode<T, K>** children, K key,
            TreeNode<T, K>* child, int old_len, int idx); // Insert key/child into internal node
    void insertLeaf(K* keys, T* values, K key,
            T data, int old_len, int idx); // Insert key/value into leaf node
    
    void insertPar(TreeNode<T, K>* par, TreeNode<T, K>* child, K key); // Parent insertion
    void removePar(TreeNode<T, K>* node, int index, TreeNode<T, K>* par);

    void cleanup(TreeNode<T, K>* cursor); // Cleanup tree
    void printHelper(TreeNode<T, K>* cursor); // Print recursively

public:
    // Core functionality
    T* search(K key); // Retrieve data by key
    void insert(K key, T data); // Insert new data
    void remove(K key); // Remove data by key
    
    // Iterator support
    using bptIterator = BPlusTreeIterator<T, K>;
    bptIterator begin();  // First data item in the leftmost leaf
    bptIterator end();    // One-past-the-last element

    // Print
    void print(); // Print the full tree
};

#include "bptree.tpp"
#endif

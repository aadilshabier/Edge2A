#ifndef BPlusTree_H
#define BPlusTree_H

#include "treenode.hpp"
#include "bptreeIterator.hpp"

template <typename T, typename K>
class BPlusTree {
    TreeNode<T, K>* root;
    std::size_t degree_k; // Max number of keys
    std::size_t degree_t; // Max number of values

private:
    BPlusTree(std::size_t _degree_k, std::size_t _degree_t)
        : degree_k(_degree_k), degree_t(_degree_t), root(nullptr) {}
    ~BPlusTree() { cleanup(root); }

    TreeNode<T, K>* searchNode(K key); // Traverse to the node where key belongs
    int findIndex(T* arr, T data, int len); // Index based on internal key comparison
    T* valueInsert(T* arr, T data, int len, int index); // Insert value based on key
    TreeNode<T, K>** childInsert(TreeNode<T, K>** child_arr,
            TreeNode<T, K>* child, int len, int index); // Insert child pointer
    
    void insertPar(TreeNode<T, K>* par, TreeNode<T, K>* child, K key); // Parent insertion
    void removePar(TreeNode<T, K>* node, int index, TreeNode<T, K>* par);

    void cleanup(TreeNode<T, K>* cursor); // Cleanup tree
    void printHelper(TreeNode<T, K>* cursor); // Print recursively

public:
    T* search(K key); // Retrieve data by key
    void insert(T data, K key); // Insert new data
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

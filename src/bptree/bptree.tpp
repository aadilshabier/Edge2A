#include "bptree.hpp"

#include <iostream>
#include <cassert>

// Returns TreeNode where a given key is "supposed" to go
template <typename T, typename K>
TreeNode<T, K>* BPlusTree<T, K>::searchNode(K key) const {
    TreeNode<T, K>* cursor = root;
    if (!cursor) return nullptr;  // Tree is empty

    while (!cursor->is_leaf) {
        int i = 0;
        while (i < cursor->size && key >= cursor->keys[i]) {
            i++;
        }
        cursor = cursor->children[i];
    }

    return cursor;
}

// Return the index where an item is supposed to go
template <typename T, typename K>
int BPlusTree<T, K>::findIndex(K* arr, K key, int len) const {
    int i = 0;
    while (i < len && key > arr[i]) {
        i++;
    }
    return i;
}

// Insert key/child into the internal node
template <typename T, typename K>
void BPlusTree<T, K>::insertInternal(K* keys, TreeNode<T, K>** children,
                                K key, TreeNode<T, K>* child, int old_len, int idx) {
    for (int i = old_len; i > idx; i--) {
        keys[i] = keys[i - 1];
        children[i + 1] = children[i];
    }
    
    keys[idx] = key;
    children[idx + 1] = child;
}

// Insert key/value into the leaf node
template <typename T, typename K>
void BPlusTree<T, K>::insertLeaf(K* keys, T* values,
                                K key, T data, int old_len, int idx) {
    for (int i = old_len; i > idx; i--) {
        keys[i] = keys[i - 1];
        values[i] = values[i - 1];
    }

    keys[idx] = key;
    values[idx] = data;
}

// Return ptr if the item exists. Return null if not.
template <typename T, typename K>
T* BPlusTree<T, K>::search(K key) const {
    TreeNode<T, K>* node = searchNode(key);
    if (!node || !node->is_leaf) {
        return nullptr;
    }

    for (std::size_t i = 0; i < node->size; i++) {
        if (node->keys[i] == key) {
            return &node->values[i];
        }
    }

    return nullptr; // Not found
}

template <typename T, typename K>
void BPlusTree<T, K>::insertPar(TreeNode<T, K>* par, TreeNode<T, K>* child, K key) {
    if (par->size < degree_inner) {
        // There is space in parent, insert key/child in parent
        int idx = findIndex(par->keys, key, par->size);
        insertInternal(par->keys, par->children, key, child, par->size, idx);

        par->size++;
        child->parent = par;
    } else {
        // Parent is full, need to split
        TreeNode<T, K>* new_internal = new TreeNode<T, K>(degree_inner, degree_leaf, false);
        K temp_keys[degree_inner + 1];
        TreeNode<T, K>* temp_children[degree_inner + 2];

        // Copy existing keys and children to temp arrays
        for (int i = 0; i < degree_inner; i++) {
            temp_keys[i] = par->keys[i];
            temp_children[i] = par->children[i];
        }
        temp_children[degree_inner] = par->children[degree_inner];

        // Insert new key and child into temp arrays
        int idx = findIndex(temp_keys, key, degree_inner);
        insertInternal(temp_keys, temp_children, key, child, degree_inner, idx);

        // Split
        int mid = (degree_inner + 1) / 2;
        par->size = mid;
        new_internal->size = degree_inner - mid;

        for (int i = 0; i < mid; i++) {
            par->keys[i] = temp_keys[i];
            par->children[i] = temp_children[i];
        }
        par->children[mid] = temp_children[mid];

        // Note that temp_keys[mid] is not copied to either internal nodes
        // but is pushed up to parent
        
        for (int i = 0; i < new_internal->size; i++) {
            new_internal->keys[i] = temp_keys[mid + 1 + i];
            new_internal->children[i] = temp_children[mid + 1 + i];
            new_internal->children[i]->parent = new_internal;
        }
        new_internal->children[new_internal->size] = temp_children[degree_inner + 1];
        new_internal->children[new_internal->size]->parent = new_internal;

        K pushup_key = temp_keys[mid];

        if (par == root) {
            TreeNode<T, K>* new_root = new TreeNode<T, K>(degree_inner, degree_leaf, false);
            new_root->keys[0] = pushup_key;
            new_root->children[0] = par;
            new_root->children[1] = new_internal;
            new_root->size = 1;
            par->parent = new_root;
            new_internal->parent = new_root;
            root = new_root;
        } else {
            insertPar(par->parent, new_internal, pushup_key);
        }
    }
}

// Insert an item into the tree.
template <typename T, typename K>
void BPlusTree<T, K>::insert(K key, T data) {
    this->currentSize++; // Increment size of the tree cause insertion

    if (!root) {
        // Tree is empty
        root = new TreeNode<T, K>(degree_inner, degree_leaf, true);
        root->keys[0] = key;
        root->values[0] = data;
        root->size = 1;
        return;
    }

    TreeNode<T, K>* leaf = searchNode(key);

    int idx = findIndex(leaf->keys, key, leaf->size);
    if (leaf->size < degree_leaf) {
        insertLeaf(leaf->keys, leaf->values, key, data, leaf->size, idx);
        leaf->size++;
    } else {
        // Need to split
        TreeNode<T, K>* new_leaf = new TreeNode<T, K>(degree_inner, degree_leaf, true);
        K temp_keys[degree_leaf + 1];
        T temp_values[degree_leaf + 1];

        for (int i = 0; i < degree_leaf; i++) {
            temp_keys[i] = leaf->keys[i];
            temp_values[i] = leaf->values[i];
        }

        int insert_idx = findIndex(temp_keys, key, degree_leaf);
        insertLeaf(temp_keys, temp_values, key, data, degree_leaf, insert_idx);

        int split = (degree_leaf + 1) / 2;
        leaf->size = split;
        new_leaf->size = (degree_leaf + 1) - split;

        for (int i = 0; i < split; i++) {
            leaf->keys[i] = temp_keys[i];
            leaf->values[i] = temp_values[i];
        }
        for (int i = 0; i < new_leaf->size; i++) {
            new_leaf->keys[i] = temp_keys[split + i];
            new_leaf->values[i] = temp_values[split + i];
        }

        new_leaf->next = leaf->next;
        leaf->next = new_leaf;
        new_leaf->parent = leaf->parent;

        K pushup_key = new_leaf->keys[0];

        if (leaf == root) {
            TreeNode<T, K>* new_root = new TreeNode<T, K>(degree_inner, degree_leaf, false);
            new_root->keys[0] = pushup_key;
            new_root->children[0] = leaf;
            new_root->children[1] = new_leaf;
            new_root->size = 1;
            leaf->parent = new_root;
            new_leaf->parent = new_root;
            root = new_root;
        } else {
            insertPar(leaf->parent, new_leaf, pushup_key);
        }
    }
}

template <typename T, typename K>
void BPlusTree<T, K>::removePar(TreeNode<T, K>* node, int index, TreeNode<T, K>* par) {
    // Shift keys and children in parent
    for (int i = index; i < par->size - 1; i++) {
        par->keys[i] = par->keys[i + 1];
        par->children[i + 1] = par->children[i + 2];
    }
    par->size--;

    if (par == root && par->size == 0) {
        // If root becomes empty
        root = par->children[0];
        if (root)
            root->parent = nullptr;
        delete par;
        return;
    }

    // If parent underflows
    if (par->size < (degree_inner + 1) / 2) {
        TreeNode<T, K>* parent = par->parent;
        if (!parent) return; // Root

        // Find par’s index in grandparent
        int p_idx = 0;
        while (p_idx <= parent->size && parent->children[p_idx] != par)
            p_idx++;

        TreeNode<T, K>* left_sibling = (p_idx > 0) ? parent->children[p_idx - 1] : nullptr;
        TreeNode<T, K>* right_sibling = (p_idx < parent->size) ? parent->children[p_idx + 1] : nullptr;

        if (right_sibling && right_sibling->size > (degree_inner + 1) / 2) {
            // Borrow from right
            par->keys[par->size] = parent->keys[p_idx];
            par->children[par->size + 1] = right_sibling->children[0];
            par->children[par->size + 1]->parent = par;
            par->size++;

            parent->keys[p_idx] = right_sibling->keys[0];
            for (int i = 0; i < right_sibling->size - 1; i++) {
                right_sibling->keys[i] = right_sibling->keys[i + 1];
                right_sibling->children[i] = right_sibling->children[i + 1];
            }
            right_sibling->children[right_sibling->size - 1] = right_sibling->children[right_sibling->size];
            right_sibling->size--;
        } else if (left_sibling && left_sibling->size > (degree_inner + 1) / 2) {
            // Borrow from left
            for (int i = par->size; i > 0; i--) {
                par->keys[i] = par->keys[i - 1];
                par->children[i + 1] = par->children[i];
            }
            par->children[1] = par->children[0];
            par->keys[0] = parent->keys[p_idx - 1];
            par->children[0] = left_sibling->children[left_sibling->size];
            par->children[0]->parent = par;
            par->size++;

            parent->keys[p_idx - 1] = left_sibling->keys[left_sibling->size - 1];
            left_sibling->size--;
        } else {
            // Merge with sibling
            TreeNode<T, K>* sibling;
            int sibling_idx;

            if (right_sibling) {
                sibling = right_sibling;
                sibling_idx = p_idx;
            } else {
                sibling = par;
                par = left_sibling;
                sibling_idx = p_idx - 1;
            }

            // Merge sibling into par
            par->keys[par->size] = parent->keys[sibling_idx];
            for (int i = 0; i < sibling->size; i++) {
                par->keys[par->size + 1 + i] = sibling->keys[i];
                par->children[par->size + 1 + i] = sibling->children[i];
                par->children[par->size + 1 + i]->parent = par;
            }
            par->children[par->size + 1 + sibling->size] = sibling->children[sibling->size];
            if (par->children[par->size + 1 + sibling->size])
                par->children[par->size + 1 + sibling->size]->parent = par;

            par->size += sibling->size + 1;
            removePar(sibling, sibling_idx, parent);
            delete sibling;
        }
    }
}

// Remove an item from the tree.
template <typename T, typename K>
void BPlusTree<T, K>::remove(K key) {
    if (!root) return;

    TreeNode<T, K>* leaf = searchNode(key);
    if (!leaf) return;

    this->currentSize--; // Decrement size of the tree cause deletion

    int idx = -1;
    for (std::size_t i = 0; i < leaf->size; i++) {
        if (leaf->keys[i] == key) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return; // Key not found

    for (int i = idx; i < leaf->size - 1; i++) {
        leaf->keys[i] = leaf->keys[i + 1];
        leaf->values[i] = leaf->values[i + 1];
    }
    leaf->size--;

    // Underflow handling
    if (leaf == root) {
        if (leaf->size == 0) {
            delete root;
            root = nullptr;
        }
        return;
    }

    if (leaf->size >= (degree_leaf + 1) / 2) return; // Enough values left

    TreeNode<T, K>* parent = leaf->parent;
    int leaf_idx = 0;
    while (parent->children[leaf_idx] != leaf) ++leaf_idx;

    TreeNode<T, K>* left = (leaf_idx > 0) ? parent->children[leaf_idx - 1] : nullptr;
    TreeNode<T, K>* right = (leaf_idx < parent->size) ? parent->children[leaf_idx + 1] : nullptr;

    if (right && right->size > (degree_leaf + 1) / 2) {
        // Borrow from right
        leaf->keys[leaf->size] = right->keys[0];
        leaf->values[leaf->size] = right->values[0];
        leaf->size++;

        for (int i = 0; i < right->size - 1; i++) {
            right->keys[i] = right->keys[i + 1];
            right->values[i] = right->values[i + 1];
        }
        right->size--;
        parent->keys[leaf_idx] = right->keys[0];
    } else if (left && left->size > (degree_leaf + 1) / 2) {
        // Borrow from left
        for (int i = leaf->size; i > 0; i--) {
            leaf->keys[i] = leaf->keys[i - 1];
            leaf->values[i] = leaf->values[i - 1];
        }
        leaf->keys[0] = left->keys[left->size - 1];
        leaf->values[0] = left->values[left->size - 1];
        leaf->size++;
        left->size--;
        parent->keys[leaf_idx - 1] = leaf->keys[0];
    } else {
        // Merge
        TreeNode<T, K>* merge_into;
        TreeNode<T, K>* merge_from;
        int merge_idx;

        if (right) {
            merge_into = leaf;
            merge_from = right;
            merge_idx = leaf_idx;
        } else {
            merge_into = left;
            merge_from = leaf;
            merge_idx = leaf_idx - 1;
        }

        for (std::size_t i = 0; i < merge_from->size; i++) {
            merge_into->keys[merge_into->size + i] = merge_from->keys[i];
            merge_into->values[merge_into->size + i] = merge_from->values[i];
        }
        merge_into->size += merge_from->size;
        merge_into->next = merge_from->next;

        removePar(merge_from, merge_idx, parent);
        delete merge_from;
    }
}

// Release all memory used by the tree.
template <typename T, typename K>
void BPlusTree<T, K>::cleanup(TreeNode<T, K>* cursor) {
    if (!cursor) return;

    if (!cursor->is_leaf) {
        for (std::size_t i = 0; i <= cursor->size; i++) {
            cleanup(cursor->children[i]);
        }
    }

    delete cursor;
}

// Iterator: begin
template <typename T, typename K>
typename BPlusTree<T, K>::bptIterator BPlusTree<T, K>::begin() const {
    TreeNode<T, K>* cursor = root;
    if (!cursor) return bptIterator(nullptr, 0);

    while (!cursor->is_leaf) {
        cursor = cursor->children[0];
    }
    return bptIterator(cursor, 0);
}

// Iterator: end
template <typename T, typename K>
typename BPlusTree<T, K>::bptIterator BPlusTree<T, K>::end() const {
    return bptIterator(nullptr, 0);
}

// Get the maximum key in the tree
template <typename T, typename K>
K BPlusTree<T, K>::getMaxKey() const {
    if (!root) {
        throw std::runtime_error("Tree is empty");
    }

    TreeNode<T, K>* cursor = root;
    while (!cursor->is_leaf) {
        cursor = cursor->children[cursor->size];
    }

    return cursor->keys[cursor->size - 1]; // Last key in the leaf
}

// Print recursively
template <typename T, typename K>
void BPlusTree<T, K>::printHelper(TreeNode<T, K>* cursor) const {
    if (!cursor) return;

    std::cout << (cursor->is_leaf ? "[Leaf] " : "[Internal] ") << "Keys: ";
    for (std::size_t i = 0; i < cursor->size; i++) {
        std::cout << cursor->keys[i] << " ";
    }
    std::cout << "\n";

    if (!cursor->is_leaf) {
        for (std::size_t i = 0; i <= cursor->size; i++) {
            printHelper(cursor->children[i]);
        }
    }
}

// Print the full tree
template <typename T, typename K>
void BPlusTree<T, K>::print() const {
    std::cout << "B+ Tree Structure:\n";
    printHelper(root);
}

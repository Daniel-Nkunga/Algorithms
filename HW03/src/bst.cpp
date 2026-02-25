#include <bst.hpp>

template<class T>
BSTNode<T>::BSTNode() {
    this->left = this->right = NULL;
    this->height = 0;
}

template<class T>
BSTNode<T>::BSTNode(T key, int height, BSTNode *left, BSTNode *right) {
    this->key = key;
    this->height = height;
    this->left = left;
    this->right = right;
}

template<class T>
BSTNode<T>::~BSTNode() {
    this->left = this->right = NULL;
}

template<class T>
BST<T>::BST() { this->root = NULL; }

template<class T>
BST<T>::~BST() { this->clear(this->root); }

template<class T>
void BST<T>::clear(BSTNode<T> *node) {
    // YOUR CODE HERE
}

template<class T>
BSTNode<T> *BST<T>::find(T key, BSTNode<T> *node) {
    // Leaf node
    if (node->left == nullptr && node->right == nullptr)
    {
        return nullptr;
    }
    // Find smaller node when no smaller node exist
    if (key < node->key && node->left == nullptr)
    {
        return nullptr;
    }
    // Find larger node when no larger node exist
    if (key > node->key && node->right == nullptr)
    {
        return nullptr;
    }

    // Traverse the tree
    if (key < node->left->key)
    {
        find(key, node->left);
    }

    if(key > node->right->key)
    {
        find(key, node->right);
    }


    return nullptr; // Placeholder
}


template<class T>
BSTNode<T> *BST<T>::findMaximum(BSTNode<T> *node) {
    if(node->left != nullptr)
    {
        findMaximum(node->left);
    }

    return node;
}


template<class T>
BSTNode<T> *BST<T>::findMinimum(BSTNode<T> *node) {
    if(node->right != nullptr)
    {
        findMaximum(node->right);
    }

    return node;
}


template<class T>
BSTNode<T> *BST<T>::insert(T key, BSTNode<T> *node) {
    // YOUR CODE HERE
    return nullptr; // Placeholder
}

template<class T>
BSTNode<T> *BST<T>::remove(T key, BSTNode<T> *node) {
    // YOUR CODE HERE
    return nullptr; // Placeholder
}


template<class T>
BSTNode<T> *BST<T>::find(T key) { return find(key, root); }

template<class T>
BSTNode<T> *BST<T>::findMaximum() { return findMaximum(root); }

template<class T>
BSTNode<T> *BST<T>::findMinimum() { return findMinimum(root); }

template<class T>
BSTNode<T> *BST<T>::insert(T key) { return root = insert(key, root); }

template<class T>
BSTNode<T> *BST<T>::remove(T key) { return root = remove(key, root); }

template class BST<int>;
template class BST<std::pair<int, int>>;
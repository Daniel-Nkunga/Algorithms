#include <avl.hpp>

template<class T>
int AVL<T>::getHeight(BSTNode<T> *node) {
    return (node == NULL) ? -1 : node->height;
}

template<class T>
int AVL<T>::getBalance(BSTNode<T> *node) {
    return (node == NULL) ? 0 : getHeight(node->left) - getHeight(node->right);
}

template<class T>
BSTNode<T> *AVL<T>::rotateRight(BSTNode<T> *y) {
    // YOUR CODE HERE
    return nullptr; // Placeholder
}

template<class T>
BSTNode<T> *AVL<T>::rotateLeft(BSTNode<T> *x) {
    // YOUR CODE HERE
    return nullptr; // Placeholder
}

template<class T>
BSTNode<T> *AVL<T>::insert(T key, BSTNode<T> *node) {
    // YOUR CODE HERE
    return nullptr; // Placeholder
}


template<class T>
BSTNode<T> *AVL<T>::remove(T key, BSTNode<T> *node) {
    // YOUR CODE HERE
    return nullptr; // Placeholder
}

template<class T>
BSTNode<T> *AVL<T>::insert(T key) { return this->root = insert(key, this->root); }

template<class T>
BSTNode<T> *AVL<T>::remove(T key) { return this->root = remove(key, this->root); }

template class AVL<int>;
template class AVL<std::pair<int, int>>;
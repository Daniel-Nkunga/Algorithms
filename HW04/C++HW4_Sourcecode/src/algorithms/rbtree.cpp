#include "rbtree.hpp"
#include <iostream>

void RedBlackTree::rotateLeft(RBNode *&root, RBNode *&ptr) {
    RBNode *rightChild = ptr->right;

    ptr->right = rightChild->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    rightChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = rightChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = rightChild;
    else
        ptr->parent->right = rightChild;

    rightChild->left = ptr;
    ptr->parent = rightChild;
}

void RedBlackTree::rotateRight(RBNode *&root, RBNode *&ptr) {
    // YOUR CODE HERE
}

void RedBlackTree::fixViolation(RBNode *&root, RBNode *&ptr) {
    // YOUR CODE HERE
}

void RedBlackTree::insert(const int &data, int x, int y) {
    // YOUR CODE HERE
}

RBNode* RedBlackTree::search(int data) {
    RBNode *temp = root;
    while (temp != nullptr) {
        if (data == temp->data) return temp;
        if (data < temp->data) temp = temp->left;
        else temp = temp->right;
    }
    return nullptr;
}
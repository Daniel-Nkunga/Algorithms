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
    RBNode *leftChild = ptr->left;

    ptr->left = leftChild->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    leftChild->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = leftChild;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = leftChild;
    else
        ptr->parent->right = leftChild;

    leftChild->right = ptr;
    ptr->parent = leftChild;
}

void RedBlackTree::fixViolation(RBNode *&root, RBNode *&ptr) {
    RBNode *parent     = nullptr;
    RBNode *grandParent = nullptr;

    while (ptr != root && ptr->color == RED && ptr->parent->color == RED) {
        parent      = ptr->parent;
        grandParent = parent->parent;

        // Case A: Parent is the LEFT child of grandparent ---
        if (parent == grandParent->left) {
            RBNode *uncle = grandParent->right;

            // Case A1: Uncle is RED → recolor and move up
            if (uncle != nullptr && uncle->color == RED) {
                grandParent->color = RED;
                parent->color      = BLACK;
                uncle->color       = BLACK;
                ptr                = grandParent;
            } else {
                // Case A2: ptr is a RIGHT child → left-rotate parent first
                if (ptr == parent->right) {
                    rotateLeft(root, parent);
                    ptr    = parent;
                    parent = ptr->parent;
                }
                // Case A3: ptr is a LEFT child → right-rotate grandparent
                rotateRight(root, grandParent);
                std::swap(parent->color, grandParent->color);
                ptr = parent;
            }
        }
        // Case B: Parent is the RIGHT child of grandparent (mirror) ---
        else {
            RBNode *uncle = grandParent->left;

            // Case B1: Uncle is RED → recolor and move up
            if (uncle != nullptr && uncle->color == RED) {
                grandParent->color = RED;
                parent->color      = BLACK;
                uncle->color       = BLACK;
                ptr                = grandParent;
            } else {
                // Case B2: ptr is a LEFT child → right-rotate parent first
                if (ptr == parent->left) {
                    rotateRight(root, parent);
                    ptr    = parent;
                    parent = ptr->parent;
                }
                // Case B3: ptr is a RIGHT child → left-rotate grandparent
                rotateLeft(root, grandParent);
                std::swap(parent->color, grandParent->color);
                ptr = parent;
            }
        }
    }

    // Root must always be BLACK
    root->color = BLACK;
}

void RedBlackTree::insert(const int &data, int x, int y) {
    RBNode *node = new RBNode(data, x, y);

    // Empty tree: new node becomes the black root
    if (root == nullptr) {
        node->color = BLACK;
        root = node;
        return;
    }

    // --- Standard BST traversal to find insertion point ---
    RBNode *current = root;
    RBNode *parent  = nullptr;

    while (current != nullptr) {
        parent = current;
        if (node->data < current->data)
            current = current->left;
        else if (node->data > current->data)
            current = current->right;
        else {
            // Duplicate key: update coordinates and discard new node
            current->x = x;
            current->y = y;
            delete node;
            return;
        }
    }

    // Attach new node under its parent
    node->parent = parent;
    if (node->data < parent->data)
        parent->left  = node;
    else
        parent->right = node;

    // Fix any Red-Black violations introduced by the insertion
    fixViolation(root, node);
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
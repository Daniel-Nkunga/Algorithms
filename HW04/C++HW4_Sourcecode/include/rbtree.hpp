#ifndef RBTREE_HPP
#define RBTREE_HPP

enum Color { RED, BLACK };

struct RBNode {
    int data;
    int x, y; // Coordinate data for the map
    Color color;
    RBNode *left, *right, *parent;

    RBNode(int data, int x, int y) : data(data), x(x), y(y) {
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    RBNode *root;
    void rotateLeft(RBNode *&root, RBNode *&ptr);
    void rotateRight(RBNode *&root, RBNode *&ptr);
    void fixViolation(RBNode *&root, RBNode *&ptr);

public:
    RedBlackTree() { root = nullptr; }
    void insert(const int &data, int x, int y);
    RBNode* search(int data);
    void inorder(RBNode *root);
    RBNode* getRoot() { return root; }
};

#endif
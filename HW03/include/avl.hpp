#ifndef AVL_HPP
#define AVL_HPP

#include <bst.hpp>
#include <algorithm>

template<class T>
class AVL : public BST<T> {
    private:
        int getHeight(BSTNode<T> *node);
        int getBalance(BSTNode<T> *node);
        BSTNode<T> *rotateRight(BSTNode<T> *y);
        BSTNode<T> *rotateLeft(BSTNode<T> *x);

        BSTNode<T> *insert(T key, BSTNode<T> *node) override;
        BSTNode<T> *remove(T key, BSTNode<T> *node) override;

    public:
        AVL() : BST<T>() {}
        BSTNode<T> *insert(T key) override;
        BSTNode<T> *remove(T key) override;
};

#endif
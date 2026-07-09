#pragma once
#include <iostream>

template<class T>
struct LinkedListNode {
    T value;
    LinkedListNode<T> *next;
    LinkedListNode(T value = 0, LinkedListNode<T>* next = nullptr);
};

template<class T>
class LinkedList {
    private:
         LinkedListNode<T> *root;
    public:
         LinkedList();
         ~LinkedList();
         LinkedListNode<T>* insert(T value);
         LinkedListNode<T>* find(T value);
         void remove(T value);
         int size();
         LinkedListNode<T>* getRoot() const { return root; }
};
#include "../include/linked_list.hpp"

template<class T>
LinkedListNode<T>::LinkedListNode(T value, LinkedListNode<T>* next) 
    : value(value), next(next) {}

template<class T>
LinkedList<T>::LinkedList() : root(nullptr) {}

template<class T>
LinkedList<T>::~LinkedList() {
    LinkedListNode<T>* p = root;
    while(p != nullptr) {
        LinkedListNode<T>* temp = p->next;
        delete p;
        p = temp;
    }
}

template<class T>
LinkedListNode<T>* LinkedList<T>::insert(T value) {
    if (find(value)) return nullptr; // Prevent duplicates
    root = new LinkedListNode<T>(value, root);
    return root;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::find(T value) {
    LinkedListNode<T>* p = root;
    while(p != nullptr) {
        if(p->value == value) return p;
        p = p->next;
    }
    return nullptr;
}

template<class T>
void LinkedList<T>::remove(T value) {
    LinkedListNode<T> *p = root, *prev = nullptr;
    while(p != nullptr && p->value != value) {
        prev = p;
        p = p->next;
    }
    if(p == nullptr) return;
    if(prev == nullptr) root = p->next;
    else prev->next = p->next;
    delete p;
}

template<class T>
int LinkedList<T>::size() {
    int count = 0;
    LinkedListNode<T>* p = root;
    while(p != nullptr) { count++; p = p->next; }
    return count;
}

template class LinkedList<int>;
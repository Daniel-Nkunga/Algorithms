#include "../include/queue.hpp"
#include <stdexcept>

template<class T>
QueueNode<T>::QueueNode(T val) : value(val), next(nullptr) {}

template<class T>
Queue<T>::Queue() : head(nullptr), tail(nullptr) {}

template<class T>
Queue<T>::~Queue() {
    while(!empty()) pop();
}

template<class T>
bool Queue<T>::empty() { return head == nullptr; }

template<class T>
void Queue<T>::push(T value) {
    QueueNode<T>* newNode = new QueueNode<T>(value);
    if(tail) tail->next = newNode;
    else head = newNode;
    tail = newNode;
}

template<class T>
T Queue<T>::pop() {
    if(empty()) throw std::runtime_error("Queue is empty");
    T val = head->value;
    QueueNode<T>* temp = head;
    head = head->next;
    if(!head) tail = nullptr;
    delete temp;
    return val;
}

template class Queue<int>;
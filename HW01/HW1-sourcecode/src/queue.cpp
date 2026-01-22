#include "./../include/graph.hpp"

template<class T>
QueueNode<T>::QueueNode(T value, QueueNode<T> *next, QueueNode<T> *prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template<class T>
QueueNode<T>::~QueueNode() {
    this->next = this->prev = NULL;
}

template<class T>
Queue<T>::Queue() {
    this->head = this->tail = NULL;
}

template<class T>
Queue<T>::~Queue() {
    // YOUR CODE HERE 

    // END OF YOUR CODE HERE
}

template<class T>
bool Queue<T>::empty() {
    // YOUR CODE HERE

    // END OF YOUR CODE HERE
}

template<class T>
T Queue<T>::pop() {
    if (this->empty()){
        throw std::out_of_range("Queue is empty");
    }
    T value = this->head->value;
    // YOUR CODE HERE

    // END OF YOUR CODE HERE
    return value;
}

template<class T>
void Queue<T>::push(T value) {
    QueueNode<T> *p = new QueueNode<T>(value, NULL, NULL);
    // YOUR CODE HERE

    // END OF YOUR CODE HERE
}

template class Queue<int>;

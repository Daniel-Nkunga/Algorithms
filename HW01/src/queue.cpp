#include <cstddef>
#include <graph.hpp>
#include <iterator>

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
    QueueNode<T>* current = this->head;

    while(current != NULL)
    {
        QueueNode<T>* next = current->next;
        delete current;
        current = next;
    }

    this->head = NULL;
    this->tail = NULL;
}

template<class T>
bool Queue<T>::empty() {
    return (this->head == NULL && this->tail == NULL);
}

template<class T>
T Queue<T>::pop() {
    if (this->empty()){
        throw std::out_of_range("Queue is empty");
    }
    T value = this->head->value;

    QueueNode<T>* headToDelete = this->head;
    this->head = this->head->next;

    // Accounting for a newly empty queue
    if(this->head == NULL)
    {
        this->tail = NULL;
    } else {
        this->head->prev = NULL;
    }

    delete headToDelete;

    return value;
}

template<class T>
void Queue<T>::push(T value) {
    QueueNode<T> *p = new QueueNode<T>(value, NULL, this->tail); // Why doesn't the third paramet point to the current tail?

    if(this->empty())
    {
        this->head = p;
        this->tail = p;
    } else {
        this->tail->next = p;
        this->tail = p;
    }
}

template class Queue<int>;

#pragma once

template<class T>
struct QueueNode {
    T value;
    QueueNode<T> *next;
    QueueNode(T val);
};

template<class T>
class Queue {
    private:
        QueueNode<T> *head;
        QueueNode<T> *tail;
    public:
        Queue();
        ~Queue();
        bool empty();
        void push(T value);
        T pop();
};
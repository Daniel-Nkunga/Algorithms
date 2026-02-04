#include <linked_list.hpp>
#include <exception>

template<class T>
LinkedListNode<T>::LinkedListNode(T value, LinkedListNode<T>* next, LinkedListNode<T>* prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

template<class T>
LinkedListNode<T>::~LinkedListNode() {
    this->next = NULL;
}

template<class T>
LinkedList<T>::LinkedList() {
     this->root = NULL;
}

// Deconstructor
template<class T>
LinkedList<T>::~LinkedList() {
    LinkedListNode<T>* current = this->root;

    while (current != NULL)
    {
        LinkedListNode<T>* next = current->next;
        delete current;
        current = next;
    }

    this->root = NULL;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::insert(T value) {

    // Empty list
    if(this->root == NULL)
    {
        this->root = new LinkedListNode<T>(value);
        return this->root;
    }

    LinkedListNode<T>* current = this->root;

    while(current != NULL)
    {
        // Return value pointer if value already exist
        if(current->value == value)
        {
            return current;
        }

        // Insert the new node if the next node is empty
        if(current->next == NULL)
        {
            LinkedListNode<T>* newNode = new LinkedListNode<T>(value);
            current->next = newNode;
            newNode->prev = current;
            return newNode;
        }

        // Iterate along the list so long as the next element exist
        current = current->next;
    }

    // Redundant code to ensure return statement
    LinkedListNode<T>* newNode = new LinkedListNode<T>(value);
    current->next = newNode;
    newNode->prev = current;

    return newNode;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::find(T value) {
    LinkedListNode<T>* current = this->root;

    // Iterate across list while node exist
    while(current != NULL)
    {
        if(current->value == value)
        {
            return current;
        }
        current = current->next;
    }

    // Return NULL if it cannot find node
    return NULL;
}

template<class T>
LinkedListNode<T>* LinkedList<T>::remove(T value) {
    // Find node to delete
    LinkedListNode<T>* nodeToDelete = this->find(value);

    if(nodeToDelete != NULL)
    {
        // Account for deleting the root node
        if(nodeToDelete->prev == NULL)
        {
            this->root = nodeToDelete->next;
        } else {
            // Skip over deleted node from previous node
            nodeToDelete->prev->next = nodeToDelete->next;
        }

        // Account for deleting the last node
        if(nodeToDelete->next != NULL)
        {
            // Skip over deleted node from next node
            nodeToDelete->next->prev = nodeToDelete->prev;
        }

        delete nodeToDelete;
    }

    return this->root;
}

template<class T>
int LinkedList<T>::size() {
    LinkedListNode<T>* current = this->root;
    int size = 0;

    // Iterate across list while node exist
    while(current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

template class LinkedListNode<int>;
template class LinkedList<int>;

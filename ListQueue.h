#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "DblList.h"

template <typename T>
class ListQueue {
public:
    ListQueue();
    ~ListQueue(); // You might want to manage memory cleanup if needed
    void enqueue(T data);
    T dequeue();
    bool isEmpty() const;

private:
    DblList<T> list;
};

template <typename T>
ListQueue<T>::ListQueue() {
}

template <typename T>
ListQueue<T>::~ListQueue() {
    // Clean up resources if necessary
}

template <typename T>
void ListQueue<T>::enqueue(T data) {
    list.insertBack(data);
}

template <typename T>
T ListQueue<T>::dequeue() {
    return list.removeFront();
}

template <typename T>
bool ListQueue<T>::isEmpty() const {
    return list.isEmpty();
}

#endif // LISTQUEUE_H

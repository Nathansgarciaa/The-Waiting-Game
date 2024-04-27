#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "DblList.h"

template<typename T>
class ListQueue {
private:
    DblList<T> list;

public:
    ListQueue() : list() { 
        // Constructor body, if needed.
        // The initialization list 'list()' calls the default constructor of DblList.
    }

    void enqueue(T d) {
        list.insertFront(d);
    }

    T dequeue() {
        if (list.isEmpty()) {
            throw std::runtime_error("Queue is empty");
        }
        return list.removeFront();
    }

    bool isEmpty() const {
        return list.isEmpty();
    }

    unsigned int getSize() const {
        return list.size;
    }
};

#endif // LISTQUEUE_H

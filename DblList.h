#ifndef DBLLIST_H
#define DBLLIST_H

#include "ListNode.h"

template <typename T>
class DblList {
public:
    DblList();
    ~DblList();
    void insertBack(T data);
    T removeFront();
    bool isEmpty() const;
    // Additional functions as needed

private:
    ListNode<T> *head;
    ListNode<T> *tail;
    int size;
};

template <typename T>
DblList<T>::DblList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
DblList<T>::~DblList() {
    while (!isEmpty()) {
        removeFront();
    }
}

template <typename T>
void DblList<T>::insertBack(T data) {
    ListNode<T>* newNode = new ListNode<T>(data);
    if (isEmpty()) {
        head = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
    }
    tail = newNode;
    size++;
}

template <typename T>
T DblList<T>::removeFront() {
    ListNode<T>* temp = head;
    T data = head->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    } else {
        head->prev = nullptr;
    }
    delete temp;
    size--;
    return data;
}

template <typename T>
bool DblList<T>::isEmpty() const {
    return size == 0;
}



#endif // DBLLIST_H

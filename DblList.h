#ifndef DBLLIST_H
#define DBLLIST_H

#include <stdexcept>

template<typename T>
class ListNode {
public:
    T data;
    ListNode<T> *next;
    ListNode<T> *prev;

    ListNode(T d) : data(d), next(nullptr), prev(nullptr) {}
};

template<typename T>
class DblList {
public:
    ListNode<T>* head;
    ListNode<T>* tail;
    unsigned int size;

    DblList() : head(nullptr), tail(nullptr), size(0) {}

    ~DblList() {
        while (head != nullptr) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    void insertFront(T d) {
        ListNode<T>* newNode = new ListNode<T>(d);
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    T removeFront() {
        if (isEmpty()) {
            throw std::runtime_error("List is empty");
        }
        ListNode<T>* temp = head;
        T data = temp->data;
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

    bool isEmpty() const {
        return size == 0;
    }
};

#endif // DBLLIST_H

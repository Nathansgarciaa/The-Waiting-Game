#ifndef LISTNODE_H
#define LISTNODE_H

template <typename T>
class ListNode {
public:
    T data;             // The data stored in the node
    ListNode<T> *next;  // Pointer to the next node
    ListNode<T> *prev;  // Pointer to the previous node

    ListNode(T data);   // Constructor with data
    ~ListNode();        // Destructor
};

template <typename T>
ListNode<T>::ListNode(T data) : data(data), next(nullptr), prev(nullptr) {}

template <typename T>
ListNode<T>::~ListNode() {
    // Optional: Manage memory or handle deletion of next/prev if needed
}

#endif // LISTNODE_H

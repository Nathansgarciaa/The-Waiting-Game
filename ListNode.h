#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
#include <exception>
using namespace std;

class ListNode{
    public:
        ListNode();
        ListNode(int d);
        ~ListNode();
        ListNode *next;
        ListNode *prev;
        int data;
        
}
;

#endif
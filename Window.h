#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include "ListQueue.h"
#include "Customer.h"

class Window {
private:
    bool occupied = false;
    Customer* currentCustomer = nullptr;
    int occupiedTime = 0;
    int idleTime = 0;

public:
    Window() = default;
    ~Window() = default;

    void occupy();
    void releaseCustomer();
    void checkTime();
    void setCustomer(Customer* customer);
    bool isOccupied() const;

    ListQueue<Customer*> waitingQueue;
};

#endif // WINDOW_H

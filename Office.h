#ifndef OFFICE_H
#define OFFICE_H

#include <iostream>
#include <string>
#include "Window.h"
#include "ListQueue.h"

class Office {
public:
    std::string officeName;
    Window* windows;
    int numWindows;
    ListQueue<Customer*> queue;
    ListQueue<Customer*> nextQueue;
    int totalCustomers = 0;
    int StudentWaitTime = 0;
    int maxWaitTime = 0;
    int numStudents10Mins = 0;
    int meanIdleTime = 0;
    int totalIdleTime = 0;
    int longestWindowIdleTime = 0;
    int numWindowsIdle5mins = 0;

   

    Office(int numberOfWindows, std::string name);
    ~Office();

    void addCustomer(Customer* customer);
    void updateOffice();
    double meanWaitTime() const;
    double getMeanIdleTime();
    int getLongestWindowIdleTime();
};

#endif // OFFICE_H

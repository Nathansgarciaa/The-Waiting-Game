#include <iostream>
#include "Window.cpp"

#include "ListQueue.h"  // Include your ListQueue implementation here

class Office {
public:
    std::string officeName;
    Window* windows;
    int numWindows;
    ListQueue<Customer*> queue;
    int totalCustomers = 0;

    Office(int numberOfWindows, std::string name) : numWindows(numberOfWindows), officeName(name) {
        windows = new Window[numWindows];
    }

    ~Office() {
        delete[] windows;
    }

    void addCustomer(Customer* customer) {
        queue.enqueue(customer);
        totalCustomers++;
        nextInLine();
    }

    void nextInLine() {
        for (int i = 0; i < numWindows; ++i) {
            if (!windows[i].isOccupied() && !queue.isEmpty()) {
                Customer* customer = queue.dequeue();
                windows[i].setCustomer(customer);
            }
            windows[i].processTime();
        }
    }

    int totalIdleTime() const {
        int totalIdle = 0;
        for (int i = 0; i < numWindows; ++i) {
            totalIdle += windows[i].getIdleTime();
        }
        return totalIdle;
    }

    int longestIdleTime() const {
        int longestIdle = 0;
        for (int i = 0; i < numWindows; ++i) {
            if (windows[i].getIdleTime() > longestIdle) {
                longestIdle = windows[i].getIdleTime();
            }
        }
        return longestIdle;
    }
    int customersWaitingOver10Minutes() {
        int count = 0;
        for (int i = 0; i < numWindows; ++i) {
            count += windows[i].customersWaitingOver10Minutes();
        }
        return count;
    }

    int idleOver5Minutes() {
        int count = 0;
        for (int i = 0; i < numWindows; ++i) {
            if (windows[i].idleOver5Minutes()) {
                count++;
            }
        }
        return count;
        void updateTotalWaitTime(int waitTime){
        totalWaitTime += waitTime;
        }

    // Function to update longest wait time
    void updateLongestWaitTime(int waitTime) {
        if (waitTime > longestWaitTime) {
            longestWaitTime = waitTime;
        }
    }

    // Function to retrieve total wait time
    int getTotalWaitTime() const {
        return totalWaitTime;
    }

    // Function to retrieve longest wait time
    int getLongestWaitTime() const {
        return longestWaitTime;
    }
    }
    int Office::totalWaitTime() {
    int total = 0;
    for (int i = 0; i < numWindows; ++i) {
        total += windows[i].customersWaitingOver10Minutes();
    }
    return total;
}

    int Office::longestWaitTime() {
        int longest = 0;
        for (int i = 0; i < numWindows; ++i) {
            if (windows[i].customersWaitingOver10Minutes() > longest) {
                longest = windows[i].customersWaitingOver10Minutes();
        }
    }
    return longest;
    }

};
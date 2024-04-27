#ifndef OFFICE_H
#define OFFICE_H
#include <iostream>
#include "Window.h"

#include "ListQueue.h" // This assumes you have a queue implementation to manage waiting customers
#include "Customer.h"
using namespace std;

class Office {
public:
    Office(int numWindows); // Constructor to initialize with a specific number of windows
    ~Office(); // Destructor

    void addCustomer(Customer* customer); // Adds a customer to the queue
    void processTick(); // Processes one tick of time, handling customer assignment and window updates
    void processTime(char office);
    void printStatistics() const; // Print out statistics about customer wait times and window idle times
    
    Window** windows; // Pointer to an array of Window objects
    int numWindows; // Number of windows in this office
    ListQueue<Customer*> customerQueue; // Queue of customers waiting for service
    Customer* currCustomer;

    // Helper methods
    void assignCustomerToWindow(); // Assigns a waiting customer to an available window if possible
    bool isWindowAvailable(); // Checks if there is at least one available window
    void printInfo();
    void setWindows(int num);
    Customer* dequeue(){
        return customerQueue.dequeue();
    }
    Customer* getCurrCustomer(){
        return currCustomer;
    }
    void setCurrCustomer(Customer* tempCustomer){
        this->currCustomer = tempCustomer;
    }
    bool isEmpty(){
        return customerQueue.isEmpty();
    };
    void finished(int i){
        windows[i]->release();
    }
};

#endif // OFFICE_H

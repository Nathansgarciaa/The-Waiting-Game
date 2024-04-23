#include <iostream>
#include "Window.cpp"
#include "ListQueue.h"  // Include your ListQueue implementation here

class Office {
public:
    std::string officeName;
    Window* windows;
    int numWindows;
    ListQueue<Customer*> queue;
    int totalCustomers = 0; // Ensure it's initialized
    int StudentWaitTime = 0; // Ensure it's initialized
    int maxWaitTime = 0;

    Office(int numberOfWindows, std::string name) : numWindows(numberOfWindows), officeName(name) {
        windows = new Window[numWindows];
        std::cout << "Office created: " << officeName << " with " << numWindows << " windows." << std::endl;
    }

    ~Office() {
        delete[] windows;
    }

    void addCustomer(Customer* customer) {
        queue.enqueue(customer);
        totalCustomers++;
        std::cout << "Customer added to " << officeName << ". Total now: " << totalCustomers << std::endl;
    }

    void nextInLine() {
        for (int i = 0; i < numWindows; ++i) {
            if (!windows[i].isOccupied() && !queue.isEmpty()) {
                Customer* customer = queue.dequeue();
                windows[i].setCustomer(customer);
                customer->SetWindowTrue();
                std::cout << "Customer moved to window in " << officeName << std::endl;
            }
            windows[i].checkTime();
        }
    }

    double meanWaitTime(){
        if (totalCustomers == 0) return 0; // Prevent division by zero
        return static_cast<double>(StudentWaitTime) / totalCustomers;
    }
};

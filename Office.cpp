#include <iostream>
#include "Window.cpp"
#include "ListQueue.h"  // Include your ListQueue implementation here

class Office {
public:
    std::string officeName;
    Window* windows;
    int numWindows;
    ListQueue<int> queue;

    Office(int numberOfWindows, std::string name) : numWindows(numberOfWindows), officeName(name) {
        windows = new Window[numWindows];
    }

    ~Office() {
        delete[] windows;
    }

    void addCustomer(int customerID) {
        queue.enqueue(customerID);
        std::cout << "Customer " << customerID << " added to the queue at " << officeName << "." << std::endl;
    }

    void processCustomers() {
        for (int i = 0; i < numWindows; ++i) {
            if (!windows[i].isOccupied() && !queue.isEmpty()) {
                int customerID = queue.dequeue();
                windows[i].occupy();
                std::cout << "Customer " << customerID << " assigned to window " << i << " at " << officeName << "." << std::endl;
            }
        }
    }

    void displayWindows() const {
        for (int i = 0; i < numWindows; ++i) {
            std::cout << "Window " << i << " at " << officeName << (windows[i].isOccupied()? ": Occupied" : ": Free") << std::endl;
        }
    }
};

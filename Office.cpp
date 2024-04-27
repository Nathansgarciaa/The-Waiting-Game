#include "Office.h"

Office::Office(int numberOfWindows, std::string name) : numWindows(numberOfWindows), officeName(std::move(name)) {
    windows = new Window[numWindows];
    std::cout << "Office created: " << officeName << " with " << numWindows << " windows." << std::endl;
}

Office::~Office() {
    delete[] windows;
}

void Office::addCustomer(Customer* customer) {
    queue.enqueue(customer);
    totalCustomers++;
    std::cout << "Customer added to " << officeName << ". Total now: " << totalCustomers << std::endl;
}

void Office::updateOffice() {
    int processedCustomers = 0;
    while (!queue.isEmpty() && processedCustomers < queue.getSize()) {
        Customer* customer = queue.dequeue();
        customer->increaseWaitTime();
        queue.enqueue(customer);
        processedCustomers++;
}

    for (int i = 0; i < numWindows; ++i) {
        if (!windows[i].isOccupied() && !queue.isEmpty()) {
            windows[i].occupy();
            Customer* customer = queue.dequeue();
            if(customer->getWaitTime() > StudentWaitTime){
                StudentWaitTime += customer->getWaitTime();
            }
            
            std::cout << "Assigning customer to window " << i << " in " << officeName << std::endl;

            windows[i].setCustomer(customer);
        }
        
        windows[i].checkTime();
    }

    while (!nextQueue.isEmpty()) {
        Customer* customer = nextQueue.dequeue();
        queue.enqueue(customer);
    }
}

double Office::meanWaitTime() const {
    return static_cast<double>(StudentWaitTime) / totalCustomers;
}

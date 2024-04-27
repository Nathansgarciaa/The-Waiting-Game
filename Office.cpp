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
    

    for (int i = 0; i < numWindows; ++i) {
        if (!windows[i].isOccupied() && !queue.isEmpty()) {
            totalIdleTime += windows[i].getIdleTime();
            if(windows[i].getIdleTime() > longestWindowIdleTime){
                longestWindowIdleTime = windows[i].getIdleTime();
            }
            if(windows[i].getIdleTime() > 4){
                numWindowsIdle5mins++;
            }
            windows[i].occupy();

            Customer* customer = queue.dequeue();
            totalCustomers++;
            
            StudentWaitTime += customer->getWaitTime();
            
            if(customer->getWaitTime() > maxWaitTime){
                maxWaitTime = customer->getWaitTime();
            }
            if(customer->getWaitTime() > 9){
                numStudents10Mins += 1;
            }
           

            
            std::cout << "Assigning customer to window " << i << " in " << officeName << std::endl;

            windows[i].setCustomer(customer);
        }
        
        windows[i].checkTime();
    }
    while (!queue.isEmpty() && processedCustomers < queue.getSize()) {
        Customer* customer = queue.dequeue();
        customer->increaseWaitTime();
        std::cout <<"waitTime: "  << customer->getWaitTime() << std::endl;
        queue.enqueue(customer);
        processedCustomers++;
        
}

    while (!nextQueue.isEmpty()) {
        Customer* customer = nextQueue.dequeue();
        queue.enqueue(customer);
    }
}

double Office::meanWaitTime() const {
    return static_cast<double>(StudentWaitTime) / totalCustomers;
}
double Office::getMeanIdleTime(){
    return totalIdleTime / numWindows;


}
int Office::getLongestWindowIdleTime(){
    return longestWindowIdleTime;
}

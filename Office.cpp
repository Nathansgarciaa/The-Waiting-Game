#include "Office.h"

Office::Office(int numWindows) : numWindows(numWindows) {
    currCustomer  = new Customer();
    windows = new Window*[numWindows];  // Allocate memory for windows
    for (int i = 0; i < numWindows; ++i) {
        windows[i] = new Window();      // Initialize each window
    }
}

Office::~Office() {
    for (int i = 0; i < numWindows; i++) {
        delete windows[i];
    }
    delete[] windows;
}

void Office::addCustomer(Customer* customer) {
    customerQueue.enqueue(customer); // Add customer to the queue
}

void Office::processTick() {
    // First, try to assign customers to any available windows
    assignCustomerToWindow();

    // Update idle times for each window
    for (int i = 0; i < numWindows; i++) {
        if (!windows[i]->isOccupied()) {
            windows[i]->incrementIdleTime();
        }
    }
}

void Office::printStatistics() const {
    // Implementation for printing statistics can go here
}

void Office::assignCustomerToWindow() {
    for (int i = 0; i < numWindows; i++) {
        if (!windows[i]->isOccupied()) {
            windows[i]->occupy(currCustomer);
        }
    }
}

bool Office::isWindowAvailable(){
    for (int i = 0; i < numWindows; i++) {
        if (!windows[i]->isOccupied()) {
            return true;
        }
    }
    return false;
}

void Office::setWindows(int newNumWindows) {
    // Delete existing windows
    for (int i = 0; i < numWindows; i++) {
        delete windows[i];
    }
    delete[] windows;

    // Allocate new windows
    windows = new Window*[newNumWindows];
    for (int i = 0; i < newNumWindows; i++) {
        windows[i] = new Window();
    }
    this->numWindows = newNumWindows;
}

void Office::printInfo(){
    
    
    cout << "Office Time: " << currCustomer->getRegistrarTime() << endl;
}

void Office::processTime(char office){
    if(office == 'R'){
        
    }
}
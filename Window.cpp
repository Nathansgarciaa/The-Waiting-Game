
#include <iostream>

class Window {
private:
    bool occupied;   // Indicates whether the window is currently occupied
     Customer* currentCustomer;  // Customer currently at the window
public:
    // Constructor
    Window() : occupied(false) {} // Initially, the window is not occupied
   
    // Function to occupy the window
    void occupy() {
        if (!occupied) {
            occupied = true;
            std::cout << "Window is now occupied." << std::endl;
        } else {
            std::cout << "Window is already occupied." << std::endl;
        }
    }
    void setCustomer(Customer* customer) {
        occupied = true;
        currentCustomer = customer;
        std::cout << "Customer set at window." << std::endl;
    }
    Customer* getCurrentCustomer() {
        return currentCustomer;
    }
    bool isCustomerDone() const {
        return currentCustomer == nullptr || currentCustomer->isDone();  // Assuming Customer has a method 'isDone' to check completion
    }

    // Function to free the window
    void free() {
        if (occupied) {
            occupied = false;
            std::cout << "Window is now free." << std::endl;
        } else {
            std::cout << "Window is already free." << std::endl;
        }
    }

    // Function to check if the window is occupied
    bool isOccupied() const {
        return occupied;
    }
};

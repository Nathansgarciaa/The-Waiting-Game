#include <iostream>
#include "Customer.h"
#include "ListQueue.h"
#include <string>

class Window {
private:
    bool occupied = false;
    Customer* currentCustomer = nullptr;
    int idleTime = 0;
    int occupiedTime = 0;

public:
    Window() {}

    void occupy() {
        if (!occupied) {
            occupied = true;
            std::cout << "Window is now occupied." << std::endl;
        } else {
            std::cout << "Window is already occupied." << std::endl;
        }
    }

    void checkTime() {
        if (occupied && currentCustomer != nullptr) {
            if (currentCustomer->getCashierTime() <= 0) {
                free();
            }
            if (currentCustomer->getRegisterTime() <= 0) {
                free();
            }
            if (currentCustomer->getFinancialAidTime() <= 0) {
                free();
            }
        }
        if (isOccupied()) {
            occupiedTime += 1;
            idleTime = 0;
            std::cout << "Window occupied time: " << occupiedTime << " at window." << std::endl;
        } else {
            idleTime += 1;
            occupiedTime = 0;
            std::cout << "Window idle time: " << idleTime << " at window." << std::endl;
        }
    }

    void setCustomer(Customer* customer) {
        occupy();
        currentCustomer = customer;
        std::cout << "Customer set at window: Processing time starts." << std::endl;
    }

    void free() {
        if (occupied) {
            occupied = false;
            currentCustomer = nullptr; // Important to clear customer
            std::cout << "Window is now free." << std::endl;
        } else {
            std::cout << "Window was already free." << std::endl;
        }
    }

    bool isOccupied() const {
        return occupied;
    }
};

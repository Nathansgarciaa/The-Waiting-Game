
#include <iostream>
#include "Customer.h"
#include <string>
#include <iostream>

#include <iostream>
#include "Customer.h"
#include "ListQueue.h"
#include <string>

class Window {
private:
    bool occupied;   // Indicates whether the window is currently occupied
    Customer* currentCustomer;  // Customer currently at the window
    int idleTime;
    int occupiedTime;

public:
    Window() : occupied(false), currentCustomer(nullptr), idleTime(0), occupiedTime(0) {}

    void occupy() {
        if (!occupied) {
            occupied = true;
            std::cout << "Window is now occupied." << std::endl;
        } else {
            std::cout << "Window is already occupied." << std::endl;
        }
    }

    void processTime() {
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
            std::cout << occupiedTime << std::endl;
        }
        if (!isOccupied()) {
            idleTime += 1;
            occupiedTime = 0;
            std::cout << idleTime << std::endl;
        }
    }

    void setCustomer(Customer* customer) {
        occupy();
        currentCustomer = customer;
        std::cout << "Customer set at window." << std::endl;
    }

    void free() {
        if (occupied) {
            occupied = false;
            std::cout << "Window is now free." << std::endl;
        } else {
            std::cout << "Window is already free." << std::endl;
        }
    }

    bool isOccupied() const {
        return occupied;
    }

    int getIdleTime() const {
        return idleTime;
    }
        int customersWaitingOver10Minutes() {
        int count = 0;
        if (currentCustomer != nullptr) {
            if (currentCustomer->getRegisterTime() > 10 || currentCustomer->getCashierTime() > 10 || currentCustomer->getFinancialAidTime() > 10) {
                count++;
            }
        }
        return count;
    }

    bool idleOver5Minutes() {
        return idleTime > 5;
    }

};

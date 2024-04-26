#include "Window.h"

void Window::occupy() {
    if (!occupied) {
        occupied = true;
        std::cout << "Window is now occupied." << std::endl;
    } else {
        std::cout << "Window is already occupied." << std::endl;
    }
}

void Window::checkTime() {
    if (currentCustomer != nullptr) {
        currentCustomer->increaseWindowTime();
        if (occupied) {
            switch (currentCustomer->getCurrentOffice()) {
                case 'R':
                    if (currentCustomer->getWindowTime() == currentCustomer->getRegisterTime()) {
                        releaseCustomer();
                    }
                    break;
                case 'C':
                    if (currentCustomer->getWindowTime() == currentCustomer->getCashierTime()) {
                        releaseCustomer();
                    }
                    break;
                case 'F':
                    if (currentCustomer->getWindowTime() == currentCustomer->getFinancialAidTime()) {
                        releaseCustomer();
                    }
                    break;
            }
        }
    }

    if (isOccupied()) {
        occupiedTime++;
        //std::cout << "Window occupied time: " << occupiedTime << " at window." << std::endl;
    } else {
        idleTime++;
        //std::cout << "Window idle time: " << idleTime << " at window." << std::endl;
    }
}

void Window::setCustomer(Customer* customer) {
    if (!occupied) {
        currentCustomer = customer;
        occupy();
        std::cout << "Customer set at window: Processing time starts." << std::endl;
    }
}

void Window::releaseCustomer() {
    if (occupied && currentCustomer) {
        occupied = false;
        waitingQueue.enqueue(currentCustomer);
        currentCustomer = nullptr;
        std::cout << "Window is now free." << std::endl;
    } else {
        std::cout << "No customer to release or window already free." << std::endl;
    }
}

bool Window::isOccupied() const {
    return occupied;
}

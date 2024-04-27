#include "Window.h"

Window::Window() : occupied(false), idleTime(0), currentCustomer(nullptr) {
}

Window::~Window() {
    // Optional: Handle any cleanup needed
}

bool Window::isOccupied(){
    return occupied;
}

void Window::occupy(Customer* customer) {
    this->currentCustomer = customer;
    this->occupied = true;
    this->idleTime = 0; // Reset idle time when occupied
}

void Window::release() {
    occupied = false;
}

int Window::getIdleTime() const {
    return this->idleTime;
}

void Window::incrementIdleTime() {
    if (!occupied) {
        this->idleTime++;
    }
}

void Window::processWindow(){
    
}


#include <iostream>
#include "Customer.h"
#include <string>
#include <iostream>

class Window {
private:
    bool occupied;   // Indicates whether the window is currently occupied
    Customer* currentCustomer;  // Customer currently at the window
    int idleTime;
    int occupiedTime; // Missing semicolon here
public:
    // Constructor
    Window() : occupied(false), currentCustomer(nullptr), idleTime(0), occupiedTime(0) {} // Initially, the window is not occupied
   
    // Function to occupy the window
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
            // Decrease the time the customer needs at this window
            if(currentCustomer->getCashierTime() <= 0){
                free();
            }
            if(currentCustomer->getRegisterTime() <= 0){
                free();
            }
            if(currentCustomer->getFinancialAidTime() <= 0){
                free();
            }
        }
        if(isOccupied()){
            occupiedTime += 1;
            idleTime = 0;
            std::cout << occupiedTime << std::endl;
        }
        if(!isOccupied()){
            idleTime += 1;
            occupiedTime = 0;
            std::cout << idleTime << std::endl;
            
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

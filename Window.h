#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h" // Assuming Customer class handles student details

class Window {
public:
    Window();  // Constructor
    ~Window(); // Destructor

    bool isOccupied(); // Check if the window is currently occupied
    void occupy(Customer* customer); // Assign a customer to the window
    void release(); // Release the current customer
    int getIdleTime() const; // Get the idle time of the window
    void incrementIdleTime(); // Increment the idle time
    void processWindow();

private:
    bool occupied;     // Is the window currently occupied?
    int idleTime;      // Total time the window has been idle
    Customer* currentCustomer; // Pointer to the current customer being served
};

#endif // WINDOW_H

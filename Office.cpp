#include <iostream>
#include "Window.cpp"

#include "ListQueue.h"  // Include your ListQueue implementation here

class Office {
public:
    std::string officeName;
    Window* windows;
    int numWindows;
    ListQueue<Customer*> queue;

    Office(int numberOfWindows, std::string name) : numWindows(numberOfWindows), officeName(name) {
        windows = new Window[numWindows];
    }

    ~Office() {
        delete[] windows;
    }

    void addCustomer(Customer* customer) {
        queue.enqueue(customer);
        nextInLine();
        


        
    }

    void nextInLine() {
        for (int i = 0; i < numWindows; ++i) {
            if (!windows[i].isOccupied() && !queue.isEmpty()) {
                
                Customer* customer = queue.dequeue();
                windows[i].occupy();
                

             
            }
            windows[i].processTime();
        }
    }

    
    
};

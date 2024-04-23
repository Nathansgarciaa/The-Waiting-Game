#include "Office.cpp"
#include "Customer.h"
#include "ListQueue.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm> // for std::max
using namespace std;

class ServiceCenter {
private:
    Office* registrar;
    Office* cashier;
    Office* financialAid;
    ListQueue<Customer*>* scc;

public:
    // Constructor initialization list syntax corrected with proper initialization.
    ServiceCenter() : registrar(nullptr), cashier(nullptr), financialAid(nullptr), scc(new ListQueue<Customer*>()) {}

    // Destructor with proper deletion of members.
    ~ServiceCenter() {
        delete registrar;
        delete cashier;
        delete financialAid;
        delete scc; // Ensure deletion of the queue as well
    }

    // Function to process customers and calculate metrics.
    void processCustomers() {
        while (!scc->isEmpty()) {
            Customer* customer = scc->dequeue();
            char direction = customer->getCurrentOffice();
            if (!customer->officeStatus()) {  // use ! for boolean checks
                switch (direction) {  // using switch-case for clarity
                    case 'R':
                        registrar->addCustomer(customer);
                        break;
                    case 'C':
                        cashier->addCustomer(customer);
                        break;
                    case 'F':
                        financialAid->addCustomer(customer);
                        break;
                }
            }

            if (customer->officeStatus()) {
                if (!customer->windowStatus()) {
                    customer->waitTime++;
                }
                switch (direction) {
                    case 'R':
                        if (customer->waitTime > registrar->maxWaitTime) {
                            registrar->maxWaitTime = customer->waitTime;
                        }
                        registrar->nextInLine();
                        break;
                    case 'C':
                        if (customer->waitTime > cashier->maxWaitTime) {
                            cashier->maxWaitTime = customer->waitTime;
                        }
                        customer->waitTime++;
                        cashier->nextInLine();
                        break;
                    case 'F':
                        if (customer->waitTime > financialAid->maxWaitTime) {
                            financialAid->maxWaitTime = customer->waitTime;
                        }
                        customer->waitTime++;
                        financialAid->nextInLine();
                        break;
                }
            }
        
            if (customer->getWindowTime() == customer->getCashierTime() || customer->getWindowTime() == customer->getRegisterTime() || customer->getWindowTime() == customer->getFinancialAidTime()) {
                int& studentWaitTime = direction == 'R' ? registrar->StudentWaitTime :
                                      direction == 'C' ? cashier->StudentWaitTime : financialAid->StudentWaitTime;
                studentWaitTime += customer->waitTime;
                customer->setWindowTime(0);
                customer->waitTime = 0;
                customer->nextOffice();
            }
        }
    }

    // Function to process the input file and simulate the service process.
    void processFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cerr << "Cannot open file: " << filename << endl;
            return;
        }
        int numRegWindows, numCashWindows, numFinAidWindows;
        file >> numRegWindows >> numCashWindows >> numFinAidWindows;

        registrar = new Office(numRegWindows, "Registrar");
        cashier = new Office(numCashWindows, "Cashier");
        financialAid = new Office(numFinAidWindows, "Financial Aid");

        ListQueue<Customer*> arrivals[101];  // Assuming ticks are from 0 to 100
        string line;
        int tick = 0;
        while (getline(file, line)) {
            if (line.length() == 1) {  // Check if the line is a tick
                tick = stoi(line);  // Update the current tick
                continue;
            }
            istringstream iss(line);
            int regTime, cashTime, finAidTime;
            char order[3];
            iss >> regTime >> cashTime >> finAidTime >> order[0] >> order[1] >> order[2];
            if (tick >= 0 && tick <= 100) {
                Customer* customer = new Customer(regTime, cashTime, finAidTime, order[0], order[1], order[2]);
                arrivals[tick].enqueue(customer);
            }
        }

        // Process customers at each tick
        for (int currentTick = 0; currentTick <= 100; ++currentTick) {
            while (!arrivals[currentTick].isEmpty()) {
                scc->enqueue(arrivals[currentTick].dequeue());
            }
            processCustomers();
        }

        // Output mean wait times after simulation
        cout << "Registrar Mean Wait Time: " << registrar->meanWaitTime() << endl;
        cout << "Cashier Mean Wait Time: " << cashier->meanWaitTime() << endl;
        cout << "Financial Aid Mean Wait Time: " << financialAid->meanWaitTime() << endl;
    }
};

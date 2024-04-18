#include "Office.cpp"
#include "Customer.h"
#include "ListQueue.h"
#include <fstream>
#include <string>
#include<sstream>
#include <iostream>
#include <algorithm> // for std::max
using namespace std;

class ServiceCenter {
private:
    Office* registrar;
    Office* cashier;
    Office* financialAid;
    ListQueue<Customer*>* scc;

    // Variables to store metrics
    int totalWaitTimeRegistrar;
    int totalWaitTimeCashier;
    int totalWaitTimeFinancialAid;
    int longestWaitTimeRegistrar;
    int longestWaitTimeCashier;
    int longestWaitTimeFinancialAid;
    int studentsWaitingOver10Minutes;
    int totalIdleTimeRegistrar;
    int totalIdleTimeCashier;
    int totalIdleTimeFinancialAid;
    int longestIdleTimeRegistrar;
    int longestIdleTimeCashier;
    int longestIdleTimeFinancialAid;
    int windowsIdleOver5Minutes;

public:
    ServiceCenter() : registrar(nullptr), cashier(nullptr), financialAid(nullptr), scc(new ListQueue<Customer*>()), 
        totalWaitTimeRegistrar(0), totalWaitTimeCashier(0), totalWaitTimeFinancialAid(0), 
        longestWaitTimeRegistrar(0), longestWaitTimeCashier(0), longestWaitTimeFinancialAid(0), 
        studentsWaitingOver10Minutes(0), totalIdleTimeRegistrar(0), totalIdleTimeCashier(0), totalIdleTimeFinancialAid(0),
        longestIdleTimeRegistrar(0), longestIdleTimeCashier(0), longestIdleTimeFinancialAid(0), 
        windowsIdleOver5Minutes(0) {}

    ~ServiceCenter() {
        delete registrar;
        delete cashier;
        delete financialAid;
        delete scc; // Ensure deletion of the queue as well
    }

    // Function to process customers and calculate metrics
    void processCustomers() {
        while (!scc->isEmpty()) {
            Customer* customer = scc->dequeue();
            customer->nextTime(); // Properly increment time

            char direction = customer->getCurrentOffice();
            if (customer->officeStatus() == false) {
                if (direction == 'R') {
                    registrar->addCustomer(customer);
                } else if (direction == 'C') {
                    cashier->addCustomer(customer);
                } else if (direction == 'F') {
                    financialAid->addCustomer(customer);
                }
            }

            if (customer->getTime() == customer->getCashierTime() || customer->getTime() == customer->getRegisterTime() || customer->getTime() == customer->getFinancialAidTime()) {
                if (customer->getCurrentOffice() == 'R') {
                    customer->setRegisterTime(0);
                    customer->setTime(0);
                } else if (customer->getCurrentOffice() == 'C') {
                    customer->setCashierTime(0);
                    customer->setTime(0);
                } else if (customer->getCurrentOffice() == 'F') {
                    customer->setFinancialAidTime(0);
                    customer->setTime(0);
                }
                customer->nextOffice();
            }
        }
    }

    // Function to process the input file and calculate metrics
    void processFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return;
        }
        int numRegWindows, numCashWindows, numFinAidWindows;
        file >> numRegWindows >> numCashWindows >> numFinAidWindows;

        registrar = new Office(numRegWindows, "Registrar");
        cashier = new Office(numCashWindows, "Cashier");
        financialAid = new Office(numFinAidWindows, "Financial Aid");

        std::string line;
        int tick = 0;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (line.length() == 1) {  // Check if the line contains only one character
                tick = std::stoi(line);
                processCustomers(); // Process customers at the beginning of each minute
                continue;
            }
            int regTime, cashTime, finAidTime;
            char order[3];
            iss >> regTime >> cashTime >> finAidTime >> order[0] >> order[1] >> order[2];
            // Assuming tick is the time of entry
            Customer* customer = new Customer(regTime, cashTime, finAidTime, order[0], order[1], order[2]);
            scc->enqueue(customer);
            processCustomers();
        }

        // Process any remaining customers after reading all lines
       

        file.close();

       
    }
};
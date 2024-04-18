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
        }

        // Process any remaining customers after reading all lines
        processCustomers();

        file.close();

        // Calculate and display metrics
        calculateAndDisplayMetrics();
    }

    // Function to calculate and display metrics
    void calculateAndDisplayMetrics() {
        std::cout << "Metrics:" << std::endl;

        // Calculate mean and longest wait time for each office
        calculateWaitTimesMetrics();

        // Calculate the number of students waiting over 10 minutes
        calculateStudentsWaitingOver10Minutes();

        // Calculate mean and longest window idle time for each office
        calculateIdleTimesMetrics();

        // Calculate the number of windows idle for over 5 minutes
        calculateWindowsIdleOver5Minutes();
    }

    // Function to calculate mean and longest wait time for each office
    void calculateWaitTimesMetrics() {
        std::cout << "Mean and Longest wait time for each office:" << std::endl;

        calculateAndDisplayWaitTimeMetrics(registrar, totalWaitTimeRegistrar, longestWaitTimeRegistrar, "Registrar");
        calculateAndDisplayWaitTimeMetrics(cashier, totalWaitTimeCashier, longestWaitTimeCashier, "Cashier");
        calculateAndDisplayWaitTimeMetrics(financialAid, totalWaitTimeFinancialAid, longestWaitTimeFinancialAid, "Financial Aid");
    }

    // Function to calculate mean and longest window idle time for each office
    void calculateIdleTimesMetrics() {
        std::cout << "Mean and Longest window idle time for each office:" << std::endl;

        calculateAndDisplayIdleTimeMetrics(registrar, totalIdleTimeRegistrar, longestIdleTimeRegistrar, "Registrar");
        calculateAndDisplayIdleTimeMetrics(cashier, totalIdleTimeCashier, longestIdleTimeCashier, "Cashier");
        calculateAndDisplayIdleTimeMetrics(financialAid, totalIdleTimeFinancialAid, longestIdleTimeFinancialAid, "Financial Aid");
    }

    // Function to calculate and display mean and longest wait time for an office
    void calculateAndDisplayWaitTimeMetrics(Office* office, int& totalWaitTime, int& longestWaitTime, const std::string& officeName) {
        if (office->totalCustomers() == 0) {
            std::cout << officeName << " has no waiting times." << std::endl;
            return;
        }

        totalWaitTime = office->totalWaitTime();
        longestWaitTime = office->longestWaitTime();
        double meanWaitTime = static_cast<double>(totalWaitTime) / office->totalCustomers();

        std::cout << "Mean wait time at " << officeName << ": " << meanWaitTime << " minutes." << std::endl;
        std::cout << "Longest wait time at " << officeName << ": " << longestWaitTime << " minutes." << std::endl;
    }

    // Function to calculate the number of students waiting over 10 minutes
    void calculateStudentsWaitingOver10Minutes() {
        studentsWaitingOver10Minutes = 0;

        studentsWaitingOver10Minutes += countStudentsWaitingOver10Minutes(registrar);
        studentsWaitingOver10Minutes += countStudentsWaitingOver10Minutes(cashier);
        studentsWaitingOver10Minutes += countStudentsWaitingOver10Minutes(financialAid);

        std::cout << "Number of students waiting over 10 minutes total across all offices: " << studentsWaitingOver10Minutes << std::endl;
    }

    // Function to count the number of students waiting over 10 minutes in an office
    int countStudentsWaitingOver10Minutes(Office* office) {
        int count = 0;
        for (int i = 0; i < office->numWindows(); ++i) {
            count += office->windows[i].customersWaitingOver10Minutes();
        }
        return count;
    }

    // Function to calculate and display mean and longest window idle time for an office
    void calculateAndDisplayIdleTimeMetrics(Office* office, int& totalIdleTime, int& longestIdleTime, const std::string& officeName) {
        if (office->numWindows() == 0) {
            std::cout << officeName << " has no windows." << std::endl;
            return;
        }

        totalIdleTime = office->totalIdleTime();
        longestIdleTime = office->longestIdleTime();
        double meanIdleTime = static_cast<double>(totalIdleTime) / office->numWindows();

        std::cout << "Mean idle time at " << officeName << ": " << meanIdleTime << " minutes." << std::endl;
        std::cout << "Longest idle time at " << officeName << ": " << longestIdleTime << " minutes." << std::endl;
    }

    // Function to calculate the number of windows idle for over 5 minutes
    void calculateWindowsIdleOver5Minutes() {
        windowsIdleOver5Minutes = 0;

        windowsIdleOver5Minutes += countWindowsIdleOver5Minutes(registrar);
        windowsIdleOver5Minutes += countWindowsIdleOver5Minutes(cashier);
        windowsIdleOver5Minutes += countWindowsIdleOver5Minutes(financialAid);

        std::cout << "Number of windows idle for over 5 minutes across all offices: " << windowsIdleOver5Minutes << std::endl;
    }

    // Function to count the number of windows idle for over 5 minutes in an office
    int countWindowsIdleOver5Minutes(Office* office) {
        int count = 0;
        for (int i = 0; i < office->numWindows(); ++i) {
            count += office->windows[i].idleOver5Minutes();
        }
        return count;
    }
};

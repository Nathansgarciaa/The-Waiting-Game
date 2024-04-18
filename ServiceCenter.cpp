#include "Office.cpp"
#include "Customer.h"
#include "ListQueue.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

class ServiceCenter
{
private:
    Office *registrar = nullptr;
    Office *cashier = nullptr;
    Office *financialAid = nullptr;
    ListQueue<Customer*> *scc;

public:
    ServiceCenter() : scc(new ListQueue<Customer*>()) {}

    ~ServiceCenter()
    {
        delete registrar;
        delete cashier;
        delete financialAid;
        delete scc; // Ensure deletion of the queue as well
    }

    void processCustomers() {
        while (!scc->isEmpty()) {
            Customer* customer = scc->dequeue();
            customer->nextTime(); // Properly increment time

            char direction = customer->getCurrentOffice();
            if(customer->officeStatus() == false){
                if(direction == 'R') {
                    registrar->addCustomer(customer);
            }    else if (direction == 'C') {
                    cashier->addCustomer(customer);
            }   else if (direction == 'F') {
                    financialAid->addCustomer(customer);
            }
            }
            
            

            if (customer->getTime() == customer->getCashierTime() || customer->getTime() == customer->getRegisterTime() || customer->getTime() == customer->getFinancialAidTime()) {
                if(customer->getCurrentOffice() == 'R'){
                    customer->setRegisterTime(0);
                    customer->setTime(0);

                }
                if(customer->getCurrentOffice() == 'C'){
                    customer->setCashierTime(0);
                    customer->setTime(0);
                }
                if(customer->getCurrentOffice() == 'F'){
                    customer->setFinancialAidTime(0);
                    customer->setTime(0);
                }
                customer->nextOffice();
                

            }
        }
    }

    void processFile(const std::string &filename) {
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
             for(int i = 0; i < 100; i++){
                    if (line.length() == 1) {  // Check if the line contains only one character
                        tick = std::stoi(line);
                        continue;
           }        if(tick == i){
                        int regTime, cashTime, finAidTime;
                        char order[3];
                        iss >> regTime >> cashTime >> finAidTime >> order[0] >> order[1] >> order[2];
                // Assuming tick is the time of entry
                        Customer *customer = new Customer(regTime, cashTime, finAidTime, order[0], order[1], order[2]);
                        scc->enqueue(customer);
                        processCustomers();
            
        }

        file.close();
    }
}
    }
} // <-- Added missing closing brace
;
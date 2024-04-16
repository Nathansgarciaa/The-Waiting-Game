#include "Office.cpp"
#include "Customer.cpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class ServiceCenter {
private:
    Office* registrar;
    Office* cashier;
    Office* financialAid;

public:
    ServiceCenter(int registrarWindows, int cashierWindows, int financialAidWindows) {
        registrar = new Office(registrarWindows, "Registrar");
        cashier = new Office(cashierWindows, "Cashier");
        financialAid = new Office(financialAidWindows, "Financial Aid");
    }

    ~ServiceCenter() {
        delete registrar;
        delete cashier;
        delete financialAid;
    }

    void processDay() {
        // Simulate a day of processing
        registrar->processCustomers();
        cashier->processCustomers();
        financialAid->processCustomers();
    }

    void processFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return;
        }

        int time, numberOfStudents;
        while (file >> time >> numberOfStudents) {
            for (int i = 0; i < numberOfStudents; ++i) {
                int regTime, cashTime, finAidTime;
                std::string order;
                file >> regTime >> cashTime >> finAidTime >> order;

                // Create a new customer with the times read
                Customer* customer = new Customer(regTime, cashTime, finAidTime);
                for (int j = 0; j < 3; ++j) {
                    customer->order[j] = order[j];
                }

                // Decide where to add customers based on the first office in their order
                switch (customer->order[0]) {
                    case 'R':
                        registrar->addCustomer(customer);  // Assuming addCustomer can take a pointer to Customer
                        break;
                    case 'C':
                        cashier->addCustomer(customer);
                        break;
                    case 'F':
                        financialAid->addCustomer(customer);
                        break;
                }
            }
        }

        file.close();
    }
};

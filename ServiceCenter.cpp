#include "ServiceCenter.h"


ServiceCenter::ServiceCenter() : registrar(nullptr), cashier(nullptr), financialAid(nullptr) {}

ServiceCenter::~ServiceCenter() {
    delete registrar;
    delete cashier;
    delete financialAid;
}

void ServiceCenter::processCustomers() {
    while (!scc.isEmpty()) {
        Customer* customer = scc.dequeue();

        char direction = customer->getCurrentOffice();
        switch (direction) {
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

        registrar->updateOffice();
        cashier->updateOffice();
        financialAid->updateOffice();
    }
}

void ServiceCenter::processFile(const std::string& filename) {
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
    std::getline(file, line); // Consume the rest of the line after reading window counts

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int tick, numStudents, regTime, cashTime, finAidTime;
        char order[3];
        
        iss >> tick >> numStudents;
        std::cout << "Processing tick: " << tick << " with " << numStudents << " students.\n";
        for (int i = 0; i < numStudents; ++i) {
            iss >> regTime >> cashTime >> finAidTime >> order[0] >> order[1] >> order[2];
            std::cout << "Processing " << regTime << " " << cashTime << " " << finAidTime << " "
                << order[0] << order[1] << order[2] << ":\n";

            

            Customer* customer = new Customer(regTime, cashTime, finAidTime, order[0], order[1], order[2]);
            
            scc.enqueue(customer);
            
        }
        processCustomers(); // Process all enqueued customers
    }

    file.close();
}

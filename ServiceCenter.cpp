#include "ServiceCenter.h"


ServiceCenter::ServiceCenter() : registrar(nullptr), cashier(nullptr), financialAid(nullptr) {}

ServiceCenter::~ServiceCenter() {
    if (registrar)
        delete registrar;
    if (cashier)
        delete cashier;
    if (financialAid)
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
        std::cout << "Processed customer for office: " << direction << std::endl; // Debug output
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

    // Assume maximum number of ticks you will handle
    const int MAX_TICKS = 100;
    Customer*** customersAtTicks = new Customer**[MAX_TICKS + 1];
    int* countsAtTicks = new int[MAX_TICKS + 1](); // Initialize to zero

    int tick, numStudents;
    while (file >> tick >> numStudents && tick <= MAX_TICKS) {
        customersAtTicks[tick] = new Customer*[numStudents];
        countsAtTicks[tick] = numStudents;
        for (int i = 0; i < numStudents; ++i) {
            int regTime, cashTime, finAidTime;
            char order[3];
            if (file >> regTime >> cashTime >> finAidTime >> order[0] >> order[1] >> order[2]) {
                customersAtTicks[tick][i] = new Customer(regTime, cashTime, finAidTime, order[0], order[1], order[2]);
            } else {
                std::cerr << "Error reading student details." << std::endl;
                break;
            }
        }
    }

    file.close();

    // Processing each tick
    for (int currentTick = 1; currentTick <= MAX_TICKS; currentTick++) {
        
        if (countsAtTicks[currentTick] > 0) {
            for (int i = 0; i < countsAtTicks[currentTick]; ++i) {
                scc.enqueue(customersAtTicks[currentTick][i]);
            }
        }
        processCustomers(); // Process all customers
    }

    std::cout << "Mean wait times :\n";
    std::cout << "Registrar: " << registrar->meanWaitTime() << std::endl;
    std::cout << "Cashier: " << cashier->meanWaitTime() << std::endl;
    std::cout << "Financial Aid: " << financialAid->meanWaitTime() << std::endl;
    std::cout << "Longest Wait Times :\n";
    std::cout << "Registrar: " << registrar->maxWaitTime << std::endl;
    std::cout << "Cashier: " << cashier->maxWaitTime << std::endl;
    std::cout << "Financial Aid: " << financialAid->maxWaitTime << std::endl;
    std::cout << "Number of Students waiting 10 mins or longer:\n";
    std::cout << registrar->numStudents10Mins + cashier->numStudents10Mins + financialAid->numStudents10Mins << std::endl;
    std::cout << "Mean idle times :\n";
    std::cout << "Registrar: " << registrar->getMeanIdleTime() << std::endl;
    std::cout << "Cashier: " << cashier->getMeanIdleTime() << std::endl;
    std::cout << "Financial Aid: " << financialAid->meanWaitTime() << std::endl;
    std::cout << "Longest Window Idle Times :\n";
    std::cout << "Registrar: " << registrar->longestWindowIdleTime << std::endl;
    std::cout << "Cashier: " << cashier->longestWindowIdleTime << std::endl;
    std::cout << "Financial Aid: " << financialAid->longestWindowIdleTime << std::endl;
    std::cout << "number of windows idle over 5 mins :\n";
    std::cout << registrar->numWindowsIdle5mins + cashier->numWindowsIdle5mins + financialAid->numWindowsIdle5mins << std::endl;
   
    


    // Cleanup dynamically allocated memory
    for (int i = 1; i <= MAX_TICKS; i++) {
        if (countsAtTicks[i] > 0) {
            for (int j = 0; j < countsAtTicks[i]; ++j) {
                delete customersAtTicks[i][j];
            }
            delete[] customersAtTicks[i];
        }
    }
    delete[] customersAtTicks;
    delete[] countsAtTicks;
}

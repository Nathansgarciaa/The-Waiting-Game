#ifndef SERVICE_CENTER_H
#define SERVICE_CENTER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Office.h"
#include "ListQueue.h"
#include "Customer.h"
#include <sstream>

class ServiceCenter {
private:
    Office* registrar;
    Office* cashier;
    Office* financialAid;
    ListQueue<Customer*> scc; // Queue for all service center customers

public:
    ServiceCenter();
    ~ServiceCenter();

    void processCustomers();
    void processFile(const std::string& filename);
};

#endif // SERVICE_CENTER_H

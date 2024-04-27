#ifndef SERVICECENTER_H
#define SERVICECENTER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include "Office.h"

using namespace std;

class ServiceCenter {
public:
    ServiceCenter();
    ~ServiceCenter();
    int tick;
    int meanWaitR;
    int meanWaitC;
    int meanWaitF;
    int numStudentsOverTen;
    int meanWindIdleTimeR;
    int meanWindIdleTimeC;
    int meanWindIdleTimeF;
    int numWindIdleOverFive;

    void processFile(string& filename); //reads file and gets data
    void processDay();  // Simulates a day of operation
    void printStatistics(); // Outputs the statistics of the day's operations
    bool gameOver();

    Office* registrar;
    Office* cashier;
    Office* financialAid;
};

#endif // SERVICECENTER_H

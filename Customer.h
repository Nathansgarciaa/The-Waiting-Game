#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
using namespace std;

class Customer {
public: 
    int arrivalTime; // Time at which the customer arrives
    int rTime;       // Time needed at the registrar office
    int cTime;       // Time needed at the cashier office
    int faTime;      // Time needed at the financial aid office
    int totalTime;   // Total time needed for all services
    char office1;
    char office2; 
    char office3;


    Customer();
    Customer(int arrivalTime, int rTime, int cTime, int faTime, char office1, char office2, char office3);
    ~Customer();

    int getArrivalTime();
    int getRegistrarTime();
    int getCashierTime();
    int getFinancialAidTime();
    int getTotalTime();
    void setTotalTime(int val);
    void setArrivalTime();
    void setRegistrarTime(int num){
        this->rTime = num;
    };
    void setCashierTime(int num){
        this->cTime = num;
    };
    void setFinancialAidTime(int num){
        this->faTime = num;
    };

};

#endif

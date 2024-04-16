#include <iostream>
#include <string>

class Customer {
public:
    // Constructor to initialize the customer's times
    Customer(int registerTime, int cashierTime, int financialAidTime)
        : registerTime(registerTime), cashierTime(cashierTime), financialAidTime(financialAidTime) {}

    // Getters for each time
    int getRegisterTime() const {
        return registerTime;
    }

    int getCashierTime() const {
        return cashierTime;
    }

    int getFinancialAidTime() const {
        return financialAidTime;
    }

    // Setters for each time
    void setRegisterTime(int time) {
        registerTime = time;
    }

    void setCashierTime(int time) {
        cashierTime = time;
    }

    void setFinancialAidTime(int time) {
        financialAidTime = time;
    }

private:
    int registerTime;       // Time spent at registration
    int cashierTime;        // Time spent at cashier
    int financialAidTime;   // Time spent on financial aid
    int arrivalTime;
     char order[3]; // to store the order of offices
};

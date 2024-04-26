#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>


class Customer {
public:
    Customer(int registerTime, int cashierTime, int financialAidTime, char a, char b, char c);

    int getRegisterTime() const;
    int getCashierTime() const;
    int getFinancialAidTime() const;
    void setArrivalTime(int time);
    int getArrivalTime() const;
    char getCurrentOffice() const; // Changed to const
    void nextOffice(); // Changed to camel case
    int getWindowTime() const; // Changed to const
    void nextTime();
    void increaseWindowTime();
    void inOffice(); // Removed colon
    void notAtOffice();
    bool officeStatus() const; // Changed to const
    bool windowStatus();
    void SetWindowTrue();
    void SetWindowFalse();
    void increaseWaitTime();
    int getWaitTime();
    void setWaitTime(int i);
    void printDetails();
    
    

private:
    int registerTime;
    int cashierTime;
    int financialAidTime;
    int windowTime;
    char order[3];
    char currentOffice;
    int officeIndex;
    bool atOffice;
    bool window;
    int waitTime;
};

#endif // CUSTOMER_H

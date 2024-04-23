#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
public:
    Customer(int registerTime, int cashierTime, int financialAidTime, char a, char b, char c);

    int getRegisterTime() const;
    int getCashierTime() const;
    int getFinancialAidTime() const;
    int waitTime;
    

    void setRegisterTime(int time);
    void setCashierTime(int time);
    void setFinancialAidTime(int time);
    void setArrivalTime(int time);
    int getArrivalTime() const;
    char getCurrentOffice() const; // Changed to const
    void nextOffice(); // Changed to camel case
    int getWindowTime() const; // Changed to const
    void nextTime();
    void setWindowTime(int i);
    void inOffice(); // Removed colon
    void notAtOffice();
    bool officeStatus() const; // Changed to const
    bool windowStatus();
    void SetWindowTrue();
    void SetWindowFalse();
    

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
};

#endif // CUSTOMER_H

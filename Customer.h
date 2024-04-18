#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
public:
    Customer(int registerTime, int cashierTime, int financialAidTime, char a, char b, char c);

    int getRegisterTime() const;
    int getCashierTime() const;
    int getFinancialAidTime() const;

    void setRegisterTime(int time);
    void setCashierTime(int time);
    void setFinancialAidTime(int time);
    void setArrivalTime(int time);
    int getArrivalTime() const;
    char getCurrentOffice() const; // Changed to const
    void nextOffice(); // Changed to camel case
    int getTime() const; // Changed to const
    void nextTime();
    void setTime(int i);
    void inOffice(); // Removed colon
    void notAtOffice();
    bool officeStatus() const; // Changed to const

private:
    int registerTime;
    int cashierTime;
    int financialAidTime;
    int time;
    char order[3];
    char currentOffice;
    int officeIndex;
    bool atOffice;
};

#endif // CUSTOMER_H

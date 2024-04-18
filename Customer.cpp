#include "Customer.h"

Customer::Customer(int registerTime, int cashierTime, int financialAidTime, char a, char b, char c)
    : registerTime(registerTime), cashierTime(cashierTime), financialAidTime(financialAidTime), time(0), officeIndex(0) {
    order[0] = a;
    order[1] = b;
    order[2] = c;
    currentOffice = order[0];
    atOffice = false; // Initialize atOffice variable
}

int Customer::getRegisterTime() const {
    return registerTime;
}

int Customer::getCashierTime() const {
    return cashierTime;
}

int Customer::getFinancialAidTime() const {
    return financialAidTime;
}

void Customer::setRegisterTime(int time) {
    this->registerTime = time;
}

void Customer::setCashierTime(int time) {
    this->cashierTime = time;
}

void Customer::setFinancialAidTime(int time) {
    this->financialAidTime = time;
}

void Customer::setArrivalTime(int time) {
    this->time = time;
}

int Customer::getArrivalTime() const {
    return time;
}

char Customer::getCurrentOffice() const {
    return currentOffice;
}

void Customer::nextOffice() {
    if (officeIndex < 3) { // Ensure we don't go out of bounds
        currentOffice = order[++officeIndex];
    } else {
        // Handle the case when officeIndex is out of bounds
    }
}

int Customer::getTime() const {
    return time;
}

void Customer::nextTime() {
    ++time;
}

void Customer::setTime(int i) {
    time = i;
}

void Customer::inOffice() {
    atOffice = true;
}

void Customer::notAtOffice() {
    atOffice = false;
}

bool Customer::officeStatus() const {
    return atOffice;
}

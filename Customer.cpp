#include "Customer.h"

Customer::Customer(int registerTime, int cashierTime, int financialAidTime, char a, char b, char c)
    : registerTime(registerTime), cashierTime(cashierTime), financialAidTime(financialAidTime),officeIndex(0) {
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



char Customer::getCurrentOffice() const {
    return currentOffice;
}

void Customer::nextOffice() {
    if (officeIndex < 3) { // Ensure we don't go out of bounds
        currentOffice = order[++officeIndex];
    } 
    notAtOffice();

}

int Customer::getWindowTime() const {
    return windowTime;
}



void Customer::setWindowTime(int i) {
    windowTime = i;
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

bool Customer::windowStatus(){
    return window;
}
void Customer::SetWindowTrue(){
    window = true;
}
void Customer::SetWindowFalse(){
    window = false;
}



#include "Customer.h"

Customer::Customer(){
    arrivalTime = 0;
    rTime = 0;
    cTime = 0;
    faTime = 0;
    office1 = ' ';
    office2 = ' ';
    office3 = ' ';
    

}
Customer::Customer(int arrivalTime, int rTime, int cTime, int faTime, char office1, char office2, char office3)
    : arrivalTime(arrivalTime), rTime(rTime), cTime(cTime), faTime(faTime), office1(office1), office2(office2), office3(office3){}

Customer::~Customer() {}

int Customer::getArrivalTime() {
    return arrivalTime;
}

int Customer::getRegistrarTime() {
    return rTime;
}

int Customer::getCashierTime() {
    return cTime;
}

int Customer::getFinancialAidTime() {
    return faTime;
}

int Customer::getTotalTime() {
    return totalTime;
}

void Customer::setTotalTime(int val) {
    totalTime = val;
}


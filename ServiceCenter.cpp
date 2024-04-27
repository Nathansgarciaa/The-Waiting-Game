#include "ServiceCenter.h"


ServiceCenter::ServiceCenter(){
    Office* registrar = new Office(0);
    Office* cashier = new Office(0);
    Office* financialAid = new Office(0);
    tick=0;
    meanWaitR=0;
    meanWaitC=0;
    meanWaitF=0;
    numStudentsOverTen=0;
    meanWindIdleTimeR=0;
    meanWindIdleTimeC=0;
    meanWindIdleTimeF=0;
    numWindIdleOverFive=0;
};
ServiceCenter::~ServiceCenter(){
    delete registrar;
    delete cashier;
    delete financialAid;
};

void ServiceCenter::processFile(string& filename) {
    fstream file(filename);  // Use the passed filename instead of hard-coding it
    if (!file.is_open()) {
        cerr << "Failed to open file." << endl;
    }
    int numRegWindows, numCashWindows, numFinAidWindows, time, numStudents;
    file >> numRegWindows >> numCashWindows >> numFinAidWindows;
    registrar = new Office(numRegWindows);
    cashier = new Office(numCashWindows);
    financialAid = new Office(numFinAidWindows);

    file >> time >> numStudents;
    tick = time;
    
    int time1, time2, time3;
    char office1, office2, office3;
    file >> time1 >> time2 >> time3 >> office1 >> office2 >> office3;
    int registrarTime = 0, cashierTime = 0, financialAidTime = 0;

    if (office1 == 'R') registrarTime = time1;
    else if (office1 == 'C') cashierTime = time1;
    else if (office1 == 'F') financialAidTime = time1;

    if (office2 == 'R') registrarTime = time2;
    else if (office2 == 'C') cashierTime = time2;
    else if (office2 == 'F') financialAidTime = time2;

    if (office3 == 'R') registrarTime = time3;
    else if (office3 == 'C') cashierTime = time3;
    else if (office3 == 'F') financialAidTime = time3;

    Customer* student = new Customer(time, registrarTime, cashierTime, financialAidTime, office1, office2, office3);
    registrar->addCustomer(student);
    cashier->addCustomer(student);
    financialAid->addCustomer(student);

    
    file >> time1 >> time2 >> time3 >> office1 >> office2 >> office3;
    if (office1 == 'R') registrarTime = time1;
    else if (office1 == 'C') cashierTime = time1;
    else if (office1 == 'F') financialAidTime = time1;

    if (office2 == 'R') registrarTime = time2;
    else if (office2 == 'C') cashierTime = time2;
    else if (office2 == 'F') financialAidTime = time2;

    if (office3 == 'R') registrarTime = time3;
    else if (office3 == 'C') cashierTime = time3;
    else if (office3 == 'F') financialAidTime = time3;

    Customer* student1 = new Customer(time, registrarTime, cashierTime, financialAidTime, office1, office2, office3);
    registrar->addCustomer(student1);
    cashier->addCustomer(student1);
    financialAid->addCustomer(student1);

    file >> time1 >> time2 >> time3 >> office1 >> office2 >> office3;
    if (office1 == 'R') registrarTime = time1;
    else if (office1 == 'C') cashierTime = time1;
    else if (office1 == 'F') financialAidTime = time1;

    if (office2 == 'R') registrarTime = time2;
    else if (office2 == 'C') cashierTime = time2;
    else if (office2 == 'F') financialAidTime = time2;

    if (office3 == 'R') registrarTime = time3;
    else if (office3 == 'C') cashierTime = time3;
    else if (office3 == 'F') financialAidTime = time3;

    Customer* student2 = new Customer(time, registrarTime, cashierTime, financialAidTime, office1, office2, office3);
    registrar->addCustomer(student2);
    cashier->addCustomer(student2);
    financialAid->addCustomer(student2);

    


    file.close();  // Close the file
}


void ServiceCenter::printStatistics() {
    registrar->printInfo();
}
bool ServiceCenter::gameOver(){
    if(registrar->isEmpty() && cashier->isEmpty() && financialAid->isEmpty()){
        return true;
    }else {
        return false;
    }
}


void ServiceCenter::processDay() {
    string filename = "input.txt";
    processFile(filename);
    
    bool gameOver = false;
    while(!gameOver){

        //REGISTRAR
        if(registrar->isWindowAvailable()){
            registrar->setCurrCustomer(registrar->dequeue());
            registrar->assignCustomerToWindow();
            cout << "R Assigned: " << registrar->getCurrCustomer()->getRegistrarTime() << ", " << registrar->getCurrCustomer()->getCashierTime() << ", " << registrar->getCurrCustomer()->getFinancialAidTime() << endl;
        }else{
            registrar->getCurrCustomer()->setRegistrarTime((registrar->getCurrCustomer()->getRegistrarTime()) - 1);
            cout << "R new time: " << registrar->getCurrCustomer()->getRegistrarTime() << endl;
            if(registrar->getCurrCustomer()->getRegistrarTime() == 0 && !registrar->isEmpty()){
                registrar->finished(0);
                registrar->setCurrCustomer(registrar->dequeue());
                registrar->assignCustomerToWindow();
                cout << "R Assigned: " << registrar->getCurrCustomer()->getRegistrarTime() << ", " << registrar->getCurrCustomer()->getCashierTime() << ", " << registrar->getCurrCustomer()->getFinancialAidTime() << endl;
            }
        }

        //CASHIER
        if(cashier->isWindowAvailable()){
            cashier->setCurrCustomer(cashier->dequeue());
            cashier->assignCustomerToWindow();
            cout << "C Assigned: " << cashier->getCurrCustomer()->getRegistrarTime() << ", " << cashier->getCurrCustomer()->getCashierTime() << ", " << cashier->getCurrCustomer()->getFinancialAidTime() << endl;
        }else{
            cashier->getCurrCustomer()->setCashierTime((cashier->getCurrCustomer()->getCashierTime()) - 1);
            cout << "C new time: " << cashier->getCurrCustomer()->getCashierTime() << endl;
            if(cashier->getCurrCustomer()->getCashierTime() == 0 && !cashier->isEmpty()){
                cashier->finished(0);
                cashier->setCurrCustomer(cashier->dequeue());
                cashier->assignCustomerToWindow();
                cout << "C Assigned: " << cashier->getCurrCustomer()->getRegistrarTime() << ", " << cashier->getCurrCustomer()->getCashierTime() << ", " << cashier->getCurrCustomer()->getFinancialAidTime() << endl;
            }
        }

        //FINAID
        if(financialAid->isWindowAvailable()){
            financialAid->setCurrCustomer(financialAid->dequeue());
            financialAid->assignCustomerToWindow();
            cout << "F Assigned: " << financialAid->getCurrCustomer()->getRegistrarTime() << ", " << financialAid->getCurrCustomer()->getCashierTime() << ", " << financialAid->getCurrCustomer()->getFinancialAidTime() << endl;
        }else{
            financialAid->getCurrCustomer()->setFinancialAidTime((financialAid->getCurrCustomer()->getFinancialAidTime()) - 1);
            cout << "F new time: " << financialAid->getCurrCustomer()->getFinancialAidTime() << endl;
            if(financialAid->getCurrCustomer()->getFinancialAidTime() == 0 && !financialAid->isEmpty()){
                financialAid->finished(0);
                financialAid->setCurrCustomer(financialAid->dequeue());
                financialAid->assignCustomerToWindow();
                cout << "F Assigned: " << financialAid->getCurrCustomer()->getRegistrarTime() << ", " << financialAid->getCurrCustomer()->getCashierTime() << ", " << financialAid->getCurrCustomer()->getFinancialAidTime() << endl;
            }
        }
        if(registrar->isEmpty() && cashier->isEmpty() && financialAid->isEmpty() && registrar->getCurrCustomer()->getRegistrarTime() == 0 && cashier->getCurrCustomer()->getCashierTime() == 0 && financialAid->getCurrCustomer()->getFinancialAidTime() == 0){
                gameOver = true;
            }
    }
}




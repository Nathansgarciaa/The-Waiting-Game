#include "ListQueue.h"
#include "Customer.h"
#include "Window.h"
#include "ServiceCenter.h"
#include "Office.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv){

    /*Office* office = new Office(1);
    Customer* customer1 = new Customer(1, 5, 1, 2, "RCF");
    Customer* customer2 = new Customer(1, 1, 2, 5, "FRC");
    Customer* customer3 = new Customer(1, 2, 5, 1, "CFR");
    Customer* tempCustomer = new Customer();
    Window* wind = new Window();*/
    ServiceCenter* scc = new ServiceCenter();

    try{
        string filename = "input.txt";
        scc->processFile(filename);
        scc->processDay();

        //scc->printStatistics();


        /*office->addCustomer(customer1);
        office->addCustomer(customer2);
        office->addCustomer(customer3);
        cout << "Customer 1 times: " << customer2->getRegistrarTime() << ", " << customer2->getCashierTime() << ", " << customer2->getFinancialAidTime() << endl;
        cout << "is Window free: " << office->isWindowAvailable() << endl;
        office->assignCustomerToWindow();
        cout << "is Window free: " << office->isWindowAvailable() << endl;
        /*cout << "temp customer times: " << tempCustomer->getRegistrarTime() << ", " << tempCustomer->getCashierTime() << ", " << tempCustomer->getFinancialAidTime() << endl;
        cout << "Window Occupied: " << wind->isOccupied() << endl;
        wind->occupy(office.dequeue());
        cout << "Window Occupied: " << wind->isOccupied() << endl;*/



        //cout << "SIZE: " << dll->getSize() << endl;
    }
    catch(runtime_error &excpt){
        cerr << excpt.what() << endl;
    }
    delete scc;
    return 0;
}
#include "products/Product.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

// Default Constructor
Product::Product() {
    id = 0;
    price = 0;
    unit = 0;
    qty = 0;
}

// Constructor with paramter
Product::Product(int id, string name, string code,
                 double price, int unit, int qty) {
    this->id = id;
    this->name = name;
    this->code = code;
    this->price = price;
    this->unit = unit;
    this->qty = qty;
}

// INPUT 
void Product::input() {
    cout << "Input ID    : ";
    cin >> id;

    cout << "Input Name  : ";
    cin.ignore();
    getline(cin, name);

    cout << "Input Code  : ";
    cin >> code;

    cout << "Input Price : ";
    cin >> price;

    cout << "Input Unit  : ";
    cin >> unit;

    cout << "Input Qty   : ";
    cin >> qty;
}
 // header
    void Product::displayHeader() {
    cout<<string(100, '=')<<endl;;
    cout << left
         << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(20) << "Code"
         << setw(10) << "Price"
         << setw(10) << "Qty"
         << setw(20) << "Total Stock"
         << setw(10) << "Total Amount"
         << endl;
        cout<<string(100, '=')<<endl;
}
//  OUTPUT 
void Product::output() const {
    cout<<string(100, '-')<<endl;
    cout << left
         << setw(10) << id
         << setw(20) << name
         << setw(20) << code
         << setw(10) << price <<fixed<<setprecision(2) << " $"
         << setw(10) << qty 
         << setw(20) << totalStock() 
         << setw(10) << totalAmount() <<fixed<<setprecision(2) << " $"
         << endl;
         cout<<string(100, '-')<<endl;
}
// Setter 
void Product::setId(int id){this->id = id;}
void Product::setName(const string& name){this->name = name;}
void Product::setCode(const string& code){this->code = code;}
void Product::setPrice(double price){this->price = price;}
void Product::setQty(int qty){this->qty = qty;}

// GETTERS 
int Product::getId() const { return id; }

string Product::getName() const { return name; }

string Product::getCode() const { return code; }

double Product::getPrice() const { return price; }

int Product::getUnit() const { return unit; }

int Product::getQty() const { return qty; }

// Calcutation total stock 
double Product::totalStock() const {
    return unit * qty;
}

double Product::totalAmount() const {
    return price * qty;
}


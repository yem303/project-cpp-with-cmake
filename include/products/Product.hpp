#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
using namespace std;
class Product {
private:
    int id;
    string name;
    string code;
    double price;
    int unit;
    int qty;

public:
    Product();
    Product(int id, string name, string code,
            double price, int unit, int qty);

    void input();
    void output() const;

    void setId(int id);
    void setName(const string& name);
    void setCode(const string& code);
    void setPrice(double price);
    void setUnit(int unit);
    void setQty(int qty);

    int getId() const;
    string getName() const;
    string getCode() const;   
    double getPrice() const;
    int getUnit() const;           
    int getQty() const;

    double totalStock() const;
    double totalAmount() const;
};

#endif
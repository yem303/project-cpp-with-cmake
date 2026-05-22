#include "products/ProductManager.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <xlnt/xlnt.hpp>
#include <tabulate/table.hpp>
#include "products/Product.hpp"

using namespace std;
using namespace xlnt;
using namespace tabulate;

// ================= LOAD new data =================
void ProductManager::loadFromExcel(string filename, vector<Product> products) {
    productList.clear();
    // ifstream f(filename);
    // if (!f.good()) return;
    workbook wb;
    wb.load(filename);

    auto ws = wb.active_sheet();
    int rows = ws.highest_row(); 

    for (int i = 2; i <= rows; i++) {
        int id = ws.cell("A" + to_string(i)).value<int>();
        string name = ws.cell("B" + to_string(i)).to_string();
        string code = ws.cell("C" + to_string(i)).to_string();
        double price = ws.cell("D" + to_string(i)).value<double>();
        int unit = ws.cell("E" + to_string(i)).value<int>();
        int qty = ws.cell("F" + to_string(i)).value<int>();

        productList.push_back(Product(id, name, code, price, unit, qty));
    }
}

// ----------------- Write products to store in file excel -----------------------

void ProductManager::writeProductToexcel(string filename, vector<Product> products) {
    workbook wb;
    auto ws = wb.active_sheet();

    ws.cell("A1").value("ID");
    ws.cell("B1").value("Name");
    ws.cell("C1").value("Code");
    ws.cell("D1").value("Price");
    ws.cell("E1").value("Unit");
    ws.cell("F1").value("Qty");
    ws.cell("G1").value("Total Stock");
    ws.cell("H1").value("Total Amount");

    int row = 2;

    for (auto &Product : products) {
        ws.cell("A" + to_string(row)).value(Product.getId());
        ws.cell("B" + to_string(row)).value(Product.getName());
        ws.cell("C" + to_string(row)).value(Product.getCode());
        ws.cell("D" + to_string(row)).value(Product.getPrice());
        ws.cell("E" + to_string(row)).value(Product.getUnit());
        ws.cell("F" + to_string(row)).value(Product.getQty());
        ws.cell("G" + to_string(row)).value(Product.totalStock());
        ws.cell("H" + to_string(row)).value(Product.totalAmount());
        row++;
    }

    wb.save(filename);
}
// Add product stock manager
void ProductManager::addProduct() {
    
    Product newProduct;
    newProduct.input();
    productList.push_back(newProduct);
    writeProductToexcel("products.xlsx", productList);
    cout << "✅ Product added successfully!\n";
}
// show all products stock manager
void ProductManager::showProducts() {
    Table table;
    table.add_row({"ID","Name","Code","Price","Unit","Qty","Total Stock", "Total Amount"});

    for (auto &p : productList) {
        table.add_row({
            to_string(p.getId()),
            p.getName(),
            p.getCode(),
            to_string(p.getPrice()),
            to_string(p.getUnit()),
            to_string(p.getQty()),
            to_string(p.totalStock()),
            to_string(p.totalAmount())
        });
    }

    cout << table << endl;
}
// search products
void ProductManager::searchProduct() {
    int productId;
    cout << "Enter product ID to search : ";
    cin >> productId;

    auto it_if = find_if(productList.begin(), productList.end(),
        [&](Product &obj) {
            return obj.getId() == productId;
        });

    if (it_if != productList.end()) {
        Product::displayHeader();
        it_if->output();
        cout<<"Search has found"<<endl;
    } else {
        cout << "❌ Search has not found"<<endl;;
    }
}
// update products
void ProductManager::updateProduct() {
    int productId;
    cout << "Enter product ID to update : ";
    cin >> productId;

    auto it_if = find_if(productList.begin(), productList.end(),
        [&](Product &obj) {
            return obj.getId() == productId;
        });

    if (it_if != productList.end()) {
        it_if->input();
        writeProductToexcel("products.xlsx", productList);
        cout << "✅ Updated successfully!"<<endl;;
    } else {
        cout << "❌ Update is not successfully!"<<endl;
    }
}
// Delete products
void ProductManager::deleteProduct() {

    int productId;

    cout << "🗑️ Enter product id to delete: ";
    cin >> productId;

    auto it_if = find_if(productList.begin(),
                         productList.end(),

        [&](Product &obj) {
            return obj.getId() == productId;
        });

    if (it_if != productList.end()) {

        productList.erase(it_if);

        writeProductToexcel("products.xlsx", productList);

        cout << "✅ Deleted successfully!\n";

    } else {

        cout << "❌ Product not found!\n";
    }
}
// Sort products order
void ProductManager::sortProducts() {
    sort(productList.begin(), productList.end(),
        [](Product &objA, Product &objB) {
            return objA.getId() < objB.getId();
        });
    showProducts();
    writeProductToexcel("products.xlsx", productList);
    cout << "✅ Sorted successfully\n";
}
// Stock in
void ProductManager::stockIn(){
    int id,quantity;
    cout<<"Enter ID : ";
    cin>>id;
    cout<<"Enter qty : ";
    cin>>quantity;

    for(auto& product : productList){
        if(product.getId() == id){
            product.stockIn(quantity);
            writeProductToexcel("products.xlsx", productList);
            cout<<"✅ Stock in add successfully."<<endl;
            return;
        }
        cout<<"❌ Stock in not found!"<<endl;
    }
}

// Stock out
void ProductManager::stockOut() {
    int id, quantity;

    cout << "Enter ID : ";
    cin >> id;

    cout << "Enter qty : ";
    cin >> quantity;

    for (auto& product : productList) {

        if (product.getId() == id) {

            if (product.stockOut(quantity)) {
                writeProductToexcel("products.xlsx", productList);
                cout << "Stock is out." <<endl;
            } else {
                cout << "Not enough stock." <<endl;
            }

            return;
        }
    }

    cout << "❌ Stock not found!" <<endl;
}

void ProductManager::stockAlert() {


    Product::displayHeader();

 
    for (const auto& product : productList) {

        string status;

        if (product.getQty() <= 0) {

            status = "❌ Out of Stock";

        } else if (product.getQty() <= 10) {

            status = "⚠️ Low Stock";

        } else {

            status = "✅ In Stock";
        }
        product.output(status);
    }
}
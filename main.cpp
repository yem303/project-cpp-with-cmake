#include<iostream> 
#include <tabulate/table.hpp>
#include <xlnt/xlnt.hpp>
#include "auth/Auth.hpp"
#include "auth/Admin.hpp"
#include "auth/Staff.hpp"
#include "auth/User.hpp"
#include <vector>
#include <filesystem>

using namespace std;
using namespace tabulate;
namespace fs = std::filesystem;

// ---------------- PRODUCT CLASS ----------------
class Product {
private:
    int id;
    string name;
    double price;
    int qty;
    int stock;

public:
    Product(int id, string name, double price, int qty, int stock) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->qty = qty;
        this->stock = stock;
    }

    int getId(){ return id; }
    string getName(){ return name; }
    double getPrice(){ return price; }
    int getQty(){ return qty; }
    int getStock(){ return stock; }
};

// ---------------- MENU ----------------
void printMenu(vector<string> items){
    Table table;
    table.add_row({"NO", "Menu"});

    for(int i = 0; i < items.size(); i++){
        table.add_row({to_string(i+1), items[i]});
    }

    table[0].format().font_style({FontStyle::bold});
    cout << table << endl;
}

// ---------------- TABLE ----------------
void printProductTable(vector<Product> products){
    Table table;
    table.add_row({"ID", "Name", "Qty", "Price", "Stock"});

    for (auto p : products){
        table.add_row({
            to_string(p.getId()),
            p.getName(),
            to_string(p.getQty()),
            to_string(p.getPrice()),
            to_string(p.getStock())
        });
    }

    cout << table << endl;
}

// ---------------- WRITE EXCEL ----------------
void writeProductsToExcel(string filename, vector<Product> products){

    fs::create_directories("data");

    xlnt::workbook wb;
    auto ws = wb.active_sheet();

    ws.title("Products");

    ws.cell("A1").value("ID");
    ws.cell("B1").value("Name");
    ws.cell("C1").value("Price");
    ws.cell("D1").value("Qty");
    ws.cell("E1").value("Stock");

    int row = 2;

    for(auto p : products){
        ws.cell("A" + to_string(row)).value(p.getId());
        ws.cell("B" + to_string(row)).value(p.getName());
        ws.cell("C" + to_string(row)).value(p.getPrice());
        ws.cell("D" + to_string(row)).value(p.getQty());
        ws.cell("E" + to_string(row)).value(p.getStock());
        row++;
    }

    try {
        wb.save(filename);
        cout << "[Saved] products.xlsx updated successfully!\n";
    } catch (exception &e){
        cout << "[ERROR saving file]: " << e.what() << endl;
    }
}

// ---------------- READ EXCEL ----------------
vector<Product> readProductsFromExcel(const string& filename){
    vector<Product> products;
    xlnt::workbook wb;

    try{
        wb.load(filename);
    }catch(...){
        cout << "No existing product file, starting new.\n";
        return products;
    }

    auto ws = wb.active_sheet();

    for(auto row : ws.rows(false)){

        if(row[0].to_string() == "ID") continue;

        try{
            int id = stoi(row[0].to_string());
            string name = row[1].to_string();
            double price = stod(row[2].to_string());
            int qty = stoi(row[3].to_string());
            int stock = stoi(row[4].to_string());

            products.push_back(Product(id, name, price, qty, stock));
        } catch (...) {
            // skip broken row
        }
    }

    return products;
}

// ---------------- MAIN ----------------
int main(){

    vector<User*> users;
    users.push_back(new Admin("admin", "123"));
    users.push_back(new Staff("staff", "123"));

    User* loggedInUser = nullptr;
    int choice;

    // -------- AUTH --------
    while(true){
        cout << "\n1. Login\n2. Register\n3. Exit\nChoice: ";
        cin >> choice;

        if(choice == 1){
            string u,p;
            cout<<"Username: "; cin>>u;
            cout<<"Password: "; cin>>p;

            if(login(users,u,p,loggedInUser)){
                cout<<"Login success!\n";
                break;
            }else{
                cout<<"Invalid credentials!\n";
            }
        }
        else if(choice == 2){
            registerUser(users);
        }
        else return 0;
    }

    // -------- PRODUCT SYSTEM --------
    string filename = "data/products.xlsx";
    vector<Product> products = readProductsFromExcel(filename);

    vector<string> menu = {
        "Add Product",
        "Show Products",
        "Delete Product",
        "Exit"
    };

    int option;

    do{
        printMenu(menu);
        cout<<"Choose: ";
        cin>>option;

        switch(option){

            // ADD
            case 1:{
                int id, qty, stock;
                string name;
                double price;

                cout<<"ID: "; cin>>id;
                cin.ignore();

                cout<<"Name: ";
                getline(cin,name);

                cout<<"Price: "; cin>>price;
                cout<<"Qty: "; cin>>qty;
                cout<<"Stock: "; cin>>stock;

                products.push_back(Product(id,name,price,qty,stock));
                writeProductsToExcel(filename,products);
            } break;

            // SHOW
            case 2:
                printProductTable(products);
            break;

            // DELETE
            case 3:{
                int id;
                cout<<"Enter ID to delete: ";
                cin>>id;

                for(int i=0;i<products.size();i++){
                    if(products[i].getId()==id){
                        products.erase(products.begin()+i);
                        break;
                    }
                }

                writeProductsToExcel(filename,products);
            } break;

        }

    }while(option!=4);

    // cleanup
    for(auto u: users) delete u;

    return 0;
}
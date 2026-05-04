#include<iostream>
#include<fstream>
#include <tabulate/table.hpp>
#include <xlnt/xlnt.hpp>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <windows.h> 
using namespace std;
using namespace tabulate;
using namespace xlnt;

// ================= USER CLASS =================
class User {
private:
    string username;
    string password;
    string cpass;
    string role;

public:
    User(){}

    User(string username, string password,string cpass, string role){
        this->username = username;
        this->password = password;
        this->cpass = cpass;
        this->role = role;
    }

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getCpass() {return cpass;}
    string getRole() { return role; }
};

// ================= EXCEL AUTH =================
string userFile = "users.xlsx";

void initUserFile(){
    ifstream file(userFile);
    if(!file.good()){
        workbook wb;
        auto ws = wb.active_sheet();

        ws.title("Users");
        ws.cell("A1").value("Username");
        ws.cell("B1").value("Password");
        ws.cell("C1").value("Confirm Password");
        ws.cell("D1").value("Role");

        wb.save(userFile);
    }
}

vector<User> loadUsers(){
    vector<User> users;

    workbook wb;
    wb.load(userFile);
    auto ws = wb.active_sheet();

    int rows = ws.highest_row();

    for(int i = 2; i <= rows; i++){
        string username = ws.cell("A" + to_string(i)).to_string();
        string password = ws.cell("B" + to_string(i)).to_string();
        string cpass    = ws.cell("C" + to_string(i)).to_string();
        string role     = ws.cell("D" + to_string(i)).to_string();

        users.push_back(User(username, password,cpass, role));
    }

    return users;
}

void saveUser(User user){
    workbook wb;
    wb.load(userFile);
    auto ws = wb.active_sheet();

    int row = ws.highest_row() + 1;

    ws.cell("A" + to_string(row)).value(user.getUsername());
    ws.cell("B" + to_string(row)).value(user.getPassword());
    ws.cell("C" + to_string(row)).value(user.getCpass());
    ws.cell("D" + to_string(row)).value(user.getRole());

    wb.save(userFile);
}

// ================= REGISTER =================
void registerUser(){
    string username, password,cpass, role;

    cout<<"Enter username         : ";
    cin>>username;

    cout<<"Enter password         : ";
    cin>>password;
    cout<<"Enter confirm password : ";
    cin>>cpass;

    // BUG FIX 6: Validate that password and confirm password match
    if(password != cpass){
        cout<<"❌ Passwords do not match!\n";
        return;
    }

    cout<<"Enter role (admin/staff/user): ";
    cin>>role;

    vector<User> users = loadUsers();

    for(auto u:users){
        if(u.getUsername() == username){
            cout<<"❌ Username already exists!\n";
            return;
        }
    }

    saveUser(User(username,password,cpass,role));
    cout<<"✅ Registered successfully!\n";
}

// ================= LOGIN =================
bool loginUser(User &currentUser){
    string username, password;

    cout<<"Enter username : ";
    cin>>username;

    cout<<"Enter password : ";
    cin>>password;

    vector<User> users = loadUsers();

    for(auto u:users){
        if(u.getUsername() == username &&
           u.getPassword() == password){
            currentUser = u;
            cout<<"✅ Login successful!\n";
            return true;
        }
    }

    cout<<"❌ Invalid login!\n";
    return false;
}

// ================= PRODUCT CLASS =================
class Product {
private:
    int id;
    string name;
    string code;
    double price;
    int unit;
    int qty;

public:
    Product(){
        id = 0;
        price = 0;
        qty = 0;
        unit = 0;
    }
    Product(int id, string name, string code, double price, int unit, int qty){
        this->id = id;
        this->name = name;
        this->code = code;
        this->price = price;
        this->unit = unit;
        this->qty = qty;
    }
    // Input products
    void input(){
        cout<<"Input Id    : ";
        cin>>id;

        cout<<"Input Name  : ";
        cin.ignore();
        getline(cin,name);

        cout<<"Input Code  : ";
        cin>>code;

        cout<<"Input Price : ";
        cin>>price;

        cout<<"Input Unit  : ";
        cin>>unit;
        cout<<"Input Qty   : ";
        cin>>qty;
    }

    //  total stock
    double totalStock(){
        return unit * qty;
    }
    // total amount
    double totalAmount(){
        return price * qty;
    }
   
    // output products
    void output() {
        cout<<string(100, '-')<<endl;
        cout << left
            << setw(10) << id
            << setw(20) << name
            << setw(20) << code
            << setw(10) << price
            << setw(10) << qty
            << setw(20) << totalStock()
            << setw(10) << totalAmount()
            << endl;
            cout<<string(100, '-')<<endl;
    }
    // setter (NOTE: these had self-assignment bugs; parameters were missing names)
    void setId(int id)          {this->id = id;}
    void setName(string name)   {this->name = name;}
    void setCode(string code)   {this->code = code;}
    void setPrice(double price) {this->price = price;}
    void setUnit(int unit)      {this->unit = unit;}
    void setQty(int qty)        {this->qty = qty;}

    // getter
    int getId()       { return id; }
    string getName()  { return name; }
    string getCode()  { return code; }
    double getPrice() { return price; }
    int getUnit()     { return unit; }
    int getQty()      { return qty; }

};
 // header
    void displayHeader() {
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

// ================= PRODUCT DISPLAY FROM EXCEL =================
void readProducts(vector<Product>& products){
    Table table;
    table.add_row({"ID","Name","Code","Price","Unit","Qty","Total Stock","Total Amount"});
    for(auto p:products){
        table.add_row({
            to_string(p.getId()),
            p.getName(),
            p.getCode(),
            to_string(p.getPrice()),
            to_string(p.getUnit()),
            to_string(p.getQty()),
            to_string(p.totalStock()),
            "$" + to_string(p.totalAmount())
        });
    }

    cout<<table<<endl;
}

// ================= WRITE PRODUCT TO EXCEL FILE =================
void writeProducts(string filename, const vector<Product>& products){
    workbook wb;

    auto ws = wb.active_sheet();


    // Header
    ws.cell("A1").value("ID");
    ws.cell("B1").value("Name");
    ws.cell("C1").value("Code");
    ws.cell("D1").value("Price");
    ws.cell("E1").value("Unit");
    ws.cell("F1").value("Qty");
    ws.cell("G1").value("Total Stock");
    ws.cell("H1").value("Total Amount");

    int row = 2;

    for(auto p:products){
        ws.cell("A"+to_string(row)).value(p.getId());
        ws.cell("B"+to_string(row)).value(p.getName());
        ws.cell("C"+to_string(row)).value(p.getCode());
        ws.cell("D"+to_string(row)).value(p.getPrice());
        ws.cell("E"+to_string(row)).value(p.getUnit());
        ws.cell("F"+to_string(row)).value(p.getQty());
        ws.cell("G"+to_string(row)).value(p.totalStock());
        ws.cell("H"+to_string(row)).value(p.totalAmount());
        row++;
    }

    wb.save(filename);
}

void loadProducts(string filename, vector<Product>& products){
    // BUG FIX 3: Check if file exists before loading to avoid crash
    ifstream f(filename);
    if(!f.good()) return;

    workbook wb;
    wb.load(filename);
    auto ws = wb.active_sheet();

    int rows = ws.highest_row();

    for(int i = 2; i <= rows; i++){
        int id = ws.cell("A"+to_string(i)).value<int>();
        string name = ws.cell("B"+to_string(i)).to_string();
        string code = ws.cell("C"+to_string(i)).to_string();
        double price = ws.cell("D"+to_string(i)).value<double>();
        int unit = ws.cell("E"+to_string(i)).value<int>();
        int qty = ws.cell("F"+to_string(i)).value<int>();

        products.push_back(Product(id,name,code,price,unit,qty));
    }
}
// ================= MENUS =================
void printMenu(vector<string> items, string title){
    Table table;
    table.add_row({"No", title});

    for(int i=0;i<items.size();i++){
        table.add_row({to_string(i+1), items[i]});
    }

    cout<<table<<endl;
}

// ================= MAIN =================
int main(){
    SetConsoleOutputCP(CP_UTF8);
    initUserFile(); // IMPORTANT
    vector<Product> productList;
 //   loadProducts("products.xlsx", productList); 
    vector<string> authMenu = 
    {
        "Register",
        "Login"
    };
    int choice;
    User currentUser;
    bool loggedIn = false;

    // ===== AUTH LOOP =====
    while (!loggedIn) {
        printMenu(authMenu, "Login System");
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loggedIn = loginUser(currentUser);
            if(loggedIn){
           loadProducts("products.xlsx", productList);
           writeProducts("products.xlsx", productList);
        }
        } else {
            cout << "Invalid!\n";
        }
    }

    cout<<"\nWelcome "<<currentUser.getUsername()
        <<" ("<<currentUser.getRole()<<")\n";

    // ===== PRODUCT SYSTEM =====
    
    vector<string> menu = 
    {
        "Add new products",
        "Show all products",
        "Search Products",
        "Edit products",
        "Delete products",
        "Sort products order",  // BUG FIX 2: Added missing comma (was silently merging with "Exit")
        "Exit"
    };
    int option;

    do{
        printMenu(menu, "Product System");
        cout<<"Choose: ";
        cin>>option;

        switch(option){

            case 1:{
                // Add new product to excel file
                Product newProducts;
                newProducts.input();
                productList.push_back(newProducts);
                writeProducts("products.xlsx", productList);
                cout<<"✅ Added product successfully!\n";
            }
            break;

            case 2:{
                // read products from excel
                readProducts(productList);
            }
                break;
          
            case 3: {
                // Search products
                int productsId;
                cout << "Which product ID do you want to search: ";
                cin >> productsId;
                auto it_if = find_if(productList.begin(), productList.end(), [&](Product &obj) {
                    return obj.getId() == productsId;
                });
                
                if (it_if != productList.end()) {
                    cout << "Search found!" << endl;
                    displayHeader();
                    it_if->output();
                } else {
                    cout << "Search Id has not found, please try again!" << endl;
                }
                break;
            }
            case 4:{
                // Update products
                int productId;
                cout<<"Enter product Id to upate : ";
                cin>>productId;
                auto it_if = find_if(productList.begin(), productList.end(), [&] (Product &obj){
                    return obj.getId() == productId;
                });

                if(it_if != productList.end()){
                    Product result = *it_if;
                    result.input(); // reenter the value
                    *it_if = result; // assign data to productlist
                    writeProducts("products.xlsx", productList); // BUG FIX 5: Save changes to file
                    cout<<"Data update successfully!"<<endl;
                }else{
                    cout<<"Enable to data update, please try again!"<<endl;
                }
                break;
            }
            case 5:{
                // delete product
                int productId;
                cout << "Enter product id to delete : ";

                // BUG FIX 1: Validate numeric input
                if(!(cin >> productId)){
                    cout << "❌ Invalid input! Please enter a numeric ID.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                auto it_if = find_if(productList.begin(), productList.end(), [&](Product &obj){
                    return obj.getId() == productId;
                });

                if(it_if != productList.end()){
                    productList.erase(it_if);
                    writeProducts("products.xlsx", productList); // BUG FIX 2: now writes clean file, no stale rows
                    cout << "✅ Data deleted successfully!" << endl;
                } else {
                    cout << "❌ Product ID not found, please try again!" << endl;
                }
                break;
            }

            case 6: {
                sort(productList.begin(), productList.end(),
                    [](Product &objA, Product &objB) {
                        return objA.getId() < objB.getId();
                    });
                    readProducts(productList);
                    writeProducts("products.xlsx", productList); 
                break;
            }
            case 7:  // BUG FIX 1 & 2: Exit is now correctly case 7
                cout<<"Goodbye!\n";
                break;
            default:
                cout<<"Invalid!\n";
        }

    }while(option != 7); // BUG FIX 1: Was != 4, Exit is option 7

    return 0;
}
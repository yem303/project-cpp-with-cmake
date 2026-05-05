#include "menu/Menu.hpp"
#include "auth/Auth.hpp"
#include "auth/User.hpp"
#include "auth/Admin.hpp"
#include "products/ProductManager.hpp"

#include <iostream>
#include <vector>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

// ================= MENU HELPERS =================
void printMenu(const vector<string>& items, const string& title) {
    Table table;
    table.add_row({"No", title});
    table[0].format()
        .font_color(Color::yellow)
        .font_style({FontStyle::bold});

    for (size_t i = 0; i < items.size(); i++) {
        table.add_row({to_string(i + 1), items[i]});
    }

    cout << table << endl;
}

// ================= AUTH MENU =================
void Menu::authMenu() {

    Auth auth;
    auth.initFile();

    vector<string> authMenuItems = {
        "Register",
        "Login"
    };

    User currentUser;
    int choice = 0;
    bool loggedIn = false;

    while (!loggedIn) {

        printMenu(authMenuItems, "Register Account");

        cout << "Choose: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!"<<endl;;
            continue;
        }

        switch (choice) {
            case 1:
                auth.registerUser();
                break;
            case 2:
                loggedIn = auth.login(currentUser); // must be User&
                break;
            default:
                cout << "Invalid choice!"<<endl;;
        }
    }
    ProductManager manager;
    vector<Product> productList;
    manager.loadFromExcel("products.xlsx", productList);

    if (currentUser.getRole() == "admin") {
        adminMenu(manager);
    } else {
        userMenu(manager, currentUser);
    }

    manager.writeProductToexcel("products.xlsx", productList);
}

// ================= ADMIN MENU =================
void Menu::adminMenu(ProductManager& manager) {

    int option = 0;

    vector<string> adminMenuItems = {
        "Add new products",
        "Show all products",
        "Search Products",
        "Edit products",
        "Delete products",
        "Sort products",
        "Exit"
    };

    do {
        printMenu(adminMenuItems, "Product Management System");

        cout << "Choose: ";
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!"<<endl;
            continue;
        }

        switch (option) {
            case 1: manager.addProduct(); break;
            case 2: manager.showProducts(); break;
            case 3: manager.searchProduct(); break;
            case 4: manager.updateProduct(); break;
            case 5: manager.deleteProduct(); break;
            case 6: manager.sortProducts(); break;
            case 7: cout << "Exiting admin menu...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (option != 7);
}

// ================= USER MENU =================
void Menu::userMenu(ProductManager& manager, const User& user) {

    int option = 0;

    vector<string> userMenuItems = {
        "Show Products",
        "Search Product",
        "Exit"
    };

    cout << "\nWelcome " << user.getUsername()
         << " (" << user.getRole() << ")\n";

    do {
        printMenu(userMenuItems, "User Menu");

        cout << "Choose: ";
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!"<<endl;
            continue;
        }

        switch (option) {
            case 1:
                manager.showProducts();
                break;
            case 2:
                manager.searchProduct();
                break;
            case 3:
                cout << "Exiting user menu.."<<endl;
                break;
            default:
                cout << "Invalid choice!"<<endl;
        }

    } while (option != 3);
}
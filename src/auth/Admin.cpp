#include "auth/Admin.hpp"
#include <iostream>
using namespace std;


Admin::Admin(ProductManager& m) : manager(m) {}

void Admin::menu() {
    int choice;

    do {
        cin >> choice;
        switch(choice) {
            case 1: manager.addProduct(); break;
            case 2: manager.showProducts(); break;
            case 3: manager.searchProduct(); break;
            case 4: manager.updateProduct(); break;
            case 5: manager.deleteProduct(); break;
            case 6: manager.sortProducts(); break;
        }

    } while(choice != 0);
}
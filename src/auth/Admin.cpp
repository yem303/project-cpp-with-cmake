#include <iostream>
#include "auth/Admin.hpp"

using namespace std;

Admin::Admin(string u, string p) : User(u, p) {}

void Admin::showMenu() {
    cout << "===== ADMIN MENU =====" << endl;
    cout << "1. Add Product\n2. Delete Product\n3. View Products\n";
}
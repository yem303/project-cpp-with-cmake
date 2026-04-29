#include <iostream>
#include "auth/Staff.hpp"

using namespace std;

Staff::Staff(string u, string p) : User(u, p) {}

void Staff::showMenu() {
    cout << "===== STAFF MENU =====" << endl;
    cout << "1. View Products\n";
}
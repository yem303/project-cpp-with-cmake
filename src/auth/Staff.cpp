#include <iostream>
#include "auth/Staff.hpp"

Staff::Staff(const std::string& u, const std::string& p)
    : User(u, p) {}

void Staff::showMenu() {
    std::cout << "===== STAFF MENU =====" << std::endl;
    std::cout << "1. View Products\n";
}
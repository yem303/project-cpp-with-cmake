#include <iostream>
#include "auth/Admin.hpp"

Admin::Admin(const std::string& u, const std::string& p)
    : User(u, p) {}

void Admin::showMenu() {
    std::cout << "===== ADMIN MENU =====" << std::endl;
    std::cout << "1. Add Product\n2. Delete Product\n3. View Products\n";
}
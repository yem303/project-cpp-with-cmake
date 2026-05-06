#pragma once

#include <string>
#include <vector>
#include "auth/User.hpp"
#include "products/ProductManager.hpp"

class Menu {
public:
    void loadingText();
    void showMainMenu();
    void authMenu();
    void adminMenu(ProductManager& manager);
    void userMenu(ProductManager& manager, const User& user);

private:
    void printMenu(const std::vector<std::string>& items, const std::string& title);
};
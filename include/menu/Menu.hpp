#ifndef MENU_HPP
#define MENU_HPP

#include "../auth/User.hpp"
#include "../products/ProductManager.hpp"

class Menu {
public:
    void authMenu();
    void adminMenu(ProductManager& manager);
    void userMenu(ProductManager& manager, const User& user);
};

#endif
#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "../products/ProductManager.hpp"

class Admin {
private:
    ProductManager& manager;

public:
    Admin(ProductManager& m);

    void menu(); // full control menu
};

#endif

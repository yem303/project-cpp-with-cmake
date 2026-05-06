#ifndef PRODUCT_MANAGER_HPP
#define PRODUCT_MANAGER_HPP

#include <vector>
#include <string>
#include "Product.hpp"

class ProductManager {
private:
    std::vector<Product> productList;

public:
    void loadFromExcel(std::string file, vector<Product> products);
    void writeProductToexcel(std::string file, vector<Product> products);
    void addProduct();
    void showProducts();
    void searchProduct();
    void updateProduct();
    void deleteProduct();
    void sortProducts();
};

#endif
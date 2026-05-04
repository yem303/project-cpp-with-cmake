#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"
#include <string>

class Admin : public User {
public:
    Admin(const std::string& u, const std::string& p);
    void showMenu() override;
};

#endif
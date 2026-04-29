#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "User.hpp"

class Admin : public User {
public:
    Admin(string u, string p);
    void showMenu() override;
};

#endif
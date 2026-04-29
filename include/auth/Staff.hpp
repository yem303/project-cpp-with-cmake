#ifndef STAFF_HPP
#define STAFF_HPP

#include "User.hpp"

class Staff : public User {
public:
    Staff(string u, string p);
    void showMenu() override;
};

#endif
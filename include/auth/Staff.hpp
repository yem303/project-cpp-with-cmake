#ifndef STAFF_HPP
#define STAFF_HPP

#include "User.hpp"
#include <string>

class Staff : public User {
public:
    Staff(const std::string& u, const std::string& p);
    void showMenu() override;
};

#endif
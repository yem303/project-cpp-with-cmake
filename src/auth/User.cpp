#include "auth/User.hpp"

// Constructor (better style: initializer list)
User::User(std::string u, std::string p)
    : username(u), password(p) {}

// Getters
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

// Destructor
User::~User() {}
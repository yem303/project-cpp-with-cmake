#include "auth/User.hpp"

// Defualt Construcroe
User::User() : username(""), password(""), cpass(""), role("") {}

// Constructor with parameter
User::User(const std::string& u, const std::string& p, const std::string& cp, const std::string& r)
    : username(u), password(p), cpass(cp), role(r) {}

// Getter
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getCpass() const { return cpass; }
std::string User::getRole() const { return role; }


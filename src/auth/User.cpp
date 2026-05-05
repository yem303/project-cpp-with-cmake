#include "auth/User.hpp"

User::User() : username(""), password(""), cpass(""), role("") {}

User::User(const std::string& u, const std::string& p, const std::string& cp, const std::string& r)
    : username(u), password(p), cpass(cp), role(r) {}

std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getCpass() const { return cpass; }
std::string User::getRole() const { return role; }
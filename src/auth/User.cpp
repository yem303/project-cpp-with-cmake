#include "auth/User.hpp"

User::User(string u, string p) {
    username = u;
    password = p;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

User::~User() {}
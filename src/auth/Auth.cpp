#include <iostream>
#include <vector>
#include "auth/Auth.hpp"
#include "auth/Admin.hpp"
#include "auth/Staff.hpp"

// ---------------- LOGIN ----------------
bool login(const std::vector<User*>& users,
           const std::string& username,
           const std::string& password,
           User*& loggedInUser)
{
    for (const auto& user : users) {
        if (user->getUsername() == username &&
            user->getPassword() == password)
        {
            loggedInUser = user;
            return true;
        }
    }
    return false;
}


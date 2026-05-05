#ifndef AUTH_HPP
#define AUTH_HPP

#include <vector>
#include <string>
#include "User.hpp"

class Auth {
private:
    std::string userFile = "users.xlsx";

public:
    void initFile();

    std::vector<User> loadUsers();
    void saveUser(const User& user);  

    void registerUser();
    bool login(User &currentUser);
};

#endif
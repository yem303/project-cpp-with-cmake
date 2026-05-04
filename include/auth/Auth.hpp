#include <iostream>
#include <vector>
#include <string>
#include "User.hpp"

using namespace std;

class AuthService {
private:
    string username;
    string password;
    string role;

public:
    AuthService(string username, string password, string role) {
        this->username = username;
        this->password = password;
        this->role = role;
    }

    // ✅ setters with parameters
    void setUsername(string username){ this->username = username; }
    void setPassword(string password){ this->password = password; }
    void setRole(string role){ this->role = role; }

    // ✅ getters with const
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
};
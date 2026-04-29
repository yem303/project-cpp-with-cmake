#ifndef USER_HPP
#define USER_HPP

#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;

public:
    User(string u, string p);

    string getUsername() const;
    string getPassword() const;

    virtual void showMenu() = 0; // pure virtual

    virtual ~User(); // important for polymorphism
};

#endif
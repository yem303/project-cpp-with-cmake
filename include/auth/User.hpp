#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
protected:
    std::string username;
    std::string password;

public:
    User(std::string u, std::string p);

    std::string getUsername() const;
    std::string getPassword() const;

    virtual std::string getRole() const = 0; // ✅ ADD THIS (important for your system)

    virtual void showMenu() = 0;

    virtual ~User();
};

#endif
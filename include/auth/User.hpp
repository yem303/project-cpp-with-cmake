#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string cpass;
    std::string role;

public:
    User();  

    User(const std::string& u,
         const std::string& p,
         const std::string& cp,
         const std::string& r);

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getCpass() const;
    std::string getRole() const;
};

#endif
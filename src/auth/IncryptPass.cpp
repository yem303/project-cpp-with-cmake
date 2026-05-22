#include "auth/IncryptPass.hpp"

#include <iostream>
#include <conio.h>

std::string PasswordMask::getPassword() {
    std::string password;
    char ch;

    while ((ch = getch()) != '\r') { // Enter key

        // Handle backspace
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
        }
        else {
            password += ch;
            std::cout << '*';
        }
    }

    std::cout << std::endl;
    return password;
}
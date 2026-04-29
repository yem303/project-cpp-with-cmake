#include <iostream>
#include "auth/Auth.hpp"
#include "auth/Admin.hpp"
#include "auth/Staff.hpp"

using namespace std;

// ---------------- LOGIN ----------------
bool login(const vector<User*>& users,
           const string& username,
           const string& password,
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

// ---------------- REGISTER ----------------
void registerUser(vector<User*>& users)
{
    string username, password;
    int roleChoice;

    cout << "\n=== REGISTER ===\n";
    cout << "Enter username: ";
    cin >> username;

    // check duplicate username
    for (auto user : users) {
        if (user->getUsername() == username) {
            cout << "Username already exists!\n";
            return;
        }
    }

    cout << "Enter password: ";
    cin >> password;

    cout << "Select Role:\n";
    cout << "1. Admin\n";
    cout << "2. Staff\n";
    cout << "Choice: ";
    cin >> roleChoice;

    if (roleChoice == 1) {
        users.push_back(new Admin(username, password));
    } else {
        users.push_back(new Staff(username, password));
    }

    cout << "Register successful!\n";
}
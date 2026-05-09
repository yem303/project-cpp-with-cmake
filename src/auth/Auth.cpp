#include <fstream>
#include <iostream>
#include <vector>
#include "auth/User.hpp"
#include "auth/Auth.hpp"
#include <xlnt/xlnt.hpp>

using namespace std;
using namespace xlnt;

// ================= INIT FILE =================
void Auth::initFile() {
    ifstream file(userFile);

    if (!file.good()) {
        workbook wb;
        auto ws = wb.active_sheet();

        ws.title("Users");
        ws.cell("A1").value("Username");
        ws.cell("B1").value("Password");
        ws.cell("C1").value("Confirm Password");
        ws.cell("D1").value("Role");

        wb.save(userFile);
    }
}

// Load new user
vector<User> Auth::loadUsers() {
    vector<User> users;

    workbook wb;
    wb.load(userFile);
    auto ws = wb.active_sheet();

    int rows = ws.highest_row();

    for (int i = 2; i <= rows; i++) {
        string username = ws.cell("A" + to_string(i)).to_string();
        string password = ws.cell("B" + to_string(i)).to_string();
        string cpass    = ws.cell("C" + to_string(i)).to_string();
        string role     = ws.cell("D" + to_string(i)).to_string();

        users.push_back(User(username, password, cpass, role));
    }

    return users;
}

// save user to excel file
void Auth::saveUser(const User& user) {   
    workbook wb;
    wb.load(userFile);
    auto ws = wb.active_sheet();

    int row = ws.highest_row() + 1;

    ws.cell("A" + to_string(row)).value(user.getUsername());
    ws.cell("B" + to_string(row)).value(user.getPassword());
    ws.cell("C" + to_string(row)).value(user.getCpass());
    ws.cell("D" + to_string(row)).value(user.getRole());

    wb.save(userFile);
}

// Register
void Auth::registerUser() {
    string username, password, cpass, role;

    cout << "\033[33m★ Enter Username:          \033[0m"; cin >> username;
    cout << "\033[33m★ Enter Password:          \033[0m"; cin >> password;
    cout << "\033[33m★ Confirm Password:        \033[0m"; cin >> cpass;

    if (password != cpass) {
        cout << "\033[31m❌ Passwords do not match!\n\033[0m";
        return;
    }

    cout << "\033[33m★ Enter Role (admin/user): \033[0m"; cin >> role;

    if (role != "admin" && role != "user") {
        cout << "\033[31m❌ Invalid role! Must be 'admin' or 'user'.\n\033[0m";
        return;
    }

    // use already has 
    vector<User> users = loadUsers();
    for (auto& u : users) {
        if (u.getUsername() == username) {
            cout << "\033[31m❌ Username already exists!\n\033[0m";
            return;
        }
    }

    saveUser(User(username, password, cpass, role));
    cout << "\033[32m✅ Registered successfully!\n\033[0m";
}

// Login account
bool Auth::login(User& currentUser) {
    string username, password;

    cout << "\033[33m★ Enter Username: \033[0m"; cin >> username;
    cout << "\033[33m★ Enter Password: \033[0m"; cin >> password;

    vector<User> users = loadUsers();
    for (auto& u : users) {
        if (u.getUsername() == username && u.getPassword() == password) {
            currentUser = u;
            return true;  // success message handled by showLoginSuccess() in Menu
        }
    }

    cout << "\033[31m❌ Invalid username or password!\n\033[0m";
    return false;
}
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

// ================= LOAD USERS =================
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

// ================= SAVE USER =================
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

// ================= REGISTER =================
void Auth::registerUser() {
    string username, password, cpass, role;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    cout << "Enter confirm password: ";
    cin >> cpass;

    if (password != cpass) {
        cout << "❌ Passwords do not match!\n";
        return;
    }

    cout << "Enter role (admin/user): ";
    cin >> role;

    vector<User> users = loadUsers();

    for (auto &u : users) {
        if (u.getUsername() == username) {
            cout << "❌ Username already exists!\n";
            return;
        }
    }

    saveUser(User(username, password, cpass, role));
    cout << "✅ Registered successfully!\n";
}

// ================= LOGIN =================
bool Auth::login(User &currentUser) {
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    vector<User> users = loadUsers();

    for (auto &u : users) {
        if (u.getUsername() == username &&
            u.getPassword() == password) {

            currentUser = u;
            cout << "✅ Login successful!\n";
            return true;
        }
    }

    cout << "❌ Invalid login!\n";
    return false;
}
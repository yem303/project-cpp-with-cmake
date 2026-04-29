#ifndef AUTH_HPP
#define AUTH_HPP

#include <vector>
#include <string>
#include "User.hpp"

using namespace std;

// login
bool login(const vector<User*>& users,
           const string& username,
           const string& password,
           User*& loggedInUser);

// register
void registerUser(vector<User*>& users);

#endif
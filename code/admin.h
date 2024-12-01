#ifndef ADMIN_H
#define ADMIN_H

#include <unordered_map>
#include <string>
#include "user.h"

using namespace std;

class Admin {
private:
    unordered_map<string, User>& users;

public:
    Admin(unordered_map<string, User>& users);
    void view_finances() const;
    void block_user(const string& username);
    void recommend_funds(const string& username);
    void add_user(const string& username, const string& password, double salary);
    void delete_user(const string& username);
};

#endif 
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>
#include <string>
#include "user.h"

using namespace std;

class UserManager {
private:
    unordered_map<string, User> users;

public:
    UserManager();
    void load_users();
    void save_users();
    bool login(const string& username, const string& password, User*& loggedInUser);
    void create_user(const string& username, const string& password, double salary);
    unordered_map<string, User>& get_users();
};

#endif 
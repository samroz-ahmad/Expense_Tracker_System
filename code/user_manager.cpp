#include "user_manager.h"
#include <fstream>
using namespace std;

// Constructor loads users from file
UserManager::UserManager() { 
    load_users(); 
}

// Loads users from "users.txt" file and stores them in the users map
void UserManager::load_users() {
    ifstream file("users.txt");
    string username, password;
    double salary;
    while (file >> username >> password >> salary) {
        users[username] = User(username, password, salary);
    }
}

// Saves users to "users.txt" file
void UserManager::save_users() {
    ofstream file("users.txt");
    for (const pair<const string, User>& pair : users) {
        const User& user = pair.second;
        file << user.get_username() << " " << user.get_password() << " " << user.get_salary() << "\n";
    }
}

// Authenticates the user and logs them in if credentials are valid
bool UserManager::login(const string& username, const string& password, User*& loggedInUser) {
    if (users.find(username) != users.end() && users[username].authenticate(password)) {
        loggedInUser = &users[username];
        return true;
    }
    return false;
}

// Creates a new user and saves the updated list
void UserManager::create_user(const string& username, const string& password, double salary) {
    users[username] = User(username, password, salary);
    save_users();
}

// Returns the reference to the users map
unordered_map<string, User>& UserManager::get_users() { return users; }

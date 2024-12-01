#include "admin.h"  
#include <iostream> 

using namespace std;

Admin::Admin(unordered_map<string, User>& users) : users(users) {}  // Constructor initializes the users map reference

void Admin::view_finances() const {  
    for (const pair<const string, User>& pair : users) {  // Iterate through each user in the users map
        const User& user = pair.second;  // Access the User object
        cout << "User: " << user.get_username() << ", Salary: $" << user.get_salary() << ", Total Savings: $" << user.get_savings() << "\n";  // Print user's financial details
    }
}

void Admin::block_user(const string& username) {  
    if (users.find(username) != users.end()) {  // Check if user exists in the users map
        cout << "User " << username << " has been blocked for suspicious activity.\n";  // Inform user has been blocked
        users.erase(username);  // Remove the user from the map
    } else {  
        cout << "User not found.\n";  // Inform if user was not found
    }
}

void Admin::recommend_funds(const string& username) {  
    if (users.find(username) != users.end()) {  // Check if user exists in the users map
        cout << "Admin recommends user " << username << " to add more funds.\n";  // Recommend user to add funds
    } else {  
        cout << "User not found.\n";  // Inform if user was not found
    }
}

void Admin::add_user(const string& username, const string& password, double salary) {  
    users[username] = User(username, password, salary);  // Add new user to the users map
    cout << "User " << username << " added successfully.\n";  // Confirm user was added
}

void Admin::delete_user(const string& username) {  
    if (users.erase(username)) {  // Try to delete user from the map, check if successful
        cout << "User " << username << " deleted successfully.\n";  // Confirm user was deleted
    } else {  
        cout << "User not found.\n";  // Inform if user was not found
    }
}

#include "user.h"
#include <numeric>
#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

User::User(const string& uname, const string& pword, double sal)
    : username(uname), password(pword), salary(sal), target_savings(0), actual_savings(0) {}

// Authenticate user
bool User::authenticate(const std::string& pword) const { return password == pword; }

// Set the user's savings target
void User::set_savings(double target) { target_savings = target; }

// Calculate and return the savings by subtracting total expenses from salary
double User::trackSavings() const {
    return salary - total_expenses();  
}

// Getters for various attributes
string User::get_username() const { return username; }
string User::get_password() const { return password; }
double User::get_salary() const { return salary; }
double User::get_target_savings() const { return target_savings; }
double User::get_savings() const { return trackSavings(); }  // Actual savings is salary minus total expenses

// Add an expense to the user's expenses history
void User::add_expense(double amount) { expenses_history.push_back(amount); }

// Calculate and return the total expenses of the user
double User::total_expenses() const {
    string filename = this->get_username() + "_report.txt";
    ifstream file(filename);
    if (!file){
        cerr << "Error opening file.\n";
        return 0.0; 
    }
    double total_expenses = 0;
    string line;
    while(getline(file, line)){
        if (line.find("Amount: $") != string::npos){
            double amount = stod(line.substr(9));
            total_expenses += amount;
        }
    }
    
    return total_expenses;
}

// Return a reference to the list of all expenses
const vector<double>& User::get_history() const { return expenses_history; }

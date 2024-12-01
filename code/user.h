#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

using namespace std;

class User {
private:
    string username;
    string password;
    double salary;
    double target_savings;
    double actual_savings;
    vector<double> expenses_history;

public:
    User(const string& uname = "", const string& pword = "", double sal = 0);
    bool authenticate(const string& pword) const;
    void set_savings(double target);
    double trackSavings() const;
    string get_username() const;
    double get_salary() const;
    double get_target_savings() const;
    double get_savings() const;
    void add_expense(double amount);
    double total_expenses() const;
    const vector<double>& get_history() const;
    // get password
    string get_password() const;
};


#endif 
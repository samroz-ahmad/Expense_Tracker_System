#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <ctime>

using namespace std;

class Expense {
protected:
    string description;
    double amount;
    string category;
    time_t date;

public:
    Expense(const string& desc, double amt, const string& cat, time_t expenseDate);
    virtual void print_expense_details() const;
    virtual ~Expense() = default;

    // Getter methods
    string get_description() const;   
    string get_category() const;      
    time_t get_date() const;          
    double get_amount() const;        
};

#endif 

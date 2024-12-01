#include "expense.h"
#include <iostream>

using namespace std;

Expense::Expense(const string& d, double a, const string& c, time_t d_e)
    : description(d), amount(a), category(c), date(d_e) {}

void Expense::print_expense_details() const {
    cout << "Expense: " << description << ", Amount: $" << amount << ", Category: " << category << "\n";
}

// Getter for description
string Expense::get_description() const {
    return description;
}

// Getter for category
string Expense::get_category() const {
    return category;
}

// Getter for date
time_t Expense::get_date() const {
    return date;
}

// Getter for amount
double Expense::get_amount() const {
    return amount;
}

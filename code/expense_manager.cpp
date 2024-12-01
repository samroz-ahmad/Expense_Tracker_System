#include "expense_manager.h"
#include <fstream>
#include <iomanip>
#include <ctime>
#include <iostream>

using namespace std;

void ExpenseManager::add_expense(Expense* expense) {
    expenses.push_back(expense);
}

void ExpenseManager::generate_report(const User* current_user) {
    // Use the logged-in user's username to create a personalized report file
    string filename = current_user->get_username() + "_report.txt";
    
    // Open the file in append mode to update the report instead of overwriting it
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Error opening file.\n";
        return;
    }

    
    for (const Expense* expense : expenses) {
        // Formatting date from time_t to a readable string
        time_t expenseDate = expense->get_date();
        char dateStr[20];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d %H:%M:%S", localtime(&expenseDate));
        
        // Write the details of each expense
        file << "Date: " << dateStr << "\n";
        file << "Description: " << expense->get_description() << "\n";
        file << "Amount: $" << fixed << setprecision(2) << expense->get_amount() << "\n";
        file << "Category: " << expense->get_category() << "\n";
        file << "---------------------------------\n";
    }
    // clear expenses
    expenses.clear();


    cout << "Report created/updated to " << filename << ".\n";
}

double ExpenseManager::get_totalexpenses() const {
    double total = 0;
    for (const Expense* expense : expenses) {
        total += expense->get_amount();
    }
    return total;
}

ExpenseManager::~ExpenseManager() {
    for (Expense* expense : expenses) {
        delete expense;
    }
}

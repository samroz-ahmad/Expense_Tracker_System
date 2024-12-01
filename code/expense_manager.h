#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include <vector>
#include "expense.h"
#include "user.h"

class ExpenseManager {
private:
    std::vector<Expense*> expenses;

public:
    void add_expense(Expense* expense);
    void generate_report(const User* current_user);  
    double get_totalexpenses() const;
    ~ExpenseManager();
};

#endif 
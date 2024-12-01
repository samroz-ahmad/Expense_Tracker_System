#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "user.h"
#include "user_manager.h"
#include "expense_manager.h"
#include "admin.h"

using namespace std;

class MainMenu {
    private:
        User* current_user;
        UserManager userManager;
        ExpenseManager expenseManager;
        Admin admin;
        bool running;

    public:
        MainMenu();
        void run();
        bool user_logged_in() const;
        void user_login();
        void create_user();
        void add_expense();
        void generate_report();
        void set_savings();           
        void check_savings();         
        void largest_spending();            
        void admin_menu();
        ~MainMenu();
};

#endif 

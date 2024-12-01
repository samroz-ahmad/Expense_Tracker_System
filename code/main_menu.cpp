#include "main_menu.h"  
#include <iostream>     
#include <algorithm>    
#include <limits>       
#include <fstream>      

using namespace std;

MainMenu::MainMenu() : current_user(nullptr), admin(userManager.get_users()) {}  
// Constructor initializes current_user and Admin with users

MainMenu::~MainMenu(){
    // Destructor to clean up dynamically allocated memory
    delete current_user;
}

void MainMenu::run() {
    // Flag to control the main loop
    bool running = true;

    // Variable to store user input
    int choice;

    // Main menu loop
    while (running) {
        // If no user is logged in, display login options
        if (!user_logged_in()) {
            cout << "1. Log In\n";
            cout << "2. Create New Account\n";
            cout << "3. Admin Access\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            // Clear any input errors
            cin.clear();

            // Ignore extra input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check user's choice for login options
            if (choice == 1) {
                // Call user login function
                user_login();
            } else if (choice == 2) {
                // Call function to create a new user
                create_user();
            } else if (choice == 3) {
                // Call the admin menu
                admin_menu();
            } else if (choice == 4) {
                // Exit the program
                running = false;
            } else {
                // Invalid input handling
                cout << "Invalid selection.\n";
            }

        } else {
            // If a user is logged in, display user options
            cout << "\n1. Add Expense\n";
            cout << "2. Generate Report\n";
            cout << "3. Set Savings Target\n";
            cout << "4. Check Current Saving Status\n";
            cout << "5. Largest Spending\n";
            cout << "6. Log Out\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            // Clear any input errors
            cin.clear();

            // Ignore extra input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Check user's choice for account options
            if (choice == 1) {
                // Call function to add an expense
                add_expense();
            } 
            else if (choice == 2) {
                // Call function to generate a report
                generate_report();
            } 
            else if (choice == 3) {
                // Call function to set a savings target
                set_savings();
            } 
            else if (choice == 4) {
                // Call function to check current savings status
                check_savings();
            } 
            else if (choice == 5) {
                // Call function to check the largest spending
                largest_spending();
            } 
            else if (choice == 6) {
                // Log out the current user
                current_user = nullptr;
            } 
            else if (choice == 7) {
                // Exit the program
                running = false;
            } 
            else {
                // Invalid input handling
                cout << "Invalid selection.\n";
            }

        }
    }
    // Program exit message
    cout << "Program exited successfully.\n";
}

bool MainMenu::user_logged_in() const {
    // Check if a user is logged in by checking if current_user is not null
    return current_user != nullptr;
}

void MainMenu::user_login() {
    // Variables for login credentials and attempt tracking
    string username, password;
    int attempts = 0;
    const int maxAttempts = 3;

    // Loop for login attempts
    while (attempts < maxAttempts) {
        // Prompt user for username and password
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        // Call userManager to attempt login
        if (userManager.login(username, password, current_user)) {
            cout << "Logged in successfully.\n";
            return;
        } else {
            // Handle invalid credentials and remaining attempts
            cout << "Invalid username or password. Attempts left: " << (maxAttempts - attempts - 1) << "\n";
            attempts++;
        }
    }
    // If max attempts reached, inform the user and reset current_user
    cout << "Maximum login attempts reached. Returning to the main menu.\n";
    current_user = nullptr;
}

void MainMenu::create_user() {
    // Variables for new user creation
    string username, password;
    double salary;

    // Prompt for new user details
    cout << "Enter a username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;
    cout << "Enter your monthly salary: ";
    cin >> salary;

    // Call userManager to create the new user
    userManager.create_user(username, password, salary);

    // Inform user of successful account creation
    cout << "Account created successfully. Please log in.\n";
}

void MainMenu::add_expense() {
    // Variables for expense details
    string description, category, amount_str;
    double amount;
    time_t date = time(nullptr);

    // Prompt for expense description
    cout << "Enter a description: ";
    getline(cin, description);

    // Loop to ensure valid amount input
    do {
        cout << "Enter amount: ";
        getline(cin, amount_str);
        try{
            amount = stod(amount_str);  // Convert amount string to double
            break;
        }
        catch(const std::exception& e){
            // Handle invalid input
            cout << "\nEnter a valid number! ";
            continue;
        }
    } while(true);

    // Prompt for expense category
    cout << "Enter the category ('Fixed' or 'Variable'): ";
    getline(cin, category);

    // Call expenseManager to add the new expense
    expenseManager.add_expense(new Expense(description, amount, category, date));
    current_user->add_expense(amount);

    // Inform user of successful expense addition and automatic report generation
    cout << "Expense added successfully!\n";
    cout << "To avoid losing the added expense, your Expense Report has been generated/updated automatically!\n";
    cout << "You can view your report by selecting the file in the project directory.\n";

    // Generate the updated report
    generate_report();
}

void MainMenu::generate_report() {
    // Call expenseManager to generate the report for the current user
    expenseManager.generate_report(current_user);
}

void MainMenu::set_savings() {
    // Variable for savings target
    double target;

    // Prompt for savings target
    cout << "Enter your monthly savings target: ";
    cin >> target;

    // Set the savings target for the current user
    current_user->set_savings(target);

    // Inform user of successful target setting
    cout << "Savings target set to $" << target << ".\n";
}

void MainMenu::check_savings() {
    // Retrieve the current savings and target savings for the user
    double current_savings = current_user->get_savings();
    double target_savings = current_user->get_target_savings();

    // Check if the user has met the savings target
    if (current_savings >= target_savings) {
        cout << "Congratulations! You have reached your savings target of $" << target_savings << ".\n";
    } 
    else {
        // Inform user of the current savings status and remaining amount to reach the target
        cout << "You have saved $" << current_savings << " so far. You need $" << (target_savings - current_savings) << " more to reach your target.\n";
    }
}

void MainMenu::largest_spending() {
    // Create filename for the current user's report
    string filename = current_user->get_username() + "_report.txt";

    // Open the report file
    ifstream file(filename);

    // Handle file opening errors
    if (!file) {
        cerr << "Error opening file.\n";
        return;
    }

    // Variable to track the largest expense
    double largest = -1;
    string line;

    // Read through the file to find the largest recorded expense
    while (getline(file, line)) {
        if (line.find("Amount: $") != string::npos) {
            double amount = stod(line.substr(9));  // Extract amount from the line
            largest = max(largest, amount);  // Track the largest amount
        }
    }

    // If no expenses were recorded, inform the user
    if (largest == -1) {
        cout << "No expenses recorded.\n";
        return;
    }

    // Output the largest expense found
    cout << "The largest expense recorded is: $" << largest << ".\n";
}

void MainMenu::admin_menu() {
    // Variables for admin password
    string admin_password, password;

    // Prompt for admin password
    cout << "Enter admin password: ";
    cin >> admin_password;

    // Set the actual admin password
    password = "admin123";

    // Check if the entered password matches the actual password
    if (admin_password == password) {
        int choice;

        // Admin menu loop
        do {
            // Display admin options
            cout << "1. View All Finances\n";
            cout << "2. Block a User\n";
            cout << "3. Recommend User to Add Funds\n";
            cout << "4. Add User\n";
            cout << "5. Delete User\n";
            cout << "6. Logout and return to menu\n";
            cout << "Enter your choice: ";
            cin >> choice;

            // Handle admin menu options
            switch (choice) {
                case 1: {
                    // View all finances
                    admin.view_finances(); 
                    break;
                }
                case 2: {
                    // Block a user
                    string username;
                    cout << "Enter the username to block: ";
                    cin >> username;
                    admin.block_user(username);
                    break;
                }
                case 3: {
                    // Recommend funds to a user
                    string username;
                    cout << "Enter the username to recommend funds: ";
                    cin >> username;
                    admin.recommend_funds(username);
                    break;
                }
                case 4: {
                    // Add a new user
                    string username, password;
                    double salary;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;
                    cout << "Enter salary: ";
                    cin >> salary;
                    admin.add_user(username, password, salary);
                    break;
                }
                case 5: {
                    // Delete a user
                    string username;
                    cout << "Enter the username to delete: ";
                    cin >> username;
                    admin.delete_user(username);
                    break;
                }
                case 6: {
                    // Logout and return to menu
                    cout << "Logging out and returning to menu.\n";
                    break;
                }
                default:
                    // Handle invalid input
                    cout << "Invalid selection.\n";
            }
        } while (choice != 6);
    } else {
        // Handle invalid admin password
        cout << "Invalid admin password.\n";
    }
}

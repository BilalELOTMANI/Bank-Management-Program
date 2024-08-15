#include "admin.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// Function to display the admin menu
void displayMenu() {
    cout << "Welcome ADMIN" << endl;
    cout << "Choose the following options:" << endl;
    cout << "1. Add account" << endl;
    cout << "2. Delete account" << endl;
    cout << "3. Check all accounts" << endl;
    cout << "4. See passwords of accounts" << endl;
    cout << "5. Edit account" << endl;
    cout << "6. Exit" << endl;
}

// Function to handle adding an account
#include <iostream>
#include <string>
#include <stdexcept> // For exception handling

void handleAddAccount(BST_Tree& t, Hashtable& h) {
    string name, address;
    string accNumberStr, passwordStr, balanceStr;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter address: ";
    cin >> address;

    try {
        cout << "Enter account number (10 digits): ";
        cin >> accNumberStr;
        if (accNumberStr.length() != 10) {
            throw out_of_range("Account number must be exactly 10 digits.");
        }

        cout << "Enter password (4 digits): ";
        cin >> passwordStr;
        if (passwordStr.length() != 4) {
            throw out_of_range("Password must be exactly 4 digits.");
        }

        cout << "Enter balance: ";
        cin >> balanceStr;

        // Attempt to convert strings to numbers
        long long accNumber = stoll(accNumberStr);
        int password = stoi(passwordStr);
        long long balance = stoll(balanceStr);

        // Add the account to the BST
        t.add_Account(name, address, accNumber, password, balance);


        system("cls"); // Use "cls" for clearing console on Windows
        cout << "Account added successfully!" << endl;
    }
    catch (const invalid_argument& e) {
        cerr << "Error: Invalid input. Please enter numeric values only." << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "An unexpected error occurred: " << e.what() << endl;
    }
}


// Function to handle deleting an account
void handleDeleteAccount(BST_Tree& t, Hashtable& h) {
    long long accNumber;

    cout << "Enter account number: ";
    cin >> accNumber;

    t.load_Server(); // Ensure that BST is up-to-date with file
    t.Root = t.delete_Account(t.Root, accNumber);
    h.delete_password(accNumber);  // Update hashtable
    t.update_server(t.Root); // Update the server file

    cout << "Account number and password have been deleted." << endl;
    cout << "Hashtable has been updated." << endl;
}

// Function to handle printing all accounts
void handlePrintAllAccounts(BST_Tree& t) {
    t.load_Server(); // Ensure that BST is up-to-date with file
    t.printoinfo(t.Root);
}

// Function to start the admin operations
void admin(BST_Tree& t, Hashtable& h) {
    int condition = 0;

    while (condition != 6) {
        displayMenu();
        cin >> condition;

        switch (condition) {
        case 1:
            handleAddAccount(t, h);
            break;
        case 2:
            handleDeleteAccount(t, h);
            break;
        case 3:
            handlePrintAllAccounts(t);
            break;
        case 4:
            h.displayPasswords();
            break;
        case 5:
            cout << "Edit account functionality is not implemented yet." << endl;
            break;
        case 6:
            cout << "Exiting..." << endl;
            system("cls");
            break;
        default:
            cout << "Please enter a valid option!" << endl;
            break;
        }
    }
}

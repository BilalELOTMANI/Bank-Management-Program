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
void handleAddAccount(BST_Tree& t, Hashtable& h) {
    string name, address;
    // int accNumber, password, balance;
    string accNumberStr, passwordStr, balanceStr;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter address: ";
    cin >> address;
    cout << "Enter account number: ";
    cin >> accNumberStr;
    cout << "Enter password: ";
    cin >> passwordStr;
    cout << "Enter balance: ";
    cin >> balanceStr;

    t.add_Account(name, address, stol(accNumberStr), stoi(passwordStr), stoi(balanceStr));
    //h.add(stol(accNumberStr), stoi(passwordStr));

    system("cls");
    cout << "Account added successfully !" << endl;
    displayMenu();
}

// Function to handle deleting an account
void handleDeleteAccount(BST_Tree& t, Hashtable& h) {
    int accNumber;

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
void admin() {
    BST_Tree t;
    Hashtable h;
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
            break;
        default:
            cout << "Please enter a valid option!" << endl;
            break;
        }
    }
}

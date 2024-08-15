#include "customer.h"
#include <iostream>
#include <fstream>
using namespace std;

// Function to display the customer menu
void displayCustomerMenu() {
    cout << "Welcome CUSTOMER" << endl;
    cout << "Choose the following options:" << endl;
    cout << "1. See account details" << endl;
    cout << "2. See transaction history" << endl;
    cout << "3. Exit" << endl;
}

// Function to handle viewing account details
void handleViewAccountDetails(BST_Tree& t) {
    long long accountno;
    cout << "Please enter account number: ";
    cin >> accountno;

    // Load the BST from the server file to ensure up-to-date information
    t.load_Server();

    BST_Node* temp = t.search(t.Root, accountno);
    if (temp) {
        cout << "Account Details Are:" << endl << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Address: " << temp->address << endl;
        cout << "Account Number: " << temp->account_number << endl;
        cout << "Password: " << temp->password << endl;
        cout << "Balance: " << temp->balance << endl;
    }
    else {
        cout << "Account not found." << endl;
    }
}

// Function to handle viewing transaction history
void handleViewTransactionHistory() {
    long long accountno;
    cout << "Please enter account number: ";
    cin >> accountno;

    ifstream read("transaction.txt");
    if (!read.is_open()) {
        cout << "Error opening transaction file." << endl;
        return;
    }

    long long line;
    cout << "Transaction History for Account " << accountno << ":" << endl;
    while (read >> line) {
        if (line == accountno) {
            cout << "Account " << accountno << ": ";
            read >> line; // Read the transaction amount
            cout << (line < 0 ? "Withdraw: " : "Deposit: ") << abs(line) << endl;
        }
    }
    read.close();
}

// Function to start the customer operations
void customer() {
    BST_Tree t;
    int condition = 0;

    while (condition != 3) {
        displayCustomerMenu();
        cin >> condition;

        switch (condition) {
        case 1:
            handleViewAccountDetails(t);
            break;
        case 2:
            handleViewTransactionHistory();
            break;
        case 3:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Please enter a valid option!" << endl;
            break;
        }
    }
}
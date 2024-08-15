#include "staff.h"
#include <iostream>
#include <fstream>
using namespace std;

// Function to display the staff menu
void displayStaffMenu() {
    cout << "Welcome STAFF" << endl;
    cout << "Choose the following options:" << endl;
    cout << "1. See transaction history" << endl;
    cout << "2. Transfer" << endl;
    cout << "3. Withdraw" << endl;
    cout << "4. Deposit" << endl;
    cout << "5. Exit" << endl;
}

// Function to handle viewing transaction history
void handleViewTransactionHistory(BST_Tree& t) {
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

// Function to handle transferring money
void handleTransfer(BST_Tree& t) {
    long long senderAccountNo, receiverAccountNo, amount;

    cout << "Please enter sender account number: ";
    cin >> senderAccountNo;
    cout << "Please enter receiver account number: ";
    cin >> receiverAccountNo;
    cout << "Please enter amount: ";
    cin >> amount;

    t.transfer(senderAccountNo, receiverAccountNo, amount);
}

// Function to handle withdrawing money
void handleWithdraw(BST_Tree& t) {
    long long accountNo, amount;

    cout << "Please enter account number: ";
    cin >> accountNo;
    cout << "Please enter amount: ";
    cin >> amount;

    t.withdraw(accountNo, amount);
}

// Function to handle depositing money
void handleDeposit(BST_Tree& t) {
    long long accountNo, amount;

    cout << "Please enter account number: ";
    cin >> accountNo;
    cout << "Please enter amount: ";
    cin >> amount;

    t.deposit(accountNo, amount);
}

// Function to start the staff operations
void staff(BST_Tree& t) {
    int condition = 0;

    while (condition != 5) {
        displayStaffMenu();
        cin >> condition;

        switch (condition) {
        case 1:
            handleViewTransactionHistory(t);
            break;
        case 2:
            handleTransfer(t);
            break;
        case 3:
            handleWithdraw(t);
            break;
        case 4:
            handleDeposit(t);
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Please enter a valid option!" << endl;
            break;
        }
    }
}

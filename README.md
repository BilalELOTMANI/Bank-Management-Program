# Bank Management System

## Overview
This Bank Management System is a console-based application developed in C++. It is designed to manage basic banking operations such as creating and deleting accounts, managing transactions, and viewing account details. The system is divided into three main roles: Admin, Staff, and Customer, each with its own set of functionalities.

## Features

### Admin
- **Add Account:** Create a new account with a unique account number, password, and initial balance.
- **Delete Account:** Remove an existing account and update the system accordingly.
- **Check All Accounts:** Display information for all accounts stored in the system.
- **View Passwords:** Access the passwords of all accounts (for admin use only).

### Staff
- **View Transaction History:** Check the transaction history for a specific account.
- **Transfer Funds:** Transfer funds between two accounts within the system.
- **Withdraw Funds:** Withdraw a specified amount from an account.
- **Deposit Funds:** Deposit a specified amount into an account.

### Customer
- **View Account Details:** Display the details of the customer’s own account.
- **View Transaction History:** View the history of transactions associated with the customer’s account.

## Technology Stack
- **Programming Language:** C++
- **Data Structures:** Binary Search Tree (BST) for managing account data, Hashtable for managing account passwords.
- **File Handling:** Used for loading and saving account and transaction data.


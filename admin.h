#pragma once
#include "BST_Tree.h"
#include "Hashtable.h"

// Function to display the admin menu
void displayMenu();

// Function to handle adding an account
void handleAddAccount(BST_Tree& t, Hashtable& h);

// Function to handle deleting an account
void handleDeleteAccount(BST_Tree& t, Hashtable& h);

// Function to handle printing all accounts
void handlePrintAllAccounts(BST_Tree& t);

// Function to start the admin operations
void admin();
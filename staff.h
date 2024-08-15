#pragma once
#include "BST_Tree.h"
#include "Hashtable.h"

// Function to display the staff menu
void displayStaffMenu();

// Function to handle viewing transaction history
void handleViewTransactionHistory(BST_Tree& t);

// Function to handle transferring money
void handleTransfer(BST_Tree& t);

// Function to handle withdrawing money
void handleWithdraw(BST_Tree& t);

// Function to handle depositing money
void handleDeposit(BST_Tree& t);

// Function to start the staff operations
void staff();

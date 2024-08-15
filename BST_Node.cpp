#include "BST_Node.h"

// Default Constructor
BST_Node::BST_Node() {
    left = nullptr;
    right = nullptr;
    name = "";
    address = "";
    account_number = 0;
    password = 0;
    balance = 0;
}

// Parameterized Constructor
BST_Node::BST_Node(std::string name, std::string address, long accountno, int password, int balance) {
    left = nullptr;
    right = nullptr;
    this->name = name;
    this->address = address;
    this->account_number = accountno;
    this->password = password;
    this->balance = balance;
}

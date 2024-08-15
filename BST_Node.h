#pragma once
# include <iostream>
using namespace std;
# include <vector>
# include <fstream>
# include <string>
class BST_Node 
{
public:
	BST_Node * left;
	BST_Node * right;
	string name;
	string address;
	int account_number;
	int password;
	int balance;

	BST_Node();
	BST_Node(string, string, int, int, int);
	
};

// To delete because i will switch to array based hashtable
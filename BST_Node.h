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
	long long account_number;
	int password;
	long long balance;

	BST_Node();
	BST_Node(string, string, long long, int, long long);
	
};

// To delete because i will switch to array based hashtable
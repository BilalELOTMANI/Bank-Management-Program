#pragma once
# include "BST_Node.h"
# include "Hashtable.h"
# include <stdio.h>
class BST_Tree
{
	vector <long long> v;
	
public:

	BST_Tree();

	Hashtable h;

	BST_Node *Root;

	void add_Account(string, string, long long, int, long long);

	long long findMax(BST_Node*);

	BST_Node* delete_Account(BST_Node *, long long);

	void load_Server();

	void insertIntoBST(BST_Node*& root, BST_Node* temp);

	void update_server(BST_Node*);

	void withdraw(long long, long long);

	void deposit(long long, long long);

	void editaccount_byAdmin();

	void transfer(long long, long long, long long);

	void transaction_history();
	
	BST_Node* search(BST_Node*, long long);

	void printoinfo(BST_Node*);
};


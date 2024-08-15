#pragma once
# include "BST_Node.h"
# include "Hashtable.h"
# include <stdio.h>
class BST_Tree
{
	vector <int> v;
	
public:

	BST_Tree();

	Hashtable h;

	BST_Node *Root;

	void add_Account(string, string, int, int, int);

	int findMax(BST_Node*);

	BST_Node* delete_Account(BST_Node *, int);

	void load_Server();

	void insertIntoBST(BST_Node*& root, BST_Node* temp);

	void update_server(BST_Node*);

	void withdraw(int,int);

	void deposit(int,int);

	void editaccount_byAdmin();

	void transfer(int,int,int);

	void transaction_history();
	
	BST_Node* search(BST_Node*,int);

	void printoinfo(BST_Node*);
};


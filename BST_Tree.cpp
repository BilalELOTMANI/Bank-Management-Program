# include "BST_Tree.h"
# include "Hashtable.h"
BST_Tree:: BST_Tree() {

}
void BST_Tree::add_Account(string name, string address, int accountno, int password, int balance)
{
	h.add(accountno, password);
	ofstream write;
	write.open("server.txt", ios::app);
	write << name << endl << address << endl << accountno << endl << password << endl << balance << endl;
	write.close();

	BST_Node * temp = new BST_Node(name, address, accountno, password, balance);

	BST_Node * current = Root;
	if (Root == nullptr)
	{
		Root = temp;
	}
	else
	{
		while (true)
		{
			if (accountno < current->account_number)
			{
				if (current->left == nullptr)
				{
					current->left = temp;
					break;
				}
				current = current->left;
			}

			if (accountno > current->account_number)
			{
				if (current->right == nullptr)
				{
					current->right = temp;
					break;
				}
				current = current->right;
			}
		}
	}
}


BST_Node* BST_Tree:: delete_Account(BST_Node * root, int accountno)
{
	
	if (root == nullptr)
		cout << "it seems that Tree is empty OR You have entered wrong data" << endl;
	else if (accountno < root->account_number)
		root->left = delete_Account(root->left, accountno);
	else if (accountno > Root->account_number)
		root->right = delete_Account(root->right, accountno);
	else
	{
		if (root->left && root->right)
		{
			int maxValue = findMax(root->left);
			root->account_number = v.back();
			root->left = delete_Account(root->left, root->account_number);
		}
		else
		{
			BST_Node* temp = root;
			if (root->left == nullptr)
				root = root->right;
			else if (root->right == nullptr)
				root = root->left;
			delete temp;
		}
	}
	return(root);
}

/*
void BST_Tree::withdraw(int accountno,int amount)
{
	load_Server();
	BST_Node *temp = search(Root, accountno);
	temp->balance = temp->balance - amount;
	vector <int> data;
	ifstream read;
	read.open("transaction.txt", ios::app);
	int line = 0;
	while (!read.eof())
	{
		read >> line;
		if (line == accountno)
		{
			data.push_back(line);
			line = (amount*-1);
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	ofstream write;
	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i]<<endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");
	
	update_server(Root);
}
*/

void BST_Tree::withdraw(int accountno, int amount)
{
	// Load the BST from the server file
	load_Server();

	// Search for the account in the BST
	BST_Node* temp = search(Root, accountno);
	if (temp == nullptr) {
		cout << "Account not found." << endl;
		return;
	}

	// Check if there are sufficient funds
	if (temp->balance < amount) {
		cout << "Insufficient funds." << endl;
		return;
	}

	// Update the account balance
	temp->balance -= amount;

	// Update the transaction file directly without storing all lines in memory
	ifstream read("transaction.txt");
	ofstream write("temp.txt");

	if (!read.is_open() || !write.is_open()) {
		cout << "Error opening file." << endl;
		return;
	}

	int line = 0;
	bool accountFound = false;
	while (read >> line) {
		write << line << endl;
		if (line == accountno && !accountFound) {
			accountFound = true;
			write << amount << endl;  // Record the deposit amount
		}
	}

	if (!accountFound) {
		// If account number was not found, append it
		write << accountno << endl << amount << endl;
	}

	read.close();
	write.close();

	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");

	// Update the server file with the new BST state
	update_server(Root);
}


/*
void BST_Tree::deposit(int accountno,int amount)
{
	load_Server();
	BST_Node *temp = search(Root, accountno);
	temp->balance = temp->balance + amount;

	vector <int> data;
	ifstream read;
	read.open("transaction.txt", ios::app);
	int line = 0;
	while (!read.eof())
	{
		read >> line;
		if (line == accountno)
		{
			data.push_back(line);
			line = amount;
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	ofstream write;
	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");


	update_server(Root);
}
*/


void BST_Tree::deposit(int accountno, int amount) {
	// Load the BST from the server file
	load_Server();

	// Search for the account in the BST
	BST_Node* temp = search(Root, accountno);
	if (temp == nullptr) {
		cout << "Account not found." << endl;
		return;
	}

	// Update the account balance
	temp->balance += amount;

	// Update the transaction file directly
	ifstream read("transaction.txt");
	ofstream write("temp.txt");

	if (!read.is_open() || !write.is_open()) {
		cout << "Error opening file." << endl;
		return;
	}

	int line = 0;
	bool accountFound = false;
	while (read >> line) {
		if (line == accountno) {
			// Account found, record the deposit amount
			accountFound = true;
			write << line << endl;  // Write account number
			write << amount << endl;  // Write deposit amount
		}
		else {
			// Write the current line as it is
			write << line << endl;
		}
	}

	// If the account number was not found in the file, append it
	if (!accountFound) {
		write << accountno << endl << amount << endl;  // New account with deposit amount
	}

	read.close();
	write.close();

	// Replace old transaction file with the updated file
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");

	// Update the server file with the new BST state
	update_server(Root);
}



void BST_Tree::editaccount_byAdmin()
{

}

/*
void BST_Tree::transfer(int sender_accountno,int reciever_accountno,int sender_amount)
{
	// happening in tree
	BST_Node *sender = search(Root, sender_accountno);
	sender->balance = sender->balance -sender_amount;
	BST_Node *reciever = search(Root, reciever_accountno);
	reciever->balance = reciever->balance + sender_amount;
	update_server(Root);

	// Now happening in the transacton file

	//  for sender
	vector <int> data;
	ifstream read;
	read.open("transaction.txt", ios::app);
	int line = 0;
	while (!read.eof())
	{
		read >> line;
		if (line == sender_accountno)
		{
			data.push_back(line);
			line = (sender_amount*-1);
			data.push_back(line);
			continue;
		}
		data.push_back(line);
	}
	read.close();

	ofstream write;
	write.open("temp.txt", ios::app);
	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}
	write.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");


	//  for reciever 


	vector <int> data1;
	ifstream read1;
	read1.open("transaction.txt", ios::app);
	int line1 = 0;
	while (!read1.eof())
	{
		read1 >> line1;
		if (line1 == reciever_accountno)
		{
			data1.push_back(line1);
			line1 = sender_amount;
			data1.push_back(line1);
			continue;
		}
		data1.push_back(line1);
	}
	read1.close();

	ofstream write1;
	write1.open("temp.txt", ios::app);
	for (int i = 0; i < data1.size(); i++)
	{
		write1 << data1[i] << endl;
	}
	write1.close();
	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");

}
*/

void BST_Tree::transfer(int sender_accountno, int receiver_accountno, int sender_amount)
{
	// Step 1: Update balances in the tree
	BST_Node* sender = search(Root, sender_accountno);
	if (!sender) {
		cout << "Sender account not found." << endl;
		return;
	}
	if (sender->balance < sender_amount) {
		cout << "Insufficient funds in sender's account." << endl;
		return;
	}

	sender->balance -= sender_amount;

	BST_Node* receiver = search(Root, receiver_accountno);
	if (!receiver) {
		cout << "Receiver account not found." << endl;
		return;
	}

	receiver->balance += sender_amount;

	// Update the server file with the new BST state
	update_server(Root);

	// Step 2: Update the transaction file
	ifstream read("transaction.txt");
	ofstream write("temp.txt");

	if (!read.is_open() || !write.is_open()) {
		cout << "Error opening file." << endl;
		return;
	}

	int line;
	bool sender_found = false, receiver_found = false;
	while (read >> line) {
		if (line == sender_accountno) {
			sender_found = true;
			write << line << endl;
			write << -sender_amount << endl; // Withdraw amount
		}
		else if (line == receiver_accountno) {
			receiver_found = true;
			write << line << endl;
			write << sender_amount << endl; // Deposit amount
		}
		else {
			write << line << endl;
		}
	}

	if (!sender_found) {
		write << sender_accountno << endl << -sender_amount << endl;
	}

	if (!receiver_found) {
		write << receiver_accountno << endl << sender_amount << endl;
	}

	read.close();
	write.close();

	remove("transaction.txt");
	rename("temp.txt", "transaction.txt");
}


void BST_Tree::transaction_history()
{
    
}



int BST_Tree::findMax(BST_Node* root) {
	// Check if the tree is empty
	if (root == nullptr) {
		throw std::runtime_error("The tree is empty");
	}

	// Traverse to the rightmost node
	while (root->right != nullptr) {
		root = root->right;
	}

	// Return the account number of the rightmost node
	return root->account_number;
}


/*void BST_Tree::load_Server()
{
	ifstream read;
	read.open("server.txt", ios::app);

	string name = "";
	string address = "";
	int accountno = 0;
	int password = 0;
	int balance = 0;
	while (!read.eof())
	{
		
		
		
		getline(read, name);
		getline(read, address);
		read >> accountno;
		read >> password;
		read >> balance;
		read.ignore();
		read.ignore();

		if (name!="" && address != "" && accountno != 0 && password != 0 )
		{
			//cout << "enter hua" << endl;
			BST_Node * temp = new BST_Node(name, address, accountno, password, balance);
			BST_Node * current = Root;
			if (Root == nullptr)
			{

				Root = temp;
			}
			else
			{
				while (true)
				{

					if (accountno < current->account_number)
					{
						if (current->left == nullptr)
						{
							current->left = temp;
							break;
						}
						current = current->left;
					}

					if (accountno > current->account_number)
					{
						if (current->right == nullptr)
						{
							current->right = temp;
							break;
						}
						current = current->right;
					}
					if (accountno == current->account_number)
					{
						break;
					}
				}
			}
		}
	}
	read.close();
}

*/


void BST_Tree::load_Server() {
	ifstream read("server.txt");

	string name, address;
	int accountno, password, balance;

	while (getline(read, name) && getline(read, address) && read >> accountno >> password >> balance) {
		if (!name.empty() && !address.empty() && accountno != 0 && password != 0) {
			BST_Node* temp = new BST_Node(name, address, accountno, password, balance);
			insertIntoBST(Root, temp);
		}
	}
	read.close();
}

void BST_Tree::insertIntoBST(BST_Node*& root, BST_Node* temp) {
	if (root == nullptr) {
		root = temp;
		return;
	}

	if (temp->account_number < root->account_number) {
		insertIntoBST(root->left, temp);
	}
	else if (temp->account_number > root->account_number) {
		insertIntoBST(root->right, temp);
	}
}


/*
void BST_Tree:: update_server(BST_Node *root)
{
	static int i = 0;
	if (i == 0)
	{
		i++;
		remove("server.txt");
	}

	ofstream write;
	write.open("server.txt");

	if (root)
	{
		update_server(root->left);
		write << root->name<<endl;
		write << root->address<<endl;
		write << root->account_number<<endl;
		write << root->password<<endl;
		write << root->balance<<endl;
		update_server(root->right);
	}
	write.close();
	
	
}
*/

void BST_Tree::update_server(BST_Node* root)
{
	static bool isFirstCall = true;

	ofstream write;

	// Open file only on the first call to the function, in truncate mode to clear existing contents
	if (isFirstCall) {
		isFirstCall = false;
		write.open("server.txt", ios::trunc);
	}
	else {
		write.open("server.txt", ios::app);
	}

	if (!write.is_open()) {
		cerr << "Error opening server.txt for writing." << endl;
		return;
	}

	if (root) {
		update_server(root->left);  // Traverse left subtree
		write << root->name << endl;
		write << root->address << endl;
		write << root->account_number << endl;
		write << root->password << endl;
		write << root->balance << endl;
		update_server(root->right);  // Traverse right subtree
	}

	write.close();  // Close file after writing
}





BST_Node* BST_Tree:: search (BST_Node* root, int accountno)
{
	if (root == nullptr)
		return (nullptr);
	else if (accountno < root->account_number)
		return (search(root->left, accountno));
	else if (accountno > root->account_number)
		return (search(root->right, accountno));
	return (root);

}



void BST_Tree:: printoinfo(BST_Node* root)
{

	if (root)
	{
		printoinfo(root->left);
		cout << root->name << endl;
		cout << root->address<<endl;
		cout << root->account_number<<endl;
		cout << root->password<<endl;
		cout << root->balance<<endl;
		printoinfo(root->right);
	}
}

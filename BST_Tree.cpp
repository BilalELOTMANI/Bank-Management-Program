# include "BST_Tree.h"
# include "Hashtable.h"


BST_Tree:: BST_Tree() {

}

void BST_Tree::add_Account(string name, string address, long long accountno, int password, long long balance)
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

BST_Node* BST_Tree::delete_Account(BST_Node * root, long long accountno)
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
			long long maxValue = findMax(root->left);
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

void BST_Tree::withdraw(long long accountno, long long amount)
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

	long long line = 0;
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

void BST_Tree::deposit(long long accountno, long long amount) {
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

	long long line = 0;
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

void BST_Tree::editaccount_byAdmin() {
	long long accountno;
	cout << "Enter the account number of the account you want to edit: ";
	cin >> accountno;

	// Search for the account in the BST
	BST_Node* accountNode = search(Root, accountno);
	if (accountNode == nullptr) {
		cout << "Account not found." << endl;
		return;
	}

	int choice = 0;
	while (choice != 6) {
		cout << "What would you like to edit?" << endl;
		cout << "1. Name" << endl;
		cout << "2. Address" << endl;
		cout << "3. Password" << endl;
		cout << "4. Balance" << endl;
		cout << "5. Exit" << endl;
		cin >> choice;

		switch (choice) {
		case 1: {
			string newName;
			cout << "Enter the new name: ";
			cin.ignore();
			getline(cin, newName);
			accountNode->name = newName;
			cout << "Name updated successfully." << endl;
			break;
		}
		case 2: {
			string newAddress;
			cout << "Enter the new address: ";
			cin.ignore();
			getline(cin, newAddress);
			accountNode->address = newAddress;
			cout << "Address updated successfully." << endl;
			break;
		}
		case 3: {
			string newPasswordStr;
			cout << "Enter the new password (4 digits): ";
			cin >> newPasswordStr;

			if (newPasswordStr.length() != 4) {
				cout << "Password must be 4 digits." << endl;
			}
			else {
				long long newPassword = stoll(newPasswordStr); // Convert the string to a long long
				accountNode->password = newPassword; // Store the numeric version
				cout << "Password updated successfully." << endl;
			}
			break;
		}
		case 4: {
			long long newBalance;
			cout << "Enter the new balance: ";
			cin >> newBalance;
			accountNode->balance = newBalance;
			cout << "Balance updated successfully." << endl;
			break;
		}
		case 5:
			cout << "Exiting edit mode." << endl;
			break;
		default:
			cout << "Invalid option, please try again." << endl;
		}
	}

	// Update the server file with the new BST state
	update_server(Root);
}

void BST_Tree::transfer(long long sender_accountno, long long receiver_accountno, long long sender_amount)
{
	// Step 1: Update balances in the tree
	update_server(Root);
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

	long long line;
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

long long BST_Tree::findMax(BST_Node* root) {
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

void BST_Tree::load_Server() {
	ifstream read("server.txt");

	string name, address;
	long long accountno, balance;
	int password;

	while (read >> name && 
		read >> address && 
		read >> accountno &&
		read >> password &&
		read >> balance
		) {
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

BST_Node* BST_Tree:: search (BST_Node* root, long long accountno)
{
	if (root == nullptr)
		return (nullptr);
	else if (accountno < root->account_number)
		return (search(root->left, accountno));
	else if (accountno > root->account_number)
		return (search(root->right, accountno));
	return (root);

}

void BST_Tree:: printoinfo(const BST_Node* root) const
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

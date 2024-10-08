#include "Hashtable.h"


using namespace std;

Hashtable::Hashtable() {
	size = 10;  // Set the size of the hash table 
	table.resize(size);
}

void Hashtable::add(long long a, int p) {
	ofstream write;
	write.open("hashtable.txt", ios::app);
	write << a << endl << p << endl;
	write.close();

	loadhashtable();
}

bool Hashtable::match(long long a, int p) {
	int r = a % size;
	for (const auto& entry : table[r]) {
		if (entry.first == a && entry.second == p) {
			return true;
		}
	}
	return false;
}

void Hashtable::display() {
	for (int i = 0; i < size; ++i) {
		cout << "Bucket " << i << ": ";
		for (const auto& entry : table[i]) {
			cout << "(" << entry.first << ", " << entry.second << ") ";
		}
		cout << endl;
	}
}

void Hashtable::loadhashtable() {
	long long acc;
	int pass;

	ifstream read;
	read.open("hashtable.txt");
	while (read >> acc >> pass) {
		if (match(acc, pass)) {
			continue;
		}
		int r = acc % size;
		table[r].emplace_back(acc, pass);
	}
	read.close();
}

void Hashtable::displayPasswords() {
	for (int i = 0; i < size; ++i) {
		for (const auto& entry : table[i]) {
			cout << "Account Number: " << entry.first << endl;
			cout << "Password: " << entry.second << endl << endl;
		}
	}
}

void Hashtable::delete_password(long long accountno) {
	vector<pair<long long, long long>> temp_entries;

	ifstream read;
	read.open("hashtable.txt");
	long long acc;
	int pass;
	while (read >> acc >> pass) {
		if (acc != accountno) {
			temp_entries.emplace_back(acc, pass);
		}
	}
	read.close();

	ofstream write;
	write.open("hashtable.txt", ios::trunc); // Clear the file
	for (const auto& entry : temp_entries) {
		write << entry.first << endl;
		write << entry.second << endl;
	}
	write.close();

	// Clear the hash table and reload it from the updated file
	table.clear();
	table.resize(size);
	loadhashtable();
}




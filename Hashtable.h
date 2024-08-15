#ifndef HASHTABLE_H  // Start of include guard
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>  // For the linked list
#include <utility>  // For std::pair
#include <fstream>

class Hashtable {
private:
    std::vector<std::list<std::pair<int, int>>> table;
    int size;

public:
    Hashtable();
    void add(long long a, int p);
    bool match(long long a, int p);
    void display();
    void displayPasswords();
    void delete_password(long long accountno);
    void loadhashtable();
};

#endif // HASHTABLE_H  // End of include guard

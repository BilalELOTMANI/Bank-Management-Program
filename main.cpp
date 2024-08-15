#include "Hashtable.h"
#include "BST_Tree.h"
#include "admin.h"
#include "staff.h"
#include "customer.h"
#include <iostream>
using namespace std;

// Function to initialize the system
void boot(Hashtable& H, BST_Tree& T) {
    H.loadhashtable();
    T.load_Server();
}

int main() {
    Hashtable H;
    BST_Tree T;

    // Initialize the system
    boot(H, T);

    int condition = 0;
    while (condition != 4) {
        cout << "You want to login as:" << endl;
        cout << "1. ADMIN" << endl;
        cout << "2. STAFF" << endl;
        cout << "3. CUSTOMER" << endl;
        cout << "4. EXIT" << endl;
        cin >> condition;

        switch (condition) {
        case 1:
            admin();
            break;
        case 2:
            staff(); // Assuming you will implement the staff function
            break;
        case 3:
            customer();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Please enter a valid option!" << endl;
            break;
        }
    }
    return 0;
}

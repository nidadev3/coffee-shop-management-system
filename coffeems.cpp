#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Global Arrays
string menuitems[100];
int menuprices[100];
string menucategories[100];
string staffnames[100];
int currentorder[100];

// Global Variables
int menucount = 0;
int staffcount = 0;
int ordercount = 0;
bool orderfinalized = false;

// Function Declarations
void savemenufile();
void loadmenufile();
void savestafffile();
void loadstafffile();
void adminlogin();
void cashierlogin();
void additem();
void updateitem();
void deleteitem();
void viewmenu();
void addstaff();
void deletestaff();
void viewstaff();
void placeorder();
void cancelorder();
void viewreceipt();
void searchitem();

int main() {
    loadmenufile();
    loadstafffile();
    int option;
    cout << "1: Admin Login" << endl;
    cout << "2: Cashier Login" << endl;
    cout << "Option: ";
    cin >> option;
    if (option == 1) adminlogin();
    else if (option == 2) cashierlogin();
    else cout << "Invalid Option" << endl;
    return 0;
}

void savemenufile() {
    ofstream file("menu.txt");
    for (int i = 0; i < menucount; i++)
        file << menuitems[i] << " " << menuprices[i] << " " << menucategories[i] << endl;
    file.close();
}

void loadmenufile() {
    ifstream file("menu.txt");
    while (file >> menuitems[menucount] >> menuprices[menucount] >> menucategories[menucount])
        menucount++;
    file.close();
}

void savestafffile() {
    ofstream file("staff.txt");
    for (int i = 0; i < staffcount; i++)
        file << staffnames[i] << endl;
    file.close();
}

void loadstafffile() {
    ifstream file("staff.txt");
    while (file >> staffnames[staffcount])
        staffcount++;
    file.close();
}

void adminlogin() {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    if (user == "admin" && pass == "admin123") {
        int opt;
        do {
            cout << "1: Add Item" << endl;
            cout << "2: Update Item" << endl;
            cout << "3: Delete Item" << endl;
            cout << "4: View Menu" << endl;
            cout << "5: Add Staff" << endl;
            cout << "6: Delete Staff" << endl;
            cout << "7: View Staff" << endl;
            cout << "8: Logout" << endl;
            cout << "Enter Option: ";
            cin >> opt;
            switch (opt) {
                case 1: additem(); break;
                case 2: updateitem(); break;
                case 3: deleteitem(); break;
                case 4: viewmenu(); break;
                case 5: addstaff(); break;
                case 6: deletestaff(); break;
                case 7: viewstaff(); break;
                case 8: cout << "Logged out." << endl; break;
                default: cout << "Invalid Option" << endl;
            }
        } while (opt != 8);
    } else {
        cout << "Login Failed!" << endl;
    }
}

void cashierlogin() {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;
    if (user == "cashier" && pass == "cashier123") {
        int opt;
        do {
            cout << "1: View Menu" << endl;
            cout << "2: Place Order" << endl;
            cout << "3: Cancel Order" << endl;
            cout << "4: View Receipt" << endl;
            cout << "5: Search Item" << endl;
            cout << "6: Logout" << endl;
            cout << "Enter Option: ";
            cin >> opt;
            switch (opt) {
                case 1: viewmenu(); break;
                case 2: placeorder(); break;
                case 3: cancelorder(); break;
                case 4: viewreceipt(); break;
                case 5: searchitem(); break;
                case 6: cout << "Logged out." << endl; break;
                default: cout << "Invalid Option" << endl;
            }
        } while (opt != 6);
    } else {
        cout << "Login Failed!" << endl;
    }
}

void additem() {
    cout << "Item name: ";
    cin >> menuitems[menucount];
    cout << "Price: ";
    cin >> menuprices[menucount];
    cout << "Category: ";
    cin >> menucategories[menucount];
    menucount++;
    savemenufile();
    cout << "Item added." << endl;
}

void updateitem() {
    viewmenu();
    int index;
    cout << "Index to update: ";
    cin >> index;
    if (index >= 0 && index < menucount) {
        cout << "New name: ";
        cin >> menuitems[index];
        cout << "New price: ";
        cin >> menuprices[index];
        cout << "New category: ";
        cin >> menucategories[index];
        savemenufile();
        cout << "Item updated." << endl;
    } else {
        cout << "Invalid Index" << endl;
    }
}

void deleteitem() {
    viewmenu();
    int index;
    cout << "Index to delete: ";
    cin >> index;
    if (index >= 0 && index < menucount) {
        for (int i = index; i < menucount - 1; i++) {
            menuitems[i] = menuitems[i + 1];
            menuprices[i] = menuprices[i + 1];
            menucategories[i] = menucategories[i + 1];
        }
        menucount--;
        savemenufile();
        cout << "Item deleted." << endl;
    } else {
        cout << "Invalid Index" << endl;
    }
}

void viewmenu() {
    if (menucount == 0)
        cout << "Menu is empty." << endl;
    else
        for (int i = 0; i < menucount; i++)
            cout << i << ". " << menuitems[i] << " - Rs." << menuprices[i] << " (" << menucategories[i] << ")" << endl;
}

void addstaff() {
    cout << "Staff name: ";
    cin >> staffnames[staffcount++];
    savestafffile();
    cout << "Staff added." << endl;
}

void deletestaff() {
    viewstaff();
    int index;
    cout << "Index to delete: ";
    cin >> index;
    if (index >= 0 && index < staffcount) {
        for (int i = index; i < staffcount - 1; i++)
            staffnames[i] = staffnames[i + 1];
        staffcount--;
        savestafffile();
        cout << "Staff deleted." << endl;
    } else {
        cout << "Invalid Index" << endl;
    }
}

void viewstaff() {
    if (staffcount == 0)
        cout << "No staff available." << endl;
    else
        for (int i = 0; i < staffcount; i++)
            cout << i << ". " << staffnames[i] << endl;
}

void placeorder() {
    int index;
    viewmenu();
    cout << "Enter item index to add to order: ";
    cin >> index;
    if (index >= 0 && index < menucount) {
        currentorder[ordercount++] = index;
        orderfinalized = false;
        cout << "Item added." << endl;
    } else {
        cout << "Invalid Index" << endl;
    }
}

void cancelorder() {
    if (ordercount == 0)
        cout << "No order to cancel." << endl;
    else if (orderfinalized)
        cout << "Order finalized, can't cancel." << endl;
    else {
        ordercount = 0;
        cout << "Order canceled." << endl;
    }
}

void viewreceipt() {
    if (ordercount == 0) {
        cout << "No items in order." << endl;
        return;
    }
    float total = 0;
    cout << "--- Order Receipt ---" << endl;
    for (int i = 0; i < ordercount; i++) {
        int idx = currentorder[i];
        cout << menuitems[idx] << " - Rs." << menuprices[idx] << endl;
        total += menuprices[idx];
    }
    cout << "Total: Rs." << total << endl;
    orderfinalized = true;
    ordercount = 0;
}

void searchitem() {
    string keyword;
    cout << "Search by name or category: ";
    cin >> keyword;
    bool found = false;
    for (int i = 0; i < menucount; i++) {
        if (menuitems[i].find(keyword) != string::npos || menucategories[i].find(keyword) != string::npos) {
            cout << i << ". " << menuitems[i] << " - Rs." << menuprices[i] << " (" << menucategories[i] << ")" << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No match found." << endl;
}

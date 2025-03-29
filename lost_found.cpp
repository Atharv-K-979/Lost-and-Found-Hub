#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// Function to get the current date and time
string getCurrentDateTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

// Item Class
class Item {
private:
    string name;
    string description;
    string status; // "lost", "found", or "claimed"
    string owner; // User who reported the item
    string dateTime;  // Date and Time of reporting

public:
    Item(const string& name, const string& description, const string& status, const string& owner, const string& dateTime)
        : name(name), description(description), status(status), owner(owner), dateTime(dateTime) {}

    string getName() const { return name; }
    string getDescription() const { return description; }
    string getStatus() const { return status; }
    string getOwner() const { return owner; }
    string getDateTime() const { return dateTime; }
    void setStatus(const string& newStatus) { status = newStatus; }
};

// Hub Class
class Hub {
private:
    vector<Item> items;

public:
    Hub() {
        // Adding some default items
        items.push_back(Item("Wallet", "Black leather wallet with ID inside", "lost", "Alice", getCurrentDateTime()));
        items.push_back(Item("Umbrella", "Red umbrella with polka dots", "found", "Bob", getCurrentDateTime()));
        items.push_back(Item("Phone", "Samsung Galaxy S21, cracked screen", "lost", "Charlie", getCurrentDateTime()));
    }

    void addItem(const Item& item) { items.push_back(item); }

    void listItems() const {
        if (items.empty()) {
            cout << "\n\033[1;31mNo items found.\033[0m" << endl;
            return;
        }
        cout << "\n\033[1;34m=== List of Items ===\033[0m" << endl;
        cout << left << setw(20) << "Name" << setw(30) << "Description" << setw(10) << "Status" << setw(15) << "Owner" << setw(20) << "Reported At" << endl;
        cout << string(100, '-') << endl;
        for (const auto& item : items) {
            cout << left << setw(20) << item.getName()
                 << setw(30) << item.getDescription()
                 << setw(10) << item.getStatus()
                 << setw(15) << item.getOwner()
                 << setw(20) << item.getDateTime() << endl;
        }
    }

    void findItem(const string& name) const {
        for (const auto& item : items) {
            if (item.getName() == name) {
                cout << "\n\033[1;32mFound Item:\033[0m " << endl;
                cout << "Name: " << item.getName() << "\nDescription: " << item.getDescription()
                     << "\nStatus: " << item.getStatus() << "\nOwner: " << item.getOwner()
                     << "\nReported At: " << item.getDateTime() << endl;
                return;
            }
        }
        cout << "\n\033[1;31mItem not found.\033[0m" << endl;
    }

    void updateItemStatus(const string& name, const string& newStatus) {
        for (auto& item : items) {
            if (item.getName() == name) {
                item.setStatus(newStatus);
                cout << "\n\033[1;33mStatus of " << name << " updated to " << newStatus << ".\033[0m" << endl;
                return;
            }
        }
        cout << "\n\033[1;31mItem not found.\033[0m" << endl;
    }

    void deleteItem(const string& name) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getName() == name) {
                string confirmation;
                cout << "\nAre you sure you want to delete '" << name << "'? (yes/no): ";
                cin >> confirmation;
                if (confirmation == "yes") {
                    items.erase(it);
                    cout << "\n\033[1;32mItem '" << name << "' has been removed from the system.\033[0m" << endl;
                } else {
                    cout << "\n\033[1;33mDeletion cancelled.\033[0m" << endl;
                }
                return;
            }
        }
        cout << "\n\033[1;31mItem not found.\033[0m" << endl;
    }
};

// Function to display the menu
void displayMenu() {
    cout << "\n\033[1;36m=== Lost and Found Hub ===\033[0m" << endl;
    cout << "\033[1;35m1. Add Item\033[0m" << endl;
    cout << "\033[1;35m2. List Items\033[0m" << endl;
    cout << "\033[1;35m3. Find Item\033[0m" << endl;
    cout << "\033[1;35m4. Update Item Status\033[0m" << endl;
    cout << "\033[1;35m5. Delete Item\033[0m" << endl;
    cout << "\033[1;35m6. Exit\033[0m" << endl;
    cout << "\033[1;36mChoose an option: \033[0m";
}

// Main Function
int main() {
    Hub hub;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cout << "\n\033[1;31mInvalid input. Please enter a number between 1 and 6.\033[0m" << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                string name, description, status, owner;
                cout << "Enter item name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter item description: ";
                getline(cin, description);
                cout << "Enter item status (lost/found): ";
                cin >> status;
                cout << "Enter your name (owner): ";
                cin >> ws;
                getline(cin, owner);
                hub.addItem(Item(name, description, status, owner, getCurrentDateTime()));
                cout << "\n\033[1;32mItem added successfully!\033[0m" << endl;
                break;
            }
        
            case 2:
                hub.listItems();
                break;
        
            case 3: {
                string name;
                cout << "Enter item name to find: ";
                cin >> ws;
                getline(cin, name);
                hub.findItem(name);
                break;
            }
        
            case 4: {
                string name, newStatus;
                cout << "Enter item name to update status: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter new status (lost/found/claimed): ";
                cin >> newStatus;
                hub.updateItemStatus(name, newStatus);
                break;
            }
        
            case 5: {
                string deleteName;
                cout << "Enter item name to delete: ";
                cin >> ws;
                getline(cin, deleteName);
                hub.deleteItem(deleteName);
                break;
            }
        
            case 6:
                cout << "\n\033[1;36mExiting the program.\033[0m" << endl;
                break;
        
            default:
                cout << "\n\033[1;31mInvalid option! Please choose a valid option.\033[0m" << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
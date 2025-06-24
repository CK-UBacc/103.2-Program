// 103.2 Intergrated Studio I - Group Project
// Group Members:
//  Christopher Kelly
//  Feilx Bryant
//  Warner Nash

#include <iostream>
#include <iomanip>//Used for output formating such as setw();
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;

class Employees {
public:
    list<string> employeeNames;

    void displayList() {
        cout << "\nCurrent Employee List:\n";
        cout << "----------------------\n";
        if (employeeNames.empty()) {
            cout << "No employees in the list.\n";
            return;
        }
        int i = 1;
        for (const string& employeeName : employeeNames) {
            cout << i << ". " << employeeName << endl;
            i++;
        }
        cout << "----------------------\n";
    }

    void addEmployee() {
        string employeeName;
        cout << "\nEnter the name of the employee to add: ";
        getline(cin, employeeName);
        
        if (find(employeeNames.begin(), employeeNames.end(), employeeName) != employeeNames.end()) {
            cout << "Employee " << employeeName << " already exists in the list.\n";
            return;
        }
        
        employeeNames.push_back(employeeName);
        cout << "Successfully added employee: " << employeeName << endl;
    }

    void removeEmployee() {
        displayList();
        cout << "\nEnter the name of the employee to remove: ";
        string employeeName;
        getline(cin, employeeName);
        
        // finds the employee in the list
        auto it = find(employeeNames.begin(), employeeNames.end(), employeeName);

        // removes employee if found in list
        if (it != employeeNames.end()) {
            employeeNames.erase(it);
            cout << "Successfully removed employee: " << employeeName << endl;
        }
        else {
            cout << "Employee " << employeeName << " not found in the list.\n";
        }
    }

    void saveList() {
        // Save employee list to CSV file
        ofstream EmployeeFile("EmployeeList.csv");

        if (!EmployeeFile) {
            cout << "Error opening file for saving.\n";
            return;
        }

        // writes employee name to file from employee list
        for (const string& employeeName : employeeNames) {
            EmployeeFile << employeeName << "\n";
        }

        EmployeeFile.close();
        cout << "Employee list has been saved to EmployeeList.csv\n";
    }

    void loadList() {
        ifstream EmployeeFile("EmployeeList.csv");

        if (!EmployeeFile) {
            cout << "Employee file not found. Please contact support.\n";

            return;
        }

        // clears the existing list
        employeeNames.clear();

        // reads each line from file and adds to list
        string employeeName;
        while (getline(EmployeeFile, employeeName)) {
            employeeNames.push_back(employeeName);
        }

        EmployeeFile.close();
        cout << "Employee list loaded from EmployeeList.csv\n";
    }
};

class Inventory {
public:
    string
        inventoryName = "UNINITIALIZED";

    struct Item {
        string
            name;
        int
            quantity,
            price;
    };

    vector<Item> list;

    //Function that displays currently loaded inventory
    void displayInventory() {
        /*TO-DO!
        * -figure out how to display money
        */
        cout
            << setw(8) << left << "Quantity"
            << setw(22) << left << " |Product"
            << left << "|Price"
            << "\n";
        for (Item i : list) {
            if (i.quantity < 5) {
                cout << " [!] ";
            }
            else {
                cout << "     ";
            }
            cout << setfill(' ') << setw(3) << right << i.quantity;
            cout << " |";
            cout << setfill('.') << setw(20) << left << i.name;
            cout << "|";
            cout << setfill(' ') << "$" << left << i.price;

            cout << endl;
        }
    }

    //Outputs log message to log file
    void log(string logMessage) {
        ofstream LogFile(inventoryName + "_Log.txt", ios::app);

        LogFile << logMessage << endl;

        LogFile.close();
    }

    // Saves the inventory to a file to later be loaded
    /*
    -Add Log functionality
    */
    void SaveInventory() {
        ofstream InventoryFile(inventoryName + "_Inventory.csv");

        // Error prevention
        if (!InventoryFile) {
            cout << "Error opening file.\n";
            return;
        }

        // Adds and formats each item
        for (const Item item : list) {
            InventoryFile << item.name << "," << item.quantity << "," << item.price << "\n";
        }
        InventoryFile.close();
        cout << "Inventory has been saved to Inventory.csv\n";
    }

    void loadInventory() {
        ifstream InventoryFile(inventoryName + "_Inventory.csv");
        if (!InventoryFile) {
            cout << "Inventory file cannot be found.\n";
            return;
        }

        list.clear(); // clears the current inventory

        string name;
        int quantity, price;
        char comma;

        while (InventoryFile >> ws && getline(InventoryFile, name, ',')) {
            InventoryFile >> quantity >> comma >> price;
            list.push_back({ name, quantity, price });
            InventoryFile.ignore(); // skips the newline
        }

        InventoryFile.close();
        cout << "Inventory has been loaded from file\n";
    }

    //Creates a new inventory listing
    void addItem() {
        string
            newName;
        int
            newQuantity,
            newPrice;


        cout << "Input new item name:\n";
        cin.ignore();
        getline(cin, newName);
        transform(newName.begin(), newName.end(), newName.begin(), ::toupper);

        // Check if item already exists
        for (Item item : list) {
            if (item.name == newName) {
                cout << "Item already exists.\n";
                return;
            }
        }

        cout << "Input quantity:\n";
        do {
            cin >> newQuantity;
            if (newQuantity < 0) {
                cout << "Quantity has to be positive.\n";
                //return;
            }
        } while (newQuantity < 0);

        cout << "Input price:\n$";
        do {
            cin >> newPrice;
            if (newPrice < 0) {
                cout << "Price has to be positive.\n";
                //return;
            }
        } while (newPrice < 0);

        list.push_back({ newName, newQuantity, newPrice });

        //Logging the change to the file
        log("Added " + to_string(newQuantity) + " of \"" + newName + "\" with price $" + to_string(newPrice));//Removed the log message variable bc it's not needed
    }

    bool findItem(Item*& ptr, string itemDesired) {
        transform(itemDesired.begin(), itemDesired.end(), itemDesired.begin(), ::toupper);
        for (Item& item : list) {
            if (item.name == itemDesired) {
                ptr = &item;
                return true;
            }
        }
        cout << "Could not find \"" << itemDesired << "\" in list.\n";
        return false;
    }

    //Testing stuff
    void itemFuckery() {
        Item* ptr = &list[0];
        //vector<Item>::iterator it = list.begin();
        string itemDesired = "jam";
        int index;

        displayInventory();
        cout << endl;

        if (!findItem(ptr, itemDesired)) return;//Interesting
        index = ptr - &list[0];
        list.erase(list.begin() + index);
        displayInventory();

    }

    void editItem() {
        /*TO-DO
        * Add log functionality
        */
        string desiredItem,
            input,
            newName;
        Item* selectedItem = &list[0];
        int
            newQuantity,
            newPrice,
            menuOption;

        //Chose an item from the list
        cin.ignore();
        do {
            cout << "Enter the name of the item you want to edit.\nEnter \"0\" to cancel.\n";
            getline(cin, desiredItem);
            if (desiredItem == "0") {
                return;
            }
        } while (!findItem(selectedItem, desiredItem));

        system("cls");
        cout << "Editing: " << (*selectedItem).name << endl;

        //Menu Inputs

        do {
            cout << " 1:Edit Name | 2:Edit Quantity | 3:Edit Price | 0:Exit\n";
            cin >> menuOption;//entering non int input creates infinite loop
            switch (menuOption) {
            case 0:// Exit menu
                break;
            case 1: //edit name
                cout << "Enter new name for \"" << (*selectedItem).name << "\" or leave empty to keep name";
                //cout << "enter new name (leave empty to keep\"" << (*selectedItem).name << "\"):";
                cin.ignore();
                getline(cin, newName);
                transform(newName.begin(), newName.end(), newName.begin(), ::toupper);
                if (newName.empty()) {
                    cout << "ERROR: Input field is empty\n";
                }
                else {
                    (*selectedItem).name = newName;
                    //menuOption = 0;
                }
                break;

            case 2://edit quantity
                cout << "editing \"" << (*selectedItem).name << "\"): ";
                cout << "enter new quantity (current: " << (*selectedItem).quantity << "): ";
                cin >> input;
                try {
                    newQuantity = stoi(input);
                    if (newQuantity >= 0) (*selectedItem).quantity = newQuantity;
                    else cout << "quantity must be non-negative. keeping original quantity.\n";
                }
                catch (...) {
                    cout << "invalid input. keeping original quantity.\n";
                }

                break;

            case 3://editing price
                cout << "editing \"" << (*selectedItem).name << "\"): ";
                cout << "enter new price (current: $" << (*selectedItem).price << "): ";
                cin >> input;
                try {
                    newPrice = stoi(input);
                    if (newPrice >= 0) (*selectedItem).price = newPrice;
                    else cout << "price must be non -negative keeping orginal value\n";
                }
                catch (...) {
                    cout << "Invalid input keeping original value\n";
                }
                break;

            default:
                cout << "Invalid input\n";
            }
        } while (menuOption != 0);
    }

    void removeItem() {
        /*TO-DO
        * Add log functionality
        */
        string desiredItem,
            input;
        Item* selectedItem;
        int index;

        cout << "Chose an item to remove\n";
        cin.ignore();
        getline(cin, desiredItem);
        if (findItem(selectedItem, desiredItem)) {
            cout << "Removing \"" << selectedItem->name << "\" from inventory are you sure? y/n\n";
            cin >> input;
            if (input == "y") {
                index = selectedItem - &list[0];
                cout << "\"" << (*selectedItem).name << "\" removed from inventory\n";
                list.erase(list.begin() + index);
            }
            else {
                cout << "operation cancelled\n";
            }
        }


    }

    //check to see if the list is empty
    bool emptyCheck() {
        if (list.empty()) {
            cout << "ERROR. Cannot perform action. Inventory is empty.\n";
            return true;
        }
        return false;
    }

    void menu() {
        int menuOption;

        //Display inventory and menu options
        cout << "Editing inventory: " << inventoryName << "\n\n";
        displayInventory();
        cout << " 1:New item | 2:Edit item | 3:Remove item | 0:Exit\n";

        //Menu Inputs
        do {
            cin >> menuOption;
            switch (menuOption) {
            case 0:// Exit menu
                break;
            case 1:// Add inventory item
                addItem();
                system("cls");
                return menu();
            case 2:// Edit inventory item
                if (!emptyCheck()) {
                    editItem();
                    system("cls");
                    return menu();
                }
                break;
            case 3:// Remove inventory item
                if (!emptyCheck()) {
                    removeItem();
                    system("cls");
                    return menu();
                }
                break;
            default:
                cout << "Invalid input\n";
            }
        } while (menuOption != 0);
    }


};//Class Inventory end

//testing stuff
void timestamp() {

}

int main()
{
    Inventory test;
    test.inventoryName = "test inventory";
    Employees testEmployees;
    //timestamp();
    //testEmployees.loadList;
    //test.loadInventory();
    //test.menu();
    //test.SaveInventory();
    testEmployees.loadList();
    testEmployees.addEmployee("john");
    testEmployees.displayList();
    testEmployees.removeEmployee("Johnny");
    testEmployees.displayList();
}
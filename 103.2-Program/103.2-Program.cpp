//	103.2 Intergrated Studio I - Group Project
//	Group Members:
//		Christopher Kelly
//		Feilx Bryant
//		Warner Nash

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
	string
		rosterName;
	list<string> employeeNames = {"Johnny","Joey","Jeremy","Jamie","Jackie","Jeffrey"};

	void displayList() {

	}

	void addEmployee(string employeeName) {

	}

	void editEmployee(string employeeName) {

	}

	void removeEmployee(string employeeName) {

	}

	void saveList() {

	}

	void loadList() {

	}

};

class Inventory {
public:
	string 
		inventoryName = "UNINITIALIZED";

	struct Item{
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
			cout << setfill ('.') << setw(20) << left << i.name;
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
	void saveInventory() {
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
		cout << "Inventory has been saved to \"" + inventoryName + "_Inventory.csv\"\n";
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
	void addItem(){
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
		log("Added: " + to_string(newQuantity) + " of \"" + newName + "\" with price: $" + to_string(newPrice));//Removed the log message variable bc it's not needed
	}

	bool findItem(Item *&ptr, string itemDesired) {
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
		}while (!findItem(selectedItem, desiredItem));

		system("cls");

		//Menu Inputs
		do {
			cout << "Editing: " << (*selectedItem).name << "\nQuantity: " << (*selectedItem).quantity << "\nPrice: $" << (*selectedItem).price << endl;
			cout << " 1:Change Name | 2:Add Quantity | 3:Remove Quantity | 4:Change Price | 0:Exit\n";
			
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
				if (!newName.empty()) {

					//Log changes
					log("Changed name of \"" + (*selectedItem).name + "\" to \"" + newName + "\"");

					(*selectedItem).name = newName;
				}
				system("cls");
				break;

			case 2://Add quantity
				cout << "Enter quantity to add (current: " << (*selectedItem).quantity << "): ";
				cin >> input;
				try {
					newQuantity = stoi(input);
					system("cls");
					if (newQuantity > 0){

						//Log changes
						log("Added: " + to_string(newQuantity) + " of \"" + (*selectedItem).name + "\" (From: " + to_string((*selectedItem).quantity) + " to: " + to_string((*selectedItem).quantity + newQuantity) + ")");
						
						(*selectedItem).quantity += newQuantity;
				}
					else cout << "Invalid input. Input must be greater than 0.\n";
				}
				catch (...) {
					system("cls");
					cout << "Invalid input. Input must be an integer\n";
				}

				break;

			case 3://Remove quantity
				cout << "Enter quantity to remove (current: " << (*selectedItem).quantity << "): ";
				cin >> input;
				try {
					newQuantity = stoi(input);
					system("cls");
					if (newQuantity > 0) {
						if ((*selectedItem).quantity - newQuantity < 0) {
							cout << "ERROR! Operation would result in negative quantity of stock.\n";
						}
						else {

							//Log changes
							log("Removed " + to_string(newQuantity) + " of \"" + (*selectedItem).name + "\" (From " + to_string((*selectedItem).quantity) + " to " + to_string((*selectedItem).quantity - newQuantity) + ")");
							
							(*selectedItem).quantity -= newQuantity;
						}
					}
					else cout << "Invalid input. Input must be greater than 0.\n";
				}
				catch (...) {
					system("cls");
					cout << "Invalid input. Input must be an integer\n";
				}

				break;

			case 4://editing price
				cout << "enter new price (current: $" << (*selectedItem).price << "): ";
				cin >> input;
				try {
					newPrice = stoi(input);
					system("cls");
					if (newPrice >= 0) {

						//Log changes
						log("Set price of \"" + (*selectedItem).name + "\" from: $" + to_string((*selectedItem).price) + " to: $" + to_string(newPrice));

						(*selectedItem).price = newPrice;
					}
					else cout << "price must be non -negative keeping orginal value\n";
				}
				catch (...) {
					system("cls");
					cout << "Invalid input keeping original value\n";
				}
				break;

			default:
				cout << "Invalid input\n";
			}
		} while (menuOption != 0);
	}

	void removeItem() {
		string desiredItem,
			input;
		Item* selectedItem;
		int index;//For remove from vector jank

		cout << "Chose an item to remove\n";
		cin.ignore();
		getline(cin, desiredItem);
		if (findItem(selectedItem, desiredItem)) {
			cout << "Removing \"" << selectedItem->name << "\" from inventory are you sure? y/n\n";
			cin >> input;
			if (input == "y") {
				index = selectedItem - &list[0];
				cout << "\"" << (*selectedItem).name << "\" removed from inventory\n";

				//Logging the change to the file
				log("Deleted item \"" + (*selectedItem).name + "\". Had quantity: " + to_string((*selectedItem).quantity) + " and price: $" + to_string((*selectedItem).price));

				//Removing selected item from list
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

void runInventory(Inventory inv);

int main()
{
	Inventory test;
	test.inventoryName = "test inventory";

	//timestamp();
	runInventory(test);
}

void runInventory(Inventory inv) {
	inv.loadInventory();
	inv.menu();
	inv.saveInventory();
}
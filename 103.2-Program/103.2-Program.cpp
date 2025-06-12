//	103.2 Intergrated Studio I - Group Project
//	Group Members:
//		Christopher Kelly
//		Feilx Bryant
//		Warner Nash

#include <iostream>
#include <iomanip>//Used for output formating such as setw();
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

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

	vector<Item> list = {
		{"Peanuts", 3, 1520},//Temporary 
		{"Jam", 15, 299},
		{"Marmite", 5, 999}
	};

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

	//Creates a new inventory listing
	void addItem(){
		/*TO-DO!
		* -getline(); for name input
		* -check if name is already used
		* -check for valid quantity (e.g. not negative)
		* -price input formating (accepting 15.99 as a valid price)
		* -check for valid price (e.g. cant input $5.999)
		*/
		string
			//logMessage,
			newName;
		int 
			newQuantity,
			newPrice;

		//Taking inputs for new inventory item
		cout << "Input new item name\n";
		cin.ignore();
		getline(cin, newName);
		cout << "Input Quantity of items\n";
		cin >> newQuantity;
		cout << "Input new item price\n$";
		cin >> newPrice;
		list.push_back({newName, newQuantity, newPrice});
		cout << "\n\n";

		//Logging the change to the file
		log("Added " + to_string(newQuantity) + " of \"" + newName + "\" with price $" + to_string(newPrice));//Removed the log message variable bc it's not needed
	}

	//Gets the index of an item in the list that matches the provided string
	//Need to add case indifference
	int findItemIndex(string itemDesired) {
		int index = 0;
		//Go through the entire inventory list and compare their name with the name of the desired item
		for (Item item : list) {
			if (item.name == itemDesired) {
				return index;
			}
			index++;
		}
		return 0;
	}

	//Gets a reference of an item in the list that matches the provided string
	//Need to add case indifference
	Item& findItem(string itemDesired) {
		//Go through the entire inventory list and compare their name with the name of the desired item
		for (Item& item : list) {
			if (item.name == itemDesired) {
				return item;
			}
		}
		return list[0];//So if no item is found the entire program doesn't shit the bed and die
	}

	//Testing stuff
	void itemFuckery() {
		Item* ptr = &list[0];
		string itemDesired = "Jam";

		displayInventory();
		cout << (*ptr).name << endl;

		ptr = &list[findItemIndex(itemDesired)];//I hate this but it works
		cout << (*ptr).name << endl;
		(*ptr).name = "Jimmy Johnson";
		displayInventory();

		findItem(itemDesired).name = "George";
		displayInventory();
	}

	void editItem() {
		string desiredItem;
		Item* selectedItem = &list[0];
		int menuOption;

		//Menu Inputs
		cout << " 1:Edit Name | 2:Edit Quantity | 3:Edit Price | 0:Exit\n";
		do {
			cin >> menuOption;
			switch (menuOption) {
			case 0:// Exit menu
				break;
			case 1:
				(*selectedItem).name = "Jimmy Johson";
				cout << endl << (*selectedItem).name << endl << (*selectedItem).name;
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				cout << "Invalid input\n";
			}
		} while (menuOption != 0);
	}

	void removeItem() {
		string input;

		cout << "Chose an item to remove\n";
		cin.ignore();
		getline(cin, input);

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
					//system("cls");
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

	//timestamp();
	//test.menu();
	test.itemFuckery();
}

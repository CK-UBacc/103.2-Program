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
		inventoryName = "UNINITIALIZED",
		logMessage;

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

		//Logging change in file
		logMessage ="Added: " + to_string(newQuantity) + " \"" + newName + "\" with price set to $" + to_string(newPrice);
		log(logMessage);
	}

	void editItem() {
		cout << "editItem\n";
	}

	void removeItem() {
		cout << "removeItem\n";
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
				editItem();
				//system("cls");
				return menu();
			case 3:// Remove inventory item
				removeItem();
				//system("cls");
				return menu();
			default:
				cout << "Invalid input\n";
			}
		} while (menuOption != 0);
	}

};//Class Inventory end

int main()
{
	Inventory test;
	test.inventoryName = "test inventory";

	test.menu();
	//test.SaveInventory();
}

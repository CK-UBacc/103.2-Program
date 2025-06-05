//	103.2 Intergrated Studio I - Group Project
//	Group Members:
//		Christopher Kelly
//		Feilx Bryant
//		Warner Nash

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Inventory {
public:
	string testMessage = "This is working\n";

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
		* -Output formating
		*/
		for (Item i : list) {
			if (i.quantity < 5) {
				cout << " [!] ";
			}
			cout << "Product: " << i.name << "\tPrice: $" << i.price << "\tQuantity: " << i.quantity << "\n";
		}
	}

	//Outputs log message to log file
	void logChange() {

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

		cout << "Input new item name\n";
		cin.ignore();
		getline(cin, newName);

		cout << "Input Quantity of items\n";
		cin >> newQuantity;
		cout << "Input new item price\n$";
		cin >> newPrice;
		list.push_back({newName, newQuantity, newPrice});
		cout << "\n\n";
	}
};


int main()
{
	Inventory test;

	test.displayInventory();
	test.addItem();
	test.addItem();
	test.displayInventory();
}

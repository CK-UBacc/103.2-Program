//	103.2 Intergrated Studio I - Group Project
//	Group Members:
//		Christopher Kelly
//		Feilx Bryant
//		Warner Nash

#include <iostream>
#include <iomanip>//Used for output formating such as setw();
#include <string>
#include <vector>

using namespace std;

class Inventory {
public:
	string logprint;

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
		cout << "     " << setw(20) << left << "Product"
			<< setw(10) << left << "Price"
			<< setw(5) << left << "Quantity\n";
		for (Item i : list) {
			if (i.quantity < 5) {
				cout << " [!] ";
			}
			else {
				cout << "     ";
			}
			cout << setfill('.') << setw(20) << left << i.name
				<< "$" << setw(10) << left << i.price
				<< i.quantity << "\n";
		}
	}

	//Outputs log message to log file
	void logChange() {
		cout << logprint;
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
		cin.ignore();//First letter gets cut of on first input but not on subsequent inputs
		getline(cin, newName);

		cout << "Input Quantity of items\n";
		cin >> newQuantity;
		cout << "Input new item price\n$";
		cin >> newPrice;
		list.push_back({newName, newQuantity, newPrice});
		cout << "\n\n";
		logprint = "\n" + to_string(newQuantity) + " " + newName + "(s) have been added to the list for $" + to_string(newPrice) + ".\n";
		logChange();
	}
};//Class inventory end


int main()
{
	Inventory test;

	test.displayInventory();
	test.addItem();
	test.addItem();
	test.displayInventory();
}

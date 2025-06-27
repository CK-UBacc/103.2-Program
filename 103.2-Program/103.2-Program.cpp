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

/*
class EmployeeManager {
public:
	string
		rosterName,
		employeesFileName = "EmployeeList.csv";
	list<string> employeeNames; //= { "Johnny","Joey","Jeremy","Jamie","Jackie","Jeffrey" };

	void displayList() {
		for (string employeeName : employeeNames) {
			cout << employeeName << "\n";
		}
	}

	void addEmployee(string employeeName) {

		//cout << "Enter the name of the employee to add";
		//getline(cin, employeeName);

		employeeNames.push_back(employeeName);
	}

	//Ignore for now
	void editEmployee(string employeeName) {

	}



	void removeEmployee(string employeeName) {
		// finds the employee in the list
		auto it = find(employeeNames.begin(), employeeNames.end(), employeeName);

		// removes employee if found in list
		if (it != employeeNames.end()) {
			employeeNames.erase(it);
			cout << "Employee \"" << employeeName << "\" has been removed from the list.\n";
		}
		else {
			cout << "Employee \"" << employeeName << "\" not found in the list.\n";
		}
	}

	void saveEmployees() {
		// Save employee list to CSV file
		ofstream EmployeeFile(employeesFileName);

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

	void loadEmployees() {
		ifstream EmployeeFile(employeesFileName);

		if (!EmployeeFile) {
			if (!EmployeeFile) {
				cout << "ERROR! An error occured when loading list.\n";
				//No - Chris
				//cout << "Employee file not found. Initializing with default employees.\n";
				//employeeNames = { "Peter Griffin","Glenn Quagmire","Cleveland Brown","Joe Swanson" };
				return;
			}
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
*/

class RosterManager {
public:
	string
		rosterFileName = "test_Roster.csv",
		rosterName,
		employeesFileName = "EmployeeList.csv";

	struct {
		string day[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

		list<string> employeeList[7];
	} roster;

	list<string> employeeNames; //= { "Johnny","Joey","Jeremy","Jamie","Jackie","Jeffrey" };

	void displayEmployeeList() {
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

	void addEmployee(string employeeName) {
		/*
		cout << "Enter the name of the employee to add";
		getline(cin, employeeName);
		*/
		employeeNames.push_back(employeeName);
	}

		employeeNames.push_back(employeeName);
		cout << "Successfully added employee: " << employeeName << endl;
	}

	void removeEmployee() {
		displayEmployeeList();
		cout << "\nEnter the name of the employee to remove: ";
		string employeeName;
		getline(cin, employeeName);

		// finds the employee in the list
		auto it = find(employeeNames.begin(), employeeNames.end(), employeeName);

		// removes employee if found in list
		if (it != employeeNames.end()) {
			employeeNames.erase(it);
			cout << "Employee \"" << employeeName << "\" has been removed from the list.\n";
		}
		else {
			cout << "Employee \"" << employeeName << "\" not found in the list.\n";
		}
	}

	void saveEmployees() {
		// Save employee list to CSV file
		ofstream EmployeeFile(employeesFileName);

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

	void loadEmployees() {
		ifstream EmployeeFile(employeesFileName);

		if (!EmployeeFile) {
			if (!EmployeeFile) {
				cout << "ERROR! An error occured when loading list.\n";
				//No - Chris
				//cout << "Employee file not found. Initializing with default employees.\n";
				//employeeNames = { "Peter Griffin","Glenn Quagmire","Cleveland Brown","Joe Swanson" };
				return;
			}
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

	void displayRoster() {
		for (int i = 0; i < 7; i++) {
			cout << roster.day[i] << ":\n";
			if (roster.employeeList[i].empty()) {
				cout << "No employees asigned to this day";
			}
			else {
				for (string j : roster.employeeList[i]) {
					cout << "\"" << j << "\", ";
				}
			}
			cout << "\n\n";
		}
	}

	void addToRoster(string employee, int day) {
		roster.employeeList[day].push_back(employee);
	}

	void removeFromRoster(string employee, int day) {
		for (string i : roster.employeeList[day]) {
			if (employee == i) {
				roster.employeeList[day].remove(employee);
				return;//Stops program from crashing. Fun.
			}
		}
		cout << "ERROR! Could not find \"" << employee << "\" working on " << roster.day[day] << ".\n";
	}

	void loadRoster() {
		ifstream RosterFile(rosterFileName);

		string input;

		if (!RosterFile) {
			cout << "Roster file cannot be found.\n";
			return;
		}
		for (int i = 0; i < 7; i++) {
			while (getline(RosterFile, input, ',')) {
				if (input == "\n") break; //Jank fix for loading
				roster.employeeList[i].push_back(input);
			}
		}

		RosterFile.close();
		cout << "Roster has been loaded from \"" << rosterFileName << "\"\n";
	}

	void saveRoster() {
		ofstream RosterFile(rosterFileName);

		// Error prevention
		if (!RosterFile) {
			cout << "Error opening file.\n";
			return;
		}

		// Adds and formats each item
		for (int i = 0; i < 7; i++) {
			for (string j : roster.employeeList[i]) {
				RosterFile << j << ",";
			}
			RosterFile << "\n,";//Needs the comma before the newline character for jank fix for loading the file.
			RosterFile.close();
			cout << "Roster has been saved to \"" << rosterFileName << "\".";
		}
	}
	// Menu for managing the roster assignments
	void rosterMenu() {
		int menuOption;
		string employeeName;
		int day;

		do {
			displayRoster();

			// displays menu for roster
			cout << "\n| Roster Management Menu |\n";
			cout << "1. Add employee to roster\n";
			cout << "2. Remove employee from roster\n";
			cout << "3. Display current roster\n";
			cout << "0. Go Back\n\n";
			cout << "Enter your choice: ";

			cin >> menuOption;
			cin.ignore(); // Clear input buffer

			switch (menuOption) {
			case 1: // adds employee to roster
			{
				cout << "Enter employee name: ";
				getline(cin, employeeName);
				cout << "Enter day (0-6, where 0=Monday, 6=Sunday): ";
				cin >> day;
				if (day >= 0 && day <= 6) {
					addToRoster(employeeName, day);
					cout << "Employee added to roster.\n";
				}
				else {
					cout << "Invalid day number. Please enter a number between 0 and 6.\n";
				}
			}
			break;

			case 2: // removes employee from roster
			{
				cout << "Enter employee name to remove: ";
				getline(cin, employeeName);
				cout << "Enter day (0-6): ";
				cin >> day;
				if (day >= 0 && day <= 6) {
					removeFromRoster(employeeName, day);
					cout << "Employee removed from roster.\n";
				}
				else {
					cout << "Invalid day number. Please enter a number between 0 and 6.\n";
				}
			}
			break;

			case 3: // displays roster
				displayRoster();
				break;

			case 0: // goes back
				cout << "Returning to menu.\n";
				break;

			default:
				cout << "Invalid option. Please try again.\n";
			}

			// Wait for user to see messages before continuing
			if (menuOption != 0) {
				cout << "\nPress Enter to continue...";
				cin.get();
			}
		} while (menuOption != 0);
	}

	// menu for managing employees
	void employeeMenu() {
		int menuOption;
		string employeeName;

		do {
			// display employee list
			displayEmployeeList();

			// displays menu options
			cout << "\nEmployee Management Menu:\n";
			cout << "1. Add new employee\n";
			cout << "2. Remove employee\n";
			cout << "3. Display employee list\n";
			cout << "Enter your choice: ";

			// fet user input
			cin >> menuOption;


			switch (menuOption) {
			case 1: // adds new employee
			{
				cout << "Enter new employee name: ";
				getline(cin, employeeName);
				addEmployee(employeeName);
				cout << "Employee added to system.\n";
			}
			break;

			case 2: // Remove employee
			{
				cout << "Enter employee name to remove: ";
				getline(cin, employeeName);
				removeEmployee(employeeName);
				cout << "Employee removed from system.\n";
			}
			break;

			case 3: // displays employee list
				displayEmployeeList();
				break;

			case 0: // goes back to menu
				cout << "Returning to main menu.\n";
				break;

			default:
				cout << "Invalid option. Please try again.\n";
			}

class InventoryManager {
public:
	string 
		inventoryName = "UNINITIALIZED",
		inventoryFileExtension = "_Inventory.csv";

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
	void saveInventory() {
		ofstream InventoryFile(inventoryName + inventoryFileExtension);

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
		list.clear(); // clears the current inventory
		cout << "Inventory has been saved to \"" + inventoryName + inventoryFileExtension << "\"\n";
	}

	void loadInventory() {
		ifstream InventoryFile(inventoryName + inventoryFileExtension);
		if (!InventoryFile) {
			cout << "Inventory file cannot be found.\n";
			return;
		}

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
		  /*
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
		  */

	void editItem() {
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
			
			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Entered non integer input\n";
			}//entering non int input creates infinite loop
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

		  void inventoryMenu() {
			  int menuOption;

		//Display inventory and menu options
		cout << "Managing inventory: " << inventoryName << "\n\n";
		displayInventory();
		cout << " 1:New item | 2:Edit item | 3:Remove item | 0:Exit\n";

		//Menu Inputs
		do {
			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Entered non integer input\n";
			}
			switch (menuOption) {
			case 0:// Exit menu
				break;
			case 1:// Add inventory item
				addItem();
				system("cls");
				return inventoryMenu();
			case 2:// Edit inventory item
				if (!emptyCheck()) {
					editItem();
					system("cls");
					return inventoryMenu();
				}
				break;
			case 3:// Remove inventory item
				if (!emptyCheck()) {
					removeItem();
					system("cls");
					return inventoryMenu();
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

void runInventory(InventoryManager& inv);
void runRoster(RosterManager &roster);
void testRunRoster(RosterManager& roster);
bool adminLogin(LoginManager);
//void runEmployee(EmployeeManager& employee);
//void rosterMenu(RosterManager& roster, EmployeeManager& employees);

int main()
{
	InventoryManager test;
	test.inventoryName = "test inventory";
	RosterManager testRoster;
	LoginManager testLogin;

	InventoryManager inv;
	RosterManager ros;

	string store;
	int menuOption;
	bool loop;


	//runInventory(test);

	if (!adminLogin(testLogin)) {
		return 0;
	}
	cout << "Choose a store to manage.\n1.Auckland\n2.Wellington\n3.Christchurch\n";

	do {
		loop = false;
		while (!(cin >> menuOption)) {
			cin.clear();
			cin.ignore();
			cout << "Entered non integer input\n";
		}
		switch (menuOption) {
		case 0:
			break;
		case 1:
			store = "Auckland";
			break;
		case 2:
			store = "Wellington";
			break;
		case 3:
			store = "Christchurch";
			break;
		default:
			cout << "Invalid input";
			loop = true;
		}
	} while (loop);
	inv.inventoryName = store;
	ros.rosterName = store;
	system("cls");

	cout << "Managing store: \"" << store << "\"\n"
		<< "1.Manage Inventory\n2.Manage Roster\n3.Manage Employees\n0.Exit\n";
	/*
	* -Need to add looping
	*/
	do {
		while (!(cin >> menuOption)) {
			cin.clear();
			cin.ignore();
			cout << "Entered non integer input\n";
		}
		switch (menuOption) {
		case 0:
			break;
		case 1://Manage Inventory
			system("cls");
			runInventory(inv);
			break;
		case 2://Manage Roster
			ros.rosterMenu();
			break;
		case 3://Manage Employees
			cout << "Manage Employees non-functional.\n";
			break;
		default:
			cout << "Invalid input";
		}
	} while (menuOption != 0);
	
}

bool adminLogin(LoginManager testLogin) {
	string
		usernameInput,
		passwordInput;

	while (testLogin.noAdmins()) { 
		testLogin.createAdmin(); 
		system("cls");
	}
	for (int i = 3; i > 0; i--) {
		cout << "Input Username: ";
		getline(cin, usernameInput);
		cout << "Input Password: ";
		getline(cin, passwordInput);
		if (!testLogin.login(usernameInput, passwordInput)) {
			cout << "Invalid Username or Password.\n"<< i - 1 << " login attempts left.\n\n";
		}
		else {
			cout << "Login Success!\n";
			return true;
		}
		
	}
	cout << "To many login attempts exiting program.\n";
	return false;
}

void testRunRoster(RosterManager& roster) {
	roster.loadEmployees();
	roster.loadRoster();
	roster.rosterMenu();
	roster.saveEmployees();
	roster.saveRoster();
}

void runRoster(RosterManager& roster) {
	string name;
	int day;

	cout << "Who would you like to kill\n";
	getline(cin, name);
	cout << "And when are they working?\n";
	cin >> day;
	system("cls");
	roster.removeFromRoster(name, day);
}

void runInventory(InventoryManager& inv) {
	inv.loadInventory();
	inv.inventoryMenu();
	inv.saveInventory();//saves to UNINITIALIZED_Inventory.csv
}

/*
void rosterMenu(RosterManager& roster, EmployeeManager& employees) {
	int
		menuOption,
		dayInput;
	string employeeInput;

	roster.loadRoster();
	employees.loadEmployees();
	cout << "1: Manage Roster | 2: Manage Employees | 0: Exit\n";
	do {
		cin >> menuOption;
		switch (menuOption) {
		case 0://Exit
			break;
		case 1://Manage roster
			system("cls");
			roster.displayRoster();
			cout << "1: Add to day | 2: Remove from day | 0: Exit\n";
			do {
				cin >> menuOption;
				switch (menuOption) {
				case 0:
					break;
				case 1://Add to day
					roster.addToRoster(employeeInput,dayInput);
					break;
				case 2:
					break;
				default:
					cout << "Invalid input";
				}
			}while (menuOption != 0);
			break;
		case 2:
			break;
		default:
			cout << "Invalid input.\n";
		}
	} while (menuOption != 0);
}
*/

/*
void runEmployee(EmployeeManager& employee) {
	employee.loadEmployees();
	employee.displayList();
	//employee.saveList();
}
*/
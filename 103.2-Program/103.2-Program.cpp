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

class LoginManager {
public:
	string
		user,
		adminFile = "adminFile.csv";

	bool noAdmins()
	{
		ifstream AdminFile(adminFile);

		if (!AdminFile) createAdmin();
		return AdminFile.tellg() == 0 && AdminFile.peek() == ifstream::traits_type::eof();
	}

	bool login(string usernameInput, string passwordInput) {
		string
			validUsername,
			validPassword;
		ifstream AdminFile(adminFile);

		while (getline(AdminFile, validUsername, ',') && getline(AdminFile, validPassword)) {
			if (usernameInput == validUsername && passwordInput == validPassword) {
				AdminFile.close();
				return true;
			}
		}
		AdminFile.close();
		return false;
	}

	void createAdmin() {
		string
			input,
			usernameInput,
			passwordInput,
			passwordConfirm;
		ofstream AdminFile(adminFile, ios::app);
		cout << "Create Admin\n";
		do {
			cout << "Input Username: ";
			getline(cin, usernameInput);
			cout << "Input Password: ";
			getline(cin, passwordInput);
			cout << "Confirm Password: ";
			getline(cin, passwordConfirm);
			if (passwordConfirm != passwordInput) cout << "\nERROR! Passwords do not match.\n";
		} while (passwordInput != passwordConfirm);
		cout << "Confirm creation of User \"" << usernameInput << "\"? Y/N\n";
		do {
			getline(cin, input);
			switch (toupper(input[0])) {
			case 'Y':
				AdminFile << usernameInput << ',' << passwordConfirm << '\n';
				system("cls");
				cout << "Created User \"" << usernameInput << "\"\n";
				AdminFile.close();
				return;
			case 'N':
				cout << "Quit admin creation? Y/N\n";
				do {
					getline(cin, input);
					switch (toupper(input[0])) {
					case 'Y':
						return;
					case 'N':
						system("cls");
						return createAdmin();
					default:
						cout << "Invalid input";
					}
				} while (true);
				break;
			default:
				cout << "Invalid Input";
			}
		} while (true);

	}

	bool adminLogin() {
		string
			usernameInput,
			passwordInput;

		while (noAdmins()) {
			createAdmin();
			system("cls");
		}
		for (int i = 3; i > 0; i--) {
			cout << "Input Username: ";
			getline(cin, usernameInput);
			cout << "Input Password: ";
			getline(cin, passwordInput);
			if (!login(usernameInput, passwordInput)) {
				cout << "Invalid Username or Password.\n" << i - 1 << " login attempts left.\n\n";
			}
			else {
				system("cls");
				cout << "Login Success!\n";
				user = usernameInput;
				return true;
			}

		}
		cout << "To many login attempts exiting program.\n";
		return false;
	}
};

//Old Employee Manager
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

//Old Roster Manager
/*
class RosterManager {
public:
	string 
		rosterName,
		rosterFileName = rosterName + "-Roster.csv",
		employeesFileName = rosterName + "-EmployeeList.csv";

	struct {
		string day[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
		
		list<string> employeeList[7];
	} roster;

	list<string> employeeNames; //= { "Johnny","Joey","Jeremy","Jamie","Jackie","Jeffrey" };

	void displayEmployeeList() {
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
		}

		RosterFile.close();
		cout << "Roster has been saved to \"" << rosterFileName << "\".";
	}

	void rosterMenu() {

	}
};//End of RosterManager
*/

class RosterManager {
public:
	string
		rosterName,
		rosterFileName = "-Roster.csv",
		employeesFileName = "-EmployeeList.csv";

	struct {
		string day[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

		list<string> employeeList[7];
	} roster;

	list<string> employeeNames; //= { "Johnny","Joey","Jeremy","Jamie","Jackie","Jeffrey" };

	void displayEmployeeList() {
		cout << "Employees:\n  |";
		for (string employeeName : employeeNames) {
			cout << " " << employeeName << " |";
		}
		cout << "\n\n";
	}

	void addEmployee(string employeeName) {
		//cout << "Enter the name of the employee to add";
		//getline(cin, employeeName);
		if (find(employeeNames.begin(), employeeNames.end(), employeeName) != employeeNames.end()) {

			cout << "Employee \"" << employeeName << "\" already exists in the list.\n";
			return;
		}
		employeeNames.push_back(employeeName);
		cout << "Employee \"" << employeeName << "\" has been added to system.\n";
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
		ofstream EmployeeFile(rosterName + employeesFileName);

		if (!EmployeeFile) {
			cout << "Error opening file for saving.\n";
			return;
		}

		// writes employee name to file from employee list
		for (const string& employeeName : employeeNames) {
			EmployeeFile << employeeName << "\n";
		}

		EmployeeFile.close();
		cout << "Employee list has been saved to \"" << rosterName + employeesFileName << "\"\n";
	}

	void loadEmployees() {
		ifstream EmployeeFile(rosterName + employeesFileName);

		if (!EmployeeFile) {
			if (!EmployeeFile) {
				cout << "ERROR! An error occured when loading \"" << rosterName + employeesFileName << "\".\n";
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
		cout << "Employee list loaded from \"" << rosterName + employeesFileName << "\"\n";
	}

	// menu for managing employees
	void employeeMenu() {
		int menuOption;
		string employeeName;

		do {
			// display employee list
			cout << "\n";
			displayEmployeeList();

			// displays menu options
			cout << "Employee Management Menu:\n";
			cout << "1. Add new employee\n";
			cout << "2. Remove employee\n";
			cout << "\n0. Back\n";
			//cout << "3. Display employee list\n";
			//cout << "Enter your choice: ";

			// fet user input
			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Entered non integer input\n";
			}
			switch (menuOption) {
			case 0: // goes back to menu
				cout << "Returning to main menu.\n";
				break;
			case 1: // adds new employee
				cout << "Enter new employee name: ";
				cin.ignore();
				getline(cin, employeeName);
				system("cls");
				addEmployee(employeeName);
				//cout << "Employee \"" << employeeName << "\" has been added to system.\n";
				break;

			case 2: // Remove employee
				cout << "Enter employee name to remove: ";
				cin.ignore();
				getline(cin, employeeName);
				system("cls");
				removeEmployee(employeeName);
				//cout << "Employee removed from system.\n";
				break;

				//unnecessary due to normaly displaying employee list before the menu
				//case 3: // displays employee list
				//	displayEmployeeList();
				//	break;

			default:
				cout << "Invalid option. Please try again.\n";
			}

		} while (menuOption != 0);
	}

	//Roster stuff begin

	void displayRoster() {
		for (int i = 0; i < 7; i++) {
			cout << roster.day[i] << ": ";
			if (roster.employeeList[i].empty()) {
				cout << "No employees asigned to this day";
			}
			else {
				for (string j : roster.employeeList[i]) {
					cout << j << ", ";
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
		ifstream RosterFile(rosterName + rosterFileName);

		string input;

		if (!RosterFile) {
			cout << "ERROR! An error occured when loading \"" << rosterName + rosterFileName << "\".\n";
			return;
		}
		for (int i = 0; i < 7; i++) {
			while (getline(RosterFile, input, ',')) {
				if (input == "\n") break; //Jank fix for loading
				roster.employeeList[i].push_back(input);
			}
		}

		RosterFile.close();
		cout << "Roster has been loaded from \"" << rosterName + rosterFileName << "\"\n";
	}

	void saveRoster() {
		ofstream RosterFile(rosterName + rosterFileName);

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
		}

		RosterFile.close();
		cout << "Roster has been saved to \"" << rosterName + rosterFileName << "\".";
	}

	// menu for managing roster
	void rosterMenu() {
		int 
			menuOption,
			dayIndex = -1;
		string 
			employeeName,
			dayName;

		do {
			displayRoster();
			displayEmployeeList();

			// displays menu for roster
			//cout << "\n| Roster Management Menu |\n";
			cout << "1. Add employee to roster\n";
			cout << "2. Remove employee from roster\n\n";
			//cout << "3. Display current roster\n";
			cout << "0. Go Back\n";
			//cout << "Enter your choice: "; This is never used elsewhere so it is removed to remove screen clutter

			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Entered non integer input\n";
			}
			cin.ignore();//Clears input buffer

			switch (menuOption) {
			case 0: // goes back
				cout << "Returning to menu.\n";
				break;
			case 1: // adds employee to roster
				cout << "Enter employee name: ";
				getline(cin, employeeName);

				// Check if employee exists in employee list
				if (find(employeeNames.begin(), employeeNames.end(), employeeName) == employeeNames.end()) {
					cout << "Employee \"" << employeeName << "\" does not exist in the employee list.\n";
					break;
				}

				//cout << "Enter day (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday): ";
				cout << "Enter day: "; //Cleaner UI look
				//cin.ignore(); This was causing the first letter of the day input to be removed
				getline(cin, dayName);

				//Sets day input to apropriate case
				transform(dayName.begin(), dayName.end(), dayName.begin(), ::tolower);
				dayName[0] = toupper(dayName[0]);

				// see if day input is valid then add employee to day
				for (int i = 0; i < 7; i++) {
					if (roster.day[i] == dayName) {
						//dayIndex = i;
						//See if employee is working on day
						if (find(roster.employeeList[i].begin(), roster.employeeList[i].end(), employeeName) == roster.employeeList[i].end()) {
							addToRoster(employeeName, i);
							cout << "Employee \"" << employeeName << "\" added to " << roster.day[i] << ".\n";
						}
						else {
							cout << "ERROR! \"" << employeeName << "\" is alread assigned to " << roster.day[i] << ".\n";
						}
						break;
					}
					if (i == 6) cout << "Invalid day input";
				}
				//if (dayIndex < 0) cout << "Invalid day name. Please enter a valid day of the week.\n";
			break;

			case 2: // removes employee from roster
				cout << "Enter employee name: ";
				getline(cin, employeeName);

				// Check if employee exists in employee list
				if (find(employeeNames.begin(), employeeNames.end(), employeeName) == employeeNames.end()) {
					cout << "Employee \"" << employeeName << "\" does not exist in the employee list.\n";
					break;
				}

				//cout << "Enter day (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday): ";
				cout << "Enter day: "; //Cleaner UI look
				//cin.ignore(); This was causing the first letter of the day input to be removed
				getline(cin, dayName);

				//Sets day input to apropriate case
				transform(dayName.begin(), dayName.end(), dayName.begin(), ::tolower);
				dayName[0] = toupper(dayName[0]);

				// see if day input is valid then add employee to day
				for (int i = 0; i < 7; i++) {
					if (roster.day[i] == dayName) {
						//dayIndex = i;
						//See if employee is working on day
						if (find(roster.employeeList[i].begin(), roster.employeeList[i].end(), employeeName) == roster.employeeList[i].end()) {
							cout << "ERROR! \"" << employeeName << "\" is not assigned to " << roster.day[i] << ".\n";
						}
						else {
							removeFromRoster(employeeName, i);
							cout << "Employee \"" << employeeName << "\" removed from " << roster.day[i] << ".\n";
						}
						break;
					}
					if (i == 6) cout << "Invalid day input";
				}
				break;

			case 5: // old remove employee
				cout << "Enter employee name to remove: ";
				//cin.ignore();
				getline(cin, employeeName);
				cout << "Enter day (Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday): ";
				getline(cin, dayName);
				transform(dayName.begin(), dayName.end(), dayName.begin(), ::tolower);
				dayName[0] = toupper(dayName[0]);
				// Convert day name to index
				for (int i = 0; i < 7; i++) {
					if (roster.day[i] == dayName) {
						dayIndex = i;
						removeFromRoster(employeeName, dayIndex);
						cout << "Employee removed from roster.\n";
						break;
					}
				}
				if (dayIndex < 0) cout << "Invalid day name. Please enter a valid day of the week.\n";
			break;

			//case 3: // displays roster
			//	displayRoster();
			//	break;

			default:
				cout << "Invalid option. Please try again.\n";
			}

			
			// Wait for user to see messages before continuing
			if (menuOption != 0) {
				cout << "\nPress Enter to continue...";
				cin.get();
				system("cls");
			}
		} while (menuOption != 0);
	}

	
};//End of RosterManager

class InventoryManager {
public:
	string 
		inventoryName = "UNINITIALIZED",
		inventoryFileExtension = "_Inventory.csv";

	struct Item{
		string
			name;
		int
			quantity;
		double
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
			cout << setfill(' ') << "$" << fixed << setprecision(2) << left << i.price;
			
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
		
		cout << "Inventory has been saved to \"" + inventoryName + inventoryFileExtension << "\"\n";
	}

	void loadInventory() {
		ifstream InventoryFile(inventoryName + inventoryFileExtension);
		if (!InventoryFile) {
			cout << "ERROR! An error occured when loading \"" << inventoryName + inventoryFileExtension << "\".\n";
			return;
		}
		list.clear(); // clears the current inventory
		string name;
		int quantity;
		double price;
		char comma;

		while (InventoryFile >> ws && getline(InventoryFile, name, ',')) {
			InventoryFile >> quantity >> comma >> price;
			list.push_back({ name, quantity, price });
			InventoryFile.ignore(); // skips the newline
		}

		InventoryFile.close();
		cout << "Inventory has been loaded from \"" << inventoryName + inventoryFileExtension << "\"\n";
	}

	//Creates a new inventory listing
	void addItem(){
		string
			newName;
		int
			newQuantity;
		double
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
			while (!(cin >> newQuantity)){
				cin.clear();
				cin.ignore();
				cout << "Invalid input\n";
			}
			if (newQuantity < 0) {
				cout << "Quantity has to be positive.\n";
				//return;
			}
		} while (newQuantity < 0);

		cin.ignore(1000, '\n');//If user enters a decimal point when inputing newQuantity this clears the input from after the decimal point

		cout << "Input price:\n$";
		do {
			while (!(cin >> newPrice)) {
			cin.clear();
			cin.ignore();
			cout << "Invalid input\n";
		}
			
			if (newPrice < 0) {
				cout << "Price has to be positive.\n";
				//return;
			}
			newPrice = roundNumber(newPrice);
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
	//rounds input number to 2 decimal places
	double roundNumber(double value) {
		double scale = 0.01;

		value = (int)(value / scale) * scale;
		return value;
	}

	void editItem() {
		string desiredItem,
			input,
			newName;
		Item* selectedItem = &list[0];
		int 
			newQuantity,
			menuOption;
		double
			newPrice;

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
			cout << " 1:Change Name | 2:Add Quantity | 3:Remove Quantity | 4:Change Price | 0:Return\n";
			
			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Invalid input\n";
			}//entering non int input creates infinite loop
			switch (menuOption) {
			case 0:// Exit menu
				break;

			case 1: //edit name
				cout << "Enter new name for \"" << (*selectedItem).name << "\" or leave empty to keep name\n";
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
					newPrice = stod(input);
					system("cls");
					if (newPrice >= 0) {

						newPrice = roundNumber(newPrice);
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
			cout << "Remove \"" << selectedItem->name << "\" from inventory.\nAre you sure? y/n\n";
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
		cout << " 1:New item | 2:Edit item | 3:Remove item | 0:Back\n";

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

	//Non Functional
	void buyItem() {
		string
			confirm,
			desiredItem,
			input,
			newName;
		Item* selectedItem = &list[0];
		int
			newQuantity,
			menuOption;

		cout << "Purchasing from \"" << inventoryName << "\"\n";
		displayInventory();
		cout << "Enter the name of an item to purchase?\n0: Exit\n";
		getline(cin, desiredItem);
		if (desiredItem == "0") return;
		if (findItem(selectedItem, desiredItem)) {

			//cout << "Purchasing \"" << (*selectedItem).name << "\"\nQuantity:" << (*selectedItem).quantity << "\nPrice; $" << (*selectedItem).price << endl;
			cout << "How many \"" << (*selectedItem).name << "\" do you wish to purchase?\n0: Cancel\n";

			do {
				while (!(cin >> newQuantity)) {
					cin.clear();
					cin.ignore();
					cout << "Entered non integer input\n";
				}
				cin.ignore();//Clearing buffer for later cin and getline commands

				if (newQuantity == 0) {
					//cin.ignore();
					system("cls");
					return buyItem();
				}
				if (newQuantity < 1) cout << "ERROR! Cannot purchase less than 1 unit\n";
				if ((*selectedItem).quantity - newQuantity < 0) cout << "ERROR! Not enough items in stock. (In stock: " << (*selectedItem).quantity << ")\n";
			} while (newQuantity < 1 || (*selectedItem).quantity - newQuantity < 0);

			cout << "price is $" << (*selectedItem).price * (newQuantity) << "purchase(y/n)\n";
			do {
				getline(cin, confirm);
				switch (confirm[0]) {
				case 'Y':
				case 'y':
					system("cls");
					cout << "Purchase successful!\n";
					(*selectedItem).quantity -= newQuantity;
					return buyItem();
				case 'N':
				case 'n':
					system("cls");
					return buyItem();
				default:
					cout << "invalid input";
					//return buyItem();
				}
			} while (!(confirm[0] == 'y' || confirm[0] == 'Y'));
		}
	}

	//Old buyItem
	/*
	void buyItem() {
		string
			desiredItem,
			input,
			newName;
		Item* selectedItem = &list[0];
		int
			newQuantity,
			menuOption,
			Purchase;

		cout << "what item do you wish to purchase? \n";
		getline(cin, desiredItem);
		if (findItem(selectedItem, desiredItem)) {
			cout << "purchasing " << (*selectedItem).name << "\nQuantity:" << (*selectedItem).quantity << "\nPrice; $" << (*selectedItem).price << endl;
			cout << "how many" << (*selectedItem).name << "do you wish to purchase?\n";
			cin >> input;
			newQuantity = stoi(input);
			if (newQuantity > 0) {
				if ((*selectedItem).quantity - newQuantity < 0) {
					cout << "Error not enough items in stock for purchase\n";
				}
				else {
					cout << "price is $" << (*selectedItem).price * (newQuantity) << "purchase(y/n)\n";
					cin >> Purchase;
					switch (Purchase) {
					case 'Y':
					case 'y':
						cout << "purchase successful\n";
						(*selectedItem).quantity -= newQuantity;
					case 'N':
					case 'n':
						system("cls");
						return buyItem();
					default:
						cout << "invalid input";
						return buyItem();

					}
				}
			}
		}
	}
	*/
};//Class InventoryManager end

//void runInventory(InventoryManager& inv);
//bool adminLogin(LoginManager);
void runAdmin(InventoryManager&, RosterManager&);
void purchase(InventoryManager&);
//void runEmployee(EmployeeManager& employee);
//void rosterMenu(RosterManager& roster, EmployeeManager& employees);

//Testing stuff
//InventoryManager test;
//test.inventoryName = "test inventory";
//RosterManager testRoster;

InventoryManager inv;
RosterManager ros;

/*
* TO-DO!
* -Roster menu is fucked
* -Add looping to buyItem(); -Done
* -Display Employee list when editing roster
* -Find more problems
*/
int main()
{
	int menuOption;

	cout << "Run as Admin or Customer.\n  1.Admin  |  2. Customer  |  0.Exit\n";
	do {
		while (!(cin >> menuOption)) {
			cin.clear();
			cin.ignore();
			cout << "Entered non integer input\n";
		}
		cin.ignore();//To clear buffer for later inputs
		switch (menuOption) {
		case 0:
			return 0;
		case 1:
			system("cls");
			runAdmin(inv, ros);
			system("cls");
			return main();
		case 2:
			system("cls");
			purchase(inv);
			//system("cls");
			return main();
		default:
			cout << "Invalid input.\n";
		}
	} while (menuOption != 0);
	
}

void purchase(InventoryManager& inv) {
	int menuOption;
	string store;

	cout << "Chose a store to purchase from.\n  1.Auckland\n  2.Wellington\n  3.Christchurch\n";

	do {
		while (!(cin >> menuOption)) {
			cin.clear();
			cin.ignore();
			cout << "Entered non integer input\n";
		}
		cin.ignore();//Fucking buffer BS
		switch (menuOption) {
		case 0:
			return;
		case 1://Set store to Auckland
			store = "Auckland";
			break;
		case 2://Set store to Wellington
			store = "Wellington";
			break;
		case 3://Set store to Christchurch
			store = "Christchurch";
			break;
		default:
			cout << "Invalid input\n";
		}
	} while (!(menuOption > 0 && menuOption < 4));
	inv.inventoryName = store;
	inv.loadInventory();
	system("cls");//Clear inventory load message as this is not relevant for the customer
	if (inv.emptyCheck()) return; // Fix for crashing when inventory file doesn't exits. This was an after last minute fix so it's not ideal
	inv.buyItem();
	inv.saveInventory();
	system("cls");
}

void runAdmin(InventoryManager&inv, RosterManager&ros) {
	LoginManager loginManager;
	string store;
	int menuOption;
	//bool logedIn;

	if (!loginManager.adminLogin()) {
		return;
	}

	do {
		cout << "Logged in as: " << loginManager.user << "\n";
		cout << "\nManage store:\n1.Auckland\n2.Wellington\n3.Christchurch\n"
			"\nOther options:\n4.Create new admin user\n0.Logout\n";

		do {
			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Entered non integer input\n";
			}
			switch (menuOption) {
			case 0:
				return;
			case 1://Set store to Auckland
				store = "Auckland";
				break;
			case 2://Set store to Wellington
				store = "Wellington";
				break;
			case 3://Set store to Christchurch
				store = "Christchurch";
				break;
			case 4://Create new Admin
				cin.ignore();
				loginManager.createAdmin();
				break;
			default:
				cout << "Invalid input\n";
			}
		} while (!(menuOption > 0 && menuOption < 4));
		inv.inventoryName = store;
		ros.rosterName = store;
		system("cls");

		//Loading essentials into memory
		inv.loadInventory();
		ros.loadRoster();
		ros.loadEmployees();

		cout << "\nManaging store: \"" << store << "\"\n\n"
			<< "1.Manage Inventory\n2.Manage Roster\n3.Manage Employees\n\n0.Back\n";
		do {
			while (!(cin >> menuOption)) {
				cin.clear();
				cin.ignore();
				cout << "Entered non integer input\n";
			}
			switch (menuOption) {
			case 0://Exit
				system("cls");
				break;
			case 1://Manage Inventory
				system("cls");
				//inv.loadInventory();
				inv.inventoryMenu();
				system("cls");
				inv.saveInventory();
				//Throwing the menu display here because it is the easiest way to do what I wan't
				cout << "\nManaging store: \"" << store << "\"\n\n"
					<< "1.Manage Inventory\n2.Manage Roster\n3.Manage Employees\n\n0.Back\n";
				break;
			case 2://Manage Roster
				system("cls");
				//ros.loadRoster();
				ros.rosterMenu();
				system("cls");
				ros.saveRoster();
				cout << "\nManaging store: \"" << store << "\"\n\n"
					<< "1.Manage Inventory\n2.Manage Roster\n3.Manage Employees\n\n0.Back\n";
				break;
			case 3://Manage Employees
				system("cls");
				//ros.loadEmployees();
				ros.employeeMenu();
				system("cls");
				ros.saveEmployees();
				cout << "\nManaging store: \"" << store << "\"\n\n"
					<< "1.Manage Inventory\n2.Manage Roster\n3.Manage Employees\n\n0.Back\n";
				break;
			default:
				cout << "Invalid input";
			}
		} while (menuOption != 0);
	} while (true);
}


/*
void runInventory(InventoryManager& inv) {
	inv.loadInventory();
	inv.inventoryMenu();
	inv.saveInventory();
}
*/

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
README for:
103.2 Intergrated Studio I - Group Project
Group Members:
	Christopher Kelly
	Feilx Bryant
	Warner Nash
-------------------------------------------
Aotearoa Treasures’ inventory management system

What it does:
Allows store owners and other admins to manage the Aotearoa Treasures’ stores remotely
Allows easy management of the inventory, employee list and weekly employee roster.
Also allows customers to access these stores and make purchases but perform no other actions.

How to use:
When starting the program you will be prompted to run as Admin, run as Customer or Exit.
Input the number corresponding to the option you would like to chose (displayed next to the option) then press the enter/return key to submit your choice.
All options for this program are accepted in this or simillar way.

When Running as Admin:
	If there is no admin account avaliable then you will be prompted to create one. Follow the instructions on screen to create an admin account.
		(You cannot perform admin functionality without an admin account.)
	Once there is an admin accout or an admin account already exists you will be prompted for a username and password.
	Enter the correct username and password to access the admin control panel.
	If you enter the incorrect username or password 3 times you will be booted out of the admin login and need to try again.
	If you cannot log in even with the correct username and password this is likely due to a corrupted admin login file.
		To fix this problem, delete the file "adminFile" from this programs folder. 
		This will delete all saved admin logins (Including the corrupted ones) and you will need to recreate them.

	After successfull login you will need to select the store to manage.
	All relevant files will be loaded (If they exist) and there will be messages at the top of the console reporting if the files were successfully loaded or not.
	If this is the first time you are managing this store the relevant files will not exist and the program will report that there was a problem loading the files.
	This will not affect your ability to use the program and you will still be allowed to input and modify information.
	After you input data a file will be created and any informaiton you have input will be saved and can be loaded later.

	Managing Inventory:
	When modifying the inventory all inventory items will be displayed with the quantity of the item to the left, Name of the item in the middle and price of the 
	item on the left. 
	If there is an item with a quantity of less than five a warning icon  [!]  Will apear next to the item to alert the user.
	
	To create a new item listing select "1: New item". You will be propted for an item name, input the quantity of item and then the price of the item.
		You cannot create a new item listing for an item that already exists.
	
	To edit an existing item listing select "2:Edit item". 
	This will allow you to modify the name, add or remove quantity and change the price of an item.
	You will be requred to input the name of the item you wish to edit.
	If the item you are looking for could not be found you will be re prompted for the item you wish to edit.
	If the item you are looking for is found you will enter a new menu allowing you to chose how to edit the item

	To Delete an item listing select "3:Remove item"
	This will completely delete the item and all relevant data from the inventory system. 
	THIS ACTION IS NOT REVERSEABLE!
	When deleting an item you will be prompted for the name of an item just as when editing an item and then confirm the deletion.
	
	Managing Roster:
	When modifying the roster the days will be listed in decending order and any employee working on that day will be listed to the right with a list of avaliable 
	employees listed after the roster.
	You cannot create employees to add to the roster in this menu.
	
	Option 1. Add employee to roster
	When adding an employee to the roster you must input the employees name (Note that this is case sensitive)
	If an employee is not found a message will display at the bottom of the console and the user must press enter then select to add employee again
	If a valid employee is found you must input which day to add them to. You cannot have the same employee working twice on one day. 
	You can have all the employees working on the same day

	Option 2. Remove employee from roster
	Removing an employee from the roster removes an employee from a day they are assigned to.
	Input the employee's name (Case sensitive) and then input the day you wish to remove them from.

	Managin Employees:
	You can create a new employee listing or remove an employee listing.
	
	Option 1. Add new employee
	This creates a new employee listing that can then be assigned to a day in the roster menu
	Input the employees name (This will be case sensitive)
	
	Option 2. Remove employee
	This removes an employee for the list of avaliable employees but does not remove them from the days the are listed as working on.
	To remove an employee listing input the employees name (This is case sensitive).

	
	Create new admin user:
	This creates a new admin username and password to login to the admin pannel and operates exactly the same as when you first created an admin login when first booting
	this program.

When Running as customer:
	When running as a customer you will be prompted to select a store to purchase from
	If the store has no items in inventory you will not be able to load that inventory at all.
	When you have succesfully selected a store you will be shown a list of items to purchase from that store.
	Enter the name of the item you wish to purchase and select how manu of the item you wish to purchase.
	If you try to purchase more of an item than there is stock of it you will not be able to and be requred to enter a quantity less that the quantity that is in stock.
	After inputing a valid quantity to purchase you will be required to confirm your purchase.
	After confirming your purchase the relvant items will have its quantity reduced by the ammount that was purchased.
	

File Names and File name conventions:
adminFile.csv - Contains the login information for admins. Deleting this will remove all admin logins and you will need to create a new admin login to 
		access the admin functionality
Inventory, roster and employee listing files will be saved with a prefix being the name of the store followed by a sufix indicating which sort of file it is
e.g. "Auckland-EmployeeList" is the file that contains the list of employees for the Auckland store

Suffixes
(STORENAME)_Inventory.csv - Contains the list of items for a stores inventory listed in order "Item name, Item quantity, Item price".
Deleting this file will delete the relevant stores inventory.

(STORENAME)-EmployeeList.csv - Contains the list of employees that work at that specific store 
Deleting this file will delete the relevant stores employee list

(STORENAME)-Roster.csv - Contains the weekly roster for each store. This may contain employees that where removed from the employee list
Deleting this file will delete the relevant stores weekly roster

(STORENAME)_Log.txt - An unfinished feature that logs changes done to an inventory. 
This feature was not finished and as such is not a complete or accurate log of the inventory.
Deleting this file does not affect the program.
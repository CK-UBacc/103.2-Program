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
Input the number corresponding to the option you would like to chose as displayed in the console window then press the enter/return key
All options for this program are accepted in this or simillar way.

When Running as Admin:
	If there is no admin account avaliable then you will be prompted to create one. Follow the instructions on screen to create an admin account.
		You cannot perform admin functionality without an admin account.
	Once there is an admin accout or an admin account already exists you will be prompted for a username and password.
	Enter the correct username and password to access the admin control panel.
	If you enter the incorrect username or password 3 times you will be booted out of the admin login and need to try again.
	If you cannot log in even with the correct username and password this is likely due to a corrupted admin login file.
		To fix this problem, delete the file "adminFile" from this programs folder. 
		This will delete all saved admin logins (Including the corrupted ones) and you will need to recreate them.

After successfull login you will need to select the store to manage.
	All relevant files will be loaded (If they exist) and there will be messages at the top of the console reporting if the files were successfully loaded or not.
	If the relevant file does not exist then the program will create it when apropriate.

When Running as customer:


File Names and File name conventions:

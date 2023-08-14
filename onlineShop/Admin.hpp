#include <fstream>
#include <iostream>
#include <string>

#include "ShopSystem.hpp"

//ADMIN PRIVILEGES

namespace Admin {
	bool checkLogin(User* current, string password) 
	{
		if (current->getUsername() == "Admin" && current->loginCheck(password))
			return true;
		return false;
	}

	void printMiscs(int& choice)
	{
		cout << "1. Add Products" << endl;
		cout << "2. Add Users" << endl;
		cout << "3. View Products" << endl;
		cout << "4. View Users" << endl;
		cout << "5. Logout" << endl;
		cout << "6. Exit" << endl;
		cin >> choice;
	}

	void addProducts(ShopSystem& shop)
	{
		fstream fprod("products.txt", ios::app | ios::ate);
		if (!fprod) {
			cerr << "Couldn't open file | File doesn't exist" << endl;
			exit(1);
		}
		shop.viewProducts();
		string name;
		double price{};
		int num{};
		cout << "Enter product name: ";
		cin.ignore(100, '\n') >> name;
		cout << "Enter price: ";
		cin >> price;
		cout << "Enter quantity: ";
		cin >> num;
		fprod << endl
			<< name << '\t'
			<< price << '\t'
			<< num;
		fprod.close();
		shop.addProduct(name, price, num);
	}

	void addUsers(ShopSystem& shop)
	{
		fstream fuser("users.txt", ios::app | ios::ate);
		if (!fuser) {
			cerr << "Couldn't open file | File doesn't exist" << endl;
			exit(1);
		}
		string name;
		string pass;
		cout << "Enter Username: ";
		cin.ignore(100, '\n') >> name;
		cout << "Enter Password: ";
		cin.ignore(100, '\n') >> pass;
		fuser << endl
			<< name << '\t'
			<< pass;
		fuser.close();
		shop.addUser(name, pass);
	}

	void checkChoice(ShopSystem& shopSys, int choice, User* user) {
		system("cls");
		switch (choice) {
		case 1:
			addProducts(shopSys);
			break;
		case 2:
			addUsers(shopSys);
			break;
		case 3:
			shopSys.viewProducts();
			break;
		case 4:
			shopSys.viewUsers();
			break;
		case 5:
			break;
		case 6:
			exit(0);
			break;
		default:
			exit(2);
		}
	}
};
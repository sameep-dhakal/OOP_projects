#include "ShopSystem.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>

//USER PRIVILEGES

namespace Misc {
	void printUser(string user) {
		cout << setfill('/') << setw(50) << "" << endl;
		cout << setfill(' ');
		cout << "User: " << setw(20) << left << user << endl;
		cout << setfill('/') << setw(50) << "" << endl;
		cout << setfill(' ') << endl;
	}
	void userIP(ShopSystem& shop)
	{
		string name;
		string password;
		fstream fuser{ "users.txt", ios::in };
		if (!fuser) {
			cerr << "Couldn't open file | Couldn't find file : users.txt" << endl;
			exit(1);
		}

		while (!fuser.eof()) {
			fuser >> name
				>> password;
			shop.addUser(name, password);
		}
		fuser.close();
	}

	void productIP(ShopSystem& shop)
	{
		string name;
		double price{ 0 };
		int quantity{ 0 };
		fstream fprod{ "products.txt", ios::in };
		if (!fprod) {
			cerr << "Couldn't open file | Couldn't find file : products.txt" << endl;
			exit(1);
		}

		while (!fprod.eof()) {
			fprod >> name
				>> price
				>> quantity;
			shop.addProduct(name, price, quantity);
		}
		fprod.close();
	}

	void printMiscs(int& choice)
	{
		cout << "1. Browse" << endl;
		cout << "2. View Cart" << endl;
		cout << "3. Remove from Cart" << endl;
		cout << "4. Logout" << endl;
		cout << "5. Exit" << endl;
		cin >> choice;
	}

	void inputProducts(ShopSystem& shop, User* current)
	{
		string prodName;
		double price{};
		int quantity{};
		cout << "Product Name: ";
		cin >> prodName;
		cout << "Quantity: ";
		cin >> quantity;
		if (shop.findProduct(prodName) == nullptr) {
			std::cout << "Couldn't find product" << endl;
			return;
		}
		price = shop.findProduct(prodName)->getPrice();
		Product temp{ prodName, price, quantity };
		current->addToCart(temp);
	}

	void removeProducts(ShopSystem& shop, User* current)
	{
		string prodName;
		int quantity{};
		cout << "Product Name: ";
		cin >> prodName;
		if (shop.findProduct(prodName) == nullptr) {
			std::cout << "Couldn't find product" << endl;
		}
		else {
			cout << "Remove all?[0 if all]: ";
			cin >> quantity;
			current->removeFromCart(prodName, quantity);
		}
	}

	void checkChoice(ShopSystem& shop, int choice, User* current)
	{
		system("cls");
		switch (choice) {
		case 1:
			printUser(current->getUsername());
			shop.viewProducts();
			inputProducts(shop, current);
			system("cls");
			break;
		case 2:
			printUser(current->getUsername());
			current->viewCart();
			break;
		case 3:
			printUser(current->getUsername());
			current->viewCart();
			removeProducts(shop, current);
			system("cls");
			break;
		case 4:
			break;
		case 5:
			exit(0);
			break;
		default:
			exit(2);
		}
	}
};
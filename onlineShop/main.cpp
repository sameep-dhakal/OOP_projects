#include <fstream>
#include <Windows.h>

#include "Product.hpp"
#include "Cart.hpp"
#include "User.hpp"
#include "ShopSystem.hpp"
#include "Misc.hpp"
#include "Admin.hpp"

int main()
{
	ShopSystem shopSys;

	Misc::userIP(shopSys);
	Misc::productIP(shopSys);

	string username;
	string password;


	int choice{ 0 };
	int tries{ 0 };

	User* currentUser{ nullptr };
reset:

	choice = 1;

	while (true) {
		system("cls");
		cout << "Username: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;

		currentUser = shopSys.findUser(username, password);

		if (currentUser == nullptr) {
			system("cls");
			cerr << "Username or Password is incorrect" << endl;
			Sleep(1000);
			if (tries == 3) {
				cerr << "Wrong logins too many times\nProgram has exited" << endl;
				exit(-1);
			}
		}
		else {
			break;
		}
		++tries;
	}
	system("cls");

	if (!(Admin::checkLogin(currentUser, password)))
	{
		while (choice < 4) {
			Misc::printUser(username);
			Misc::printMiscs(choice);
			Misc::checkChoice(shopSys, choice, currentUser);
		}
		if (choice == 4) {
			goto reset;
		}
	}
	else {
		while (choice < 5) {
			Misc::printUser(username);
			Admin::printMiscs(choice);
			Admin::checkChoice(shopSys, choice, currentUser);
		}
		if (choice == 5) {
			goto reset;
		}
	}
	return 0;
}


#ifndef _SHOPSYS_HPP_
#define _SHOPSYS_HPP_

#include "Product.hpp"
#include "Cart.hpp"
#include "User.hpp"

class ShopSystem {
private:
	vector<User> users;
	vector<Product> products;
public:
	void addUser(string, string);
	void addProduct(string, double, int);
	void removeUser(string);
	void removeProduct(string);
	void viewProducts();
	void viewUsers();
	User* findUser(const string, const string);
	Product* findProduct(string);
};

#endif _SHOPSYS_HPP_


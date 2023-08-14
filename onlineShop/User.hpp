
#ifndef _USER_HPP_
#define _USER_HPP_

#include "Product.hpp"
#include "Cart.hpp"

class User {
private:
	string username;
	string password;
	Cart cart;
public:
	User(string, string);
	~User();
	string getUsername() const;
	bool loginCheck(const string);
	void addToCart(Product);
	void removeFromCart(string, int num = 0);
	double checkout();
	void viewCart();
};

#endif _USER_HPP_

#ifndef _PRODUCT_HPP_
#define _PRODUCT_HPP_

#include <iostream>
using namespace std;

class Product
{
private:
	string name;
	double price;
	int quantity;
public:
	Product(string, double, int);
	~Product();
	string getName();
	double getPrice();
	int getQuantity();
	void setQuantity(int);
};

#endif _PRODUCT_HPP_


#include "Product.hpp"

Product::Product(string p_name, double p_price, int p_quantity)
	:name(p_name), price(p_price), quantity(p_quantity)
{}

Product::~Product()
{}

string Product::getName()
{
	return name;
}

double Product::getPrice()
{
	return price;
}

int Product::getQuantity()
{
	return quantity;
}

void Product::setQuantity(int num)
{
	quantity -= num;
}
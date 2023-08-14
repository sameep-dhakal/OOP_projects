#include "Cart.hpp"

void Cart::addToCart(Product product) {
	items.push_back(product);
}

void Cart::removeFromCart(string productName, int num) {
	int index{ 0 };
	for (Product product : items) {
		if (productName == product.getName()) {
			if (!num) {
				items.erase(items.begin() + index);
			}
			else if (num >= product.getQuantity()) {
				items.erase(items.begin() + index);
			}
			else {
				product.setQuantity(num);
			}
		}
		index++;
	}
}

double Cart::getTotal() {
	double total{ 0.0 };
	for (Product product : items) {
		total += product.getPrice() * product.getQuantity();
	}
	return total;
}
void Cart::displayCart() {
	cout << setw(30) << left << "Product"
		<< setw(10) << "Price"
		<< setw(10) << "Quantity" << endl;
	cout << setfill('-') << setw(50) << "" << endl;
	cout << setfill(' ');
	for (Product product : items) {
		cout << setw(30) << product.getName() 
			<< setw(10) << product.getPrice()
			<< setw(10) << product.getQuantity() << endl;
	}
	cout << setfill('-') << setw(50) << "" << endl;
	cout << setfill(' ');
	cout << setw(40) << left << "Total"
		<< setw(10) << getTotal() << endl;
	cout << setfill('-') << setw(50) << "" << endl;
	cout << setfill(' ');
}
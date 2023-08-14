#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> // Include the fstream header
using namespace std;

class item {
public:
    string name;
    double price;
    int quantity;

    item() : name(""), price(0.0), quantity(0) {}

    item(string name, double price, int quantity) : name(name), price(price), quantity(quantity) {}

    double returntotal() const {
        return price * quantity;
    }

    void display() const {
        cout << setw(20) << left << name << setw(10) << price << setw(10) << quantity << setw(10) << returntotal() << endl;
    }
};

class supermarket {
private:
    static const int max = 5;
    item itemss[max];
    int item_no;

public:
    supermarket() : item_no(0) {}

    void add(const string& name, double price, int quantity) {
        if (item_no < max) {
            itemss[item_no] = item(name, price, quantity);
            item_no++;
        } else {
            cout << "The Bill is full" << endl;
        }
    }

    double returntotal() const {
        double total = 0.0;
        for (int i = 0; i < item_no; i++) {
            total = total + itemss[i].returntotal();
        }
        return total;
    }

    void displaybill() const {
        fstream file;
        file.open("supermarket.txt", ios::out); // Open the file in append mode
        if (!file) {
            cout << "Error: Unable to open the file." << endl;
            exit(0);
        } else {
            cout << setw(30) << "SUPERMARKET BILL" << endl;
            cout << setw(20) << left << "Item name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Total" << endl;
            file << setw(30) << "SUPERMARKET BILL" << endl;
            file << setw(20) << left << "Item name" << setw(10) << "Price" << setw(10) << "Quantity" << setw(10) << "Total" << endl;

            for (int i = 0; i < item_no; i++) {
                itemss[i].display();
                file << setw(20) << left << itemss[i].name << setw(10) << itemss[i].price << setw(10) << itemss[i].quantity << setw(10) << itemss[i].returntotal() << endl;
            }

            cout << endl << "TOTAL: " << returntotal() << endl;
            file << endl << "TOTAL: " << returntotal() << endl;
        }
        file.close();
    }
};

int main() {
    supermarket s;
    string itemname;
    double itemprice;
    int itemquantity;

    while (true) {
        cout << "Enter name (if done enter done): ";
        cin >> itemname;

        if (itemname == "done") {
            break;
        }

        cout << "Enter price: ";
        cin >> itemprice;

        cout << "Enter the number of items: ";
        cin >> itemquantity;
        cout << endl;

        s.add(itemname, itemprice, itemquantity);
    }

    cout << "Billing process starting..." << endl;
    s.displaybill();

    cout << endl;
    cout << "Thank you! Please visit again." << endl;

    return 0;
}

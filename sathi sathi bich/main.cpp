// sathi sathi bich


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // for formatting output

class Friend {
private:
    std::string name;
    double borrowed;
    double lent;
    double total;

public:
    Friend(const std::string &name, double borrowed, double lent)
            : name(name), borrowed(borrowed), lent(lent) {
        total = lent - borrowed;
    }

    void display() const {
        std::cout << "| " << std::setw(10) << name << " | " << std::setw(8) << borrowed
                  << " | " << std::setw(5) << lent << " | " << std::setw(6) << total << " |\n";
    }

    double getTotal() const {
        return total;
    }
};

int main() {
    std::vector<Friend> friends;
    int numFriends;

    std::cout << "Enter the number of friends: ";
    std::cin >> numFriends;

    for (int i = 0; i < numFriends; ++i) {
        std::string name;
        double borrowed, lent;

        std::cout << "Enter name for friend " << i + 1 << ": ";
        std::cin >> name;
        std::cout << "Enter borrowed amount for " << name << ": ";
        std::cin >> borrowed;
        std::cout << "Enter lent amount for " << name << ": ";
        std::cin >> lent;

        friends.push_back(Friend(name, borrowed, lent));
    }

    // Display in tabular form
    std::cout << "\nTransaction details:\n";
    std::cout << "| Name       | Borrowed | Lent  | Total  |\n";
    std::cout << "|------------|----------|-------|--------|\n";

    double grandTotal = 0.0;
    for (const auto &f : friends) {
        f.display();
        grandTotal += f.getTotal();
    }

    std::cout << "|------------|----------|-------|--------|\n";
    std::cout << "| Grand Total                          | " << std::setw(6) << grandTotal << " |\n";

    return 0;
}
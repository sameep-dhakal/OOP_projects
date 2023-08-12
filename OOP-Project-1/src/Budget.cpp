#include "Budget.h" // includes the header file of Budget class
#include <iostream> // includes the input-output stream library

Budget::Budget() : amount(0.0) {} // initializes the budget amount as zero

double Budget::getAmount() const {
    return amount; // returns the amount
}

void Budget::addAmount(double value) {
    amount += value; // adds the amount to the budget
}

void Budget::subtractAmount(double value) {
    amount -= value; // subtracts the amount from the budget
}

void Budget::displayRemainingBudget() const {
    if (amount > 0.0) {
        std::cout << "\nRemaining Budget: Rs " << amount << std::endl; // displays the remaining budget
    }
    else {
        std::cout << "\nBudget: Rs " << amount << std::endl; // displays the starting budget i.e. zero
    }
}

std::ostream& operator<<(std::ostream& os, const Budget& budget) {
    os << budget.amount; // print the budget's amount to the ouput stream
    return os; // returns the output stream to allow chaining like "std::cout << age << height"
}

std::istream& operator>>(std::istream& is, Budget& budget) {
    is >> budget.amount; // read the input stream from the input into the budget
    return is; // returns the input stream to allow chaining like "std::cin >> age >> height"
}
#include "Expense.h" // includes the header file of Expense class
#include <iostream> // includes the input-output stream library

Expense::Expense(){} // default constructor

Expense::Expense(std::string& dt, std::string& desc, double amt)
    : date(dt), description(desc), amount(amt) {} // initializes the date, description and amount variables

std::string Expense::getDate() const {
    return date; // returns the date
}

std::string Expense::getDescription() const {
    return description; // returns the description
}

double Expense::getAmount() const {
    return amount; // returns the amount
}

void Expense::displayExpenseDetails() const {
    std::cout << "Date: " << date << "\nDescription: " << description << "\nAmount: Rs " << amount << std::endl; // prints the date, description and amount of the expense
}
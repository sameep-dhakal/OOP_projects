#ifndef EXPENSE_H // checks if the symbol is defined
#define EXPENSE_H // defines the symbol if it is not defined

#include <string> // includes the string library

class Expense {
    private:
        std::string date; // declaring the date variable as a string
        std::string description; // declaring the description variable as a string
        double amount; // declaring the amount variable as a double

    public:
        Expense(); // default constructor
        Expense(std::string& dt, std::string& desc, double amt); // constructor to set date, description and amount

        std::string getDate() const; // returns the date
        std::string getDescription() const; // returns the description
        double getAmount() const; // returns the amount
        void displayExpenseDetails() const; // displays the expense details
};

#endif // marks the end of the guards
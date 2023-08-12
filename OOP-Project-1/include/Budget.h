#ifndef BUDGET_H // checks if the symbol is defined (header guard)
#define BUDGET_H // defines the symbol if it is not defined (header guard)

#include <iostream> // includes the input-output stream library

class Budget {
    private:
        double amount; // declaring the amount variable as a double

    public:
        Budget(); // default constructor

        double getAmount() const; // returns the amount
        void addAmount(double value); // adds the amount to the budget
        void subtractAmount(double value); // subtracts the amount from the budget
        void displayRemainingBudget() const; // displays the remaining budget or the starting budget of Rs 0.0

        friend std::ostream& operator<<(std::ostream& os, const Budget& budget); // overloads the operator "<<" to be used as to output the budget
        friend std::istream& operator>>(std::istream& is, Budget& budget); // overloads the operator ">>" to be used as to input the budget
};

#endif // marks the end of the header guards
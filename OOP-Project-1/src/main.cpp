#include <iostream> // includes the input-output stream library
#include <fstream> // includes the file stream library
#include <sstream> // includes the string stream library
#include <iomanip> // includes the input-output manipulation library for formatting
#include "Budget.h" // includes the header file of Budget class
#include "Expense.h" // includes the header file of Expense class

void saveData(const Budget& budget, const Expense* expenses, int numExpenses) {
    // saves the budget and the expenses' details in the database

    std::ofstream file("data.txt"); // output file stream used to store the data in the database 

    if (!file) {
        std::cerr << "\nError opening file to save the records." << std::endl; // if there was an error in recording the details into the database
        return;
    }

    file << budget.getAmount() << "\n"; // saves the budget amount in the database
    for (int i = 0; i < numExpenses; i++) {
        // saves the expenses' details in the database
        file << expenses[i].getDate() << "," << expenses[i].getDescription() << "," << expenses[i].getAmount() << "\n"; 
    }
}

void loadData(Budget& budget, Expense* expenses, int& numExpenses) {
    // loads the budget and expenses' details from the database

    std::ifstream file("data.txt"); // input file stream used to read the data from the database

    if (!file) {
        return; // if previous data doesn't exist then it loads nothing from the database
    }

    file >> budget; // reads the budget amount from the database
    file.ignore(); // ignores the newline character("\n")

    std::string line; // declares a string variable to hold the line read from the file
    int index = 0; // initializing an index to keep track of the expense array

    // read each line from the file using std::getline until there is no line left to read
    while (std::getline(file, line)) {
        std::istringstream iss(line); // creates an input string stream for the current line
        std::string date, description; // declare variables to hold parsed data
        double amount;

        // parse the line using std::getline and ',' delimiter
        std::getline(iss, date, ','); // reads the date and stores it then iss is positioned just after the comma
        std::getline(iss, description, ','); // reads the description and stores it then iss is positioned just after the second comma
        iss >> amount; // reads the remaining part of the line

        expenses[index] = Expense(date, description, amount); // stores the expenses' details into the expenses array
        index++; // move to the next index for the next expense
    }

    numExpenses = index; // total number of expenses is stored in numExpenses
}


int main() {
    Budget budget; // declaring budget object for the class Budget
    Expense expenses[100]; // declaring expenses array that can hold upto 100 Expense objects
    int numExpenses = 0; // declaring the numExpenses as an integer and initializes as zero

    loadData(budget, expenses, numExpenses); // loads the previously recorded expenses if any

    while (true) {
        std::cout << "\nExpense Tracker Menu:\n"; // Menu Options
        std::cout << "1. Add Budget\n"; // add amount to budget and store it in the database
        std::cout << "2. Add Expense\n"; // add expense information to the database
        std::cout << "3. Display\n"; // display the remaining budget and the expenses recorded 
        std::cout << "4. Delete\n"; // delete all the data of budget amount and the expenses
        std::cout << "5. Exit\n"; // exit the program
        int choice;
        std::cout << "\nEnter your choice: "; // take the input from the user
        std::cin >> choice;

        switch (choice) {
            case 1: // 1.Add Budget
                {   
                    std::cout << "\nAdd Budget\n";
                    double budgetAmount; // declaring the budgetAmount variable as a double
                    std::cout << "\nEnter budget amount: Rs ";
                    std::cin >> budgetAmount; 
                    budget.addAmount(budgetAmount); // adds the amount to the budget
                    break;
                }

            case 2: // 2.Add Expense
                {
                    std::cout << "\nAdd Expense\n";
                    if (budget.getAmount() <= 0) {
                        std::cout << "\nPlease add budget first." << std::endl; // Budget is not added before the expense is added
                        break;
                    }
                    std::string date, description; // declaring the date and description variables as string
                    double amount; // declaring the amount variable as a double
                    std::cout << "\nEnter date (DD/MM/YYYY): ";
                    std::cin.ignore(); // clears any leftover newline character from the input buffer
                    std::getline(std::cin, date); 
                    std::cout << "\nEnter description: ";
                    std::getline(std::cin, description);
                    std::cout << "\nEnter amount: Rs ";
                    std::cin >> amount;
                    if (amount > budget.getAmount()) {
                        std::cout << "\nExpense amount exceeds budget. Please add budget first." << std::endl; // Budget is less than the expense
                    } 
                    else {
                        budget.subtractAmount(amount); // subtracts the amount from the budget
                        expenses[numExpenses] = Expense(date, description, amount); // Expense is recorded
                        numExpenses++; // increment numExpenses i.e. number of expenses
                        std::cout << "\nExpense added successfully." << std::endl;
                    }
                    break;
                }

            case 3: // 3. Display
                {
                    std::cout << "\nDisplay\n";
                    budget.displayRemainingBudget(); // displays the remaining budget
                    std::cout << "\nExpenses List:\n";
                    std::cout << "---------------------------------------------------------\n";
                    std::cout << std::left << std::setw(15) << "Date" << std::setw(25) << "Description" << std::setw(12) << "Amount (Rs )" << std::endl;
                    std::cout << "---------------------------------------------------------" << std::endl;
                    for (int i = 0; i < numExpenses; i++) { 
                        // displays the date, description and amount details of the expense
                        std::cout << std::left << std::setw(15) << expenses[i].getDate() << std::setw(25) << expenses[i].getDescription() << std::setw(12) << expenses[i].getAmount() << std::endl;
                    }
                    break;
                }

            case 4: // 4. Delete
                {
                    budget = Budget(); // resets budget amount
                    numExpenses = 0; // resets the number of expenses
                    std::cout << "\nBudget and expenses deleted.\n" << std::endl; 
                    break;
                }

            case 5: // 5. Exit
                saveData(budget, expenses, numExpenses); // saves the data in the database
                return 0;

            default:
                std::cout << "\nInvalid choice. Please try again.\n" << std::endl;
        }
        saveData(budget, expenses, numExpenses); // saves the data in the database
    }

    return 4647;
} 

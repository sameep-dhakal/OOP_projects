#include <iostream>
#include <fstream>   // For handling file input and output operations
#include <sstream>  // For string stream operations
#include <vector>  // For handling multiple numbers

using namespace std;

int main() {
    ofstream outputFile("calculator_output.txt");  // Open output file
      if (!outputFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;  // Exit with an error code
    
    }

    outputFile << "Calculator Output:" << endl;
     while (true) {  // Infinite loop to keep the program running
    char operation;
    double result;
    vector<double> numbers;  // Vector to store input numbers

    cout << "Enter operation (+, -, *, /): ";
    cin >> operation;  // Get the operation from the user

    int numCount;
    cout << "Enter the number of values: ";
    cin >> numCount;  // Get the number of values from the user

    if (numCount <= 1) {
        cout << "Invalid number count!" << endl;
        return 1;  // Exit with an error code
    }

    numbers.resize(numCount);  // Resize vector to hold the required number of values

    cout << "Enter " << numCount << " numbers: ";
    for (int i = 0; i < numCount; ++i) {
        cin >> numbers[i];  // Get each number from the user and store it in the vector
    }

    switch (operation) {
        case '+':
            result = 0;  // Initialize result with 0 for addition
            for (int i = 0; i < numCount; ++i) {
    double num = numbers[i];

                result += num;  // Perform addition for each number in the vector
            }
            break;
        case '-':
            result = numbers[0];  // Initialize result with the first number for subtraction
            for (int i = 1; i < numCount; ++i) {
                result -= numbers[i];  // Perform subtraction for each subsequent number
            }
            break;
        case '*':
            result = 1;  // Initialize result with 1 for multiplication
           for (int i = 0; i < numCount; ++i) {
    double num = numbers[i];

                result *= num;  // Perform multiplication for each number in the vector
            }
            break;
        case '/':
            result = numbers[0];  // Initialize result with the first number for division
            for (int i = 1; i < numCount; ++i) {
                if (numbers[i] != 0) {
                    result /= numbers[i];  // Perform division for each subsequent number (non-zero denominator)
                } else {
                    cout << "Error: Division by zero is not allowed!" << endl;
                    return 1;  // Exit with an error code
                }
            }
            break;
        default:
            cout << "Invalid operation!" << endl;
            return 1;  // Exit with an error code
    }

    cout << "Result: " << result << endl;

    // Write the operation and result to the output file
    outputFile << "Operation: ";
    for (int i = 0; i < numCount; ++i) {
    double num = numbers[i];

        outputFile << num << " " << operation << " ";  // Write each number and operation symbol
    }
    outputFile << "= " << result << endl;  // Write the result at the end

    outputFile.close();  // Close the output file
}

    return 0;  // Exit successfully
}

//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//
//int main() {
//    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator
//
//    const int minValue = 0;
//    const int maxValue = 9;
//    const int numValues = maxValue - minValue + 1;
//
//    std::vector<int> availableValues;
//    for (int i = minValue; i <= maxValue; ++i) {
//        availableValues.push_back(i);
//    }
//
//    while (!availableValues.empty()) {
//        int randomIndex = std::rand() % availableValues.size();
//        int randomValue = availableValues[randomIndex];
//
//        // Output the random value
//        std::cout << randomValue << " ";
//
//        // Remove the used value from the list
//        availableValues.erase(availableValues.begin() + randomIndex);
//    }
//
//    std::cout << std::endl;
//
//    return 0;
//}
//#include <iostream>
//#include <vector>
//#include<cstdlib>
//
//std::vector<int> generateRandomValues(int count) {
//    std::vector<int> values;
//    
//    for (int i = 0; i < count; ++i) {
//        int randomValue = rand() % 10; // Generates random values between 0 and 9
//        values.push_back(randomValue);
//    }
//    
//    return values;
//}
//
//int main() {
//    int numValues = 10; // Example: generate 10 random values
//    std::vector<int> randomArray = generateRandomValues(numValues);
//
//    // Print the values returned from the function
//    for (int i = 0; i < randomArray.size(); ++i) {
//        std::cout << randomArray[i] << " ";
//    }
//
//    std::cout << std::endl;
//
//    return 0;
//}
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::vector<int> generateRandomValues(int count) {
    std::vector<int> values;

    for (int i = 0; i < count; ++i) {
        int randomValue;
        do {
            randomValue = std::rand() % 10; // Generates random values between 0 and 9
        } while (std::find(values.begin(), values.end(), randomValue) != values.end());

        values.push_back(randomValue);
    }

    return values;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator

    int numValues = 10; // Example: generate 10 random values
    std::vector<int> randomArray = generateRandomValues(numValues);

    // Print the values returned from the function
    for (int i = 0; i < randomArray.size(); ++i) {
        std::cout << randomArray[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}

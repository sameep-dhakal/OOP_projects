#ifndef randomgenarator_H
#define randomgenerator_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

std::vector<int>generateRandomValues(int count) {
    std::vector<int>values;

    for (int i = 0; i < count; ++i) {
        int randomValue;
        do {
            randomValue = std::rand() % 10; // Generates random values between 0 and 9
        } while (std::find(values.begin(), values.end(), randomValue) != values.end());

        values.push_back(randomValue);
    }

    return values;
}
#endif

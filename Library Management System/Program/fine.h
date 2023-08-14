#ifndef FINE_H
#define FINE_H

#include <iostream>
#include <vector>
#include <ctime> // Include the ctime header for time functions
using namespace std;

class Fine
{
private:
    int finePerDay; // Fine amount per day for late returns
    vector<string> lateBooks; // Store the names of books returned late
    int totalFine; // Total fine amount accumulated

public:
    Fine(int finePerDay) : finePerDay(finePerDay), totalFine(0) {}

    // Record late book returns
    void addLateBook(const string& bookName)
    {
        lateBooks.push_back(bookName);
    }

    // Calculate and display the fine for a user
    void calculateFine(const std::string& username)
    {
        if (lateBooks.empty())
        {
            cout << username << ", you have no fines." << endl;
            return;
        }

        int numLateBooks = lateBooks.size();
        
        // Calculate days late based on current date and 15-day period
        time_t currentTime;
        time(&currentTime); // Get the current time
        struct tm fifteenDaysAgo;
        currentTime -= 15 * 24 * 60 * 60; // Subtract 15 days in seconds
        fifteenDaysAgo = *localtime(&currentTime);
        
        // Calculate fine amount based on days late
        int fineAmount = numLateBooks * finePerDay * (15 - fifteenDaysAgo.tm_mday);
        totalFine += fineAmount;

        cout << "Dear " << username << ", you have " << numLateBooks << " late book(s):" << endl;
        for (const string& book : lateBooks)
        {
            cout << "- " << book << endl;
        }

        cout << "Total fine amount: $" << fineAmount << endl;
    }

    // Get the total fine accumulated
    int getTotalFine()
    {
        return totalFine;
    }

    // Clear late book list and reset total fine
    void clearFines()
    {
        lateBooks.clear();
        totalFine = 0;
    }
};

#endif

#ifndef TEACHERDASHBOARD_H
#define TEACHERDASHBOARD_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<cstdlib>
using namespace std;

class TeacherDashboard
{
private:
    string username;
    string password;
    string filename;

public:
    TeacherDashboard(const string &filename) : filename(filename) {}

    void login()
    {
        cout << "\033[1;32m"; // Set text color to bright green
        cout << "Teacher Dashboard Login...." << endl;
        cout << "\033[0m"; // Reset text color to default

        cout << "Enter your username: ";
        cin.ignore();
        getline(cin, username);

        cout << "Enter your password: ";
        getline(cin, password);

        if (username == "teacher" && password == "password")
        {
            cout << "\033[1;32m"; // Set text color to bright green
            cout << "Teacher Dashboard Login Success!...." << endl;
            cout << "\033[0m"; // Reset text color to default
            displayOptions();
        }
        else
        {
            cout << "\033[1;31m"; // Set text color to bright red
            cout << "Teacher Dashboard Login \033[0;31mFailure!\033[0m" << endl;
            cout << "\033[0m"; // Reset text color to default
        }
    }

    void displayOptions()
    {
        char userCho;
        int choice;
        system("cls");
        cout << "\033[1;34m"; // Set text color to bright blue
        cout << "Teacher Dashboard Options:\n";
        cout << "\033[0m";    // Reset text color to default
        cout << "\033[1;33m"; // Set text color to bright yellow
        cout << "1. View Pending Book Requests\n";
        cout << "0. Exit\n";
        cout << "\033[0m"; // Reset text color to default
        do
        {
            cout << "Enter your choice: ";
            cin >> userCho;

            switch (userCho)
            {
            case '1':
                viewPendingBookRequests();
                break;
            case '0':
                cout << "Exiting....." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        } while (userCho != '0');
    }

    void viewPendingBookRequests()
    {
        cout << "List of the pending requested books: " << endl;
        ifstream inputThefile("../txt file/BookDetails.txt");

        if (!inputThefile.is_open())
        {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(inputThefile, line))
        {
            cout << line << endl;
        }

        inputThefile.close();
    }
};

#endif

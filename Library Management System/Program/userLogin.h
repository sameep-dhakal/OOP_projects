#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class UserLoginSection
{
private:
    string username;
    string password;
    bool loginSuccessful;

public:
    UserLoginSection() : loginSuccessful(false) {}

    void setUsername(const string& newUsername)
    {
        username = newUsername;
    }

    void setPassword(const string& newPassword)
    {
        password = newPassword;
    }

    void CreateAccount()
    {
        cout << "Create a new username: " << endl;
        cin.ignore();
        getline(cin, username);

        cout << "Create a new password: " << endl;
        getline(cin, password);

        // Save the credentials to a file (e.g., "StudentCredentials.txt")
        ofstream credentialsFile("../txt file/StudentCredentials.txtStudentCredentials.txt", ios::app);
        if (credentialsFile.is_open())
        {
            credentialsFile<<"username : " << username << endl << "password : " << password << endl;
            credentialsFile.close();
            cout << "Account created successfully!" << endl;
        }
        else
        {
            cout << "Unable to create an account." << endl;
        }
    }

    void LoginAccount()
    {
        cout << "Enter your username: " << endl;
        cin.ignore();
        getline(cin, username);

        cout << "Enter your password: " << endl;
        getline(cin, password);

        ifstream credentialsFile("StudentCredentials.txt");
        string storedUsername, storedPassword;

        loginSuccessful = false;

        while (credentialsFile >> storedUsername >> storedPassword)
        {
            if (storedUsername == username && storedPassword == password)
            {
                loginSuccessful = true;
                break;
            }
        }

        if (loginSuccessful)
        {
            cout << "Login Success!" << endl;
        }
        else
        {
            cout << "Login Failed! Invalid username or password." << endl;
        }

        credentialsFile.close();
    }

    bool isLoginSuccessful()
    {
        return loginSuccessful;
    }
};

#endif

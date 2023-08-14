#include <iostream>
#include <fstream>
using namespace std;

class ContactManager {
private:
    string firstname, lastname, phonenum;

    bool check_digits(string x) {
        return x.length() == 10;
    }

    bool check_num(string x) {
        for (int i = 0; i < x.length(); i++) {
            if (!isdigit(x[i])) {
                return false;
            }
        }
        
        return true;
    }

public:
    void addContact() {
        ofstream phone("number.txt", ios::app);
        system("cls");
        cout << "\n\n\tEnter first name:";
        cin >> firstname;
        cout << "\n\tEnter last name:";
        cin >> lastname;
        bool validphonenum = false;
        while (!validphonenum) {
            cout << "\n\tEnter a 10 Digit phone number:";
            cin >> phonenum;
            if (check_digits(phonenum)) {
                if (check_num(phonenum)) {
                    if (phone.is_open()) {
                        validphonenum = true;
                        phone << firstname << " " << lastname << " " << phonenum << endl;
                        cout << "\n\tContact Saved.";
                    } else {
                        cout << "\n\tError!";
                    }
                } else {
                    cout << "\n\tInvalid! Phone number must contain numbers only.\n\tTry Again!\n";
                }
            } else {
                cout << "\n\tThe number is invalid. Must contain 10 digits.\n\tTry again!\n";
            }
        }
        phone.close();
    }

    void searchContact() {
        bool found = false;
        ifstream file("number.txt");
        string keyword;
        cout << "\n\tEnter Name to Search:";
        cin >> keyword;
        system("cls");
        while (file >> firstname >> lastname >> phonenum) {
            if (keyword == firstname || keyword == lastname) {
                cout << "\n\n\n\tContact Details:";
                cout << "\n\n\tFirst Name:" << firstname;
                cout << "\n\tLast Name:" << lastname;
                cout << "\n\tPhone Number:" << phonenum;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\n\tContact Not Found.";
        }
    }

    void help() {
    	        system("cls");
                cout << "\n\n\tThis is a simple contact management system.";
                cout << "\n\t1.To add a contact, choose option 1 and provide the necessary information.";
                cout << "\n\t2.To search for a contact,choose option 2 and enter a name to search for.";
                cout << "\n\t3.To see this help message,choose option 3.";
                cout << "\n\t4.To exit the program,choose option 4.";
    }

    void exit() {
        system("cls");
        cout << "\n\n\t\tThank you. Hope to see you again!";
        ::exit(1);
    }

    void run() {
    while(true){
        short int choice;
        system("cls");
        system("color 0B");
        cout << ("\n\n\n\t\t||Contact Mangement||");
        cout << ("\n\n\n\t1.Add Contact \n\t2.Search Contact\n\t3.Help\n\t4.Exit\n\t- ");
        cin >> choice;

        switch (choice) {
            case 1:
                addContact();
                askToReturn();
                break;

            case 2:
                searchContact();
                askToReturn();
                break;

            case 3:
                help();
                askToReturn();
                break;

            case 4:
                exit();
                return;

            default:
                cout << "\n\n\tInvalid Input!!";
                cout << "\n\tPress Any Key TO Continue:";
                cin.ignore();
                cin.get();
                run();
           }
        
        }
    }
    void askToReturn() {
        cout << "\n\n\tPress any key to return to the main menu...";
        cin.ignore();
        cin.get();
    }
};


int main() {
    ContactManager manager;
    manager.run();
    return 0;
}

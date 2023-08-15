#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;

class Student {
	
    string name;
    int age;
    string rollNumber;
     string roomType;
    int roomPrice;
    bool laundryService;
    int cookedMealsPerWeek;
    bool wifiAccess;
public:
    Student() {}
    Student(string name, int age, string rollNumber)
        : name(name), age(age), rollNumber(rollNumber) {}

    
    string getName() const { return name; }
    int getAge() const { return age; }
    string getRollNumber() const { return rollNumber; }
      string getRoomType() const { return roomType; }
    int getRoomPrice() const { return roomPrice; }
    bool hasLaundryService() const { return laundryService; }
    int getCookedMealsPerWeek() const { return cookedMealsPerWeek; }
    bool hasWifiAccess() const { return wifiAccess; }


};

class HostelManagementSystem {
private:
    Student students[MAX_STUDENTS];
    int numStudents;

    void loadStudentsFromFile() {
        ifstream inputFile("students.txt");
        if (inputFile.is_open()) {
            string name, rollNumber;
            int age;

            while (numStudents < MAX_STUDENTS && inputFile >> name >> age >> rollNumber) {
                students[numStudents++] = Student(name, age, rollNumber);
            }

            inputFile.close();
        }
    }
public:
    HostelManagementSystem() : numStudents(0) {
        loadStudentsFromFile();
    }

    ~HostelManagementSystem() {
        saveStudentsToFile();
    }

    // Add a student to the hostel
    void addStudent() {
        if (numStudents >= MAX_STUDENTS) {
            cout << "Hostel is full. Cannot add more students.\n";
            return;
        }

        string name, rollNumber;
        int age;
        cout << "Enter student name: ";
        cin.ignore(); // Ignore any leftover newlines in the input buffer
        getline(cin, name);
        cout << "Enter student age: ";
        cin >> age;
        cout << "Enter student roll number: ";
        cin.ignore(); // Ignore any leftover newlines in the input buffer
        getline(cin, rollNumber);

        students[numStudents] = Student(name, age, rollNumber);
        numStudents++;

        cout << "Student added to the hostel.\n";
    }

    // Display all students in the hostel
    void displayStudents() const {
        if (numStudents == 0) {
            cout << "No students in the hostel.\n";
            return;
        }

        cout << "Hostel Students:\n";
        for (int i = 0; i < numStudents; ++i) {
            cout << "Name: " << students[i].getName() << ", Age: " << students[i].getAge()
                      << ", Roll Number: " << students[i].getRollNumber() << "\n";
        }
    }

    // Remove a student from the hostel by their roll number
    void removeStudent() {
        if (numStudents == 0) {
            std::cout << "No students in the hostel.\n";
            return;
        }

        string rollNumber;
        cout << "Enter the roll number of the student to be removed: ";
        cin.ignore(); // Ignore any leftover newlines in the input buffer
        getline(std::cin, rollNumber);

        for (int i = 0; i < numStudents; ++i) {
            if (students[i].getRollNumber() == rollNumber) {
                for (int j = i; j < numStudents - 1; ++j) {
                    students[j] = students[j + 1];
                }
                numStudents--;
                std::cout << "Student with roll number " << rollNumber << " removed from the hostel.\n";
                return;
            }
        }
        cout << "Student with roll number " << rollNumber << " not found in the hostel.\n";
    }

    // Search for a student in the hostel by their roll number
    void searchStudent() const {
        if (numStudents == 0) {
            cout << "No students in the hostel.\n";
            return;
        }

        string rollNumber;
        cout << "Enter the roll number of the student to search: ";
        cin.ignore(); 
        getline(cin, rollNumber);

        for (int i = 0; i < numStudents; ++i) {
            if (students[i].getRollNumber() == rollNumber) {
                cout << "Student found:\n";
                cout << "Name: " << students[i].getName() << ", Age: " << students[i].getAge()
                          << ", Roll Number: " << students[i].getRollNumber() << "\n";
                return;
            }
        }
        cout << "Student with roll number " << rollNumber << " not found in the hostel.\n";
    }



    void saveStudentsToFile() {
        ofstream outputFile("students.txt");
        if (outputFile.is_open()) {
            for (int i = 0; i < numStudents; ++i) {
                outputFile << students[i].getName() << " "
                           << students[i].getAge() << " "
                           << students[i].getRollNumber() << "\n";
            }
            outputFile.close();
        }
    }
     void information() {
        cout << "Hostel Information:\n";
        cout << "-------------------\n";
        cout << "Room Types and Prices:\n";
        cout << "1. One Seat - Price: 15000\n";
        cout << "2. Two Seat - Price: 13000\n";
        cout << "3. Three Seat - Price: 12000\n";
        cout << "4. Four Seat - Price: 10000\n";
        cout << "Facilities:\n";
        cout << "- Laundry service available once per week\n";
        cout << "- Students can have cooked meals twice a week\n";
        cout << "- Free WiFi access provided\n";
        cout << "----------------------------------------\n";
    }
};

int main() {
    HostelManagementSystem hostel;

    char choice;
    do {
		cout << "\t\tHostel Management System\n";
		cout << "\t\tConsloe Based Application \n\t\tmade by Kanchan Dhamala and Khemraj Joshi\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Remove Student\n";
        cout << "4. Search Student\n";
        cout << "5. Hostel Information\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

              switch (choice) {
            case '1':
                hostel.addStudent();
                break;
            case '2':
                hostel.displayStudents();
                break;
            case '3':
                hostel.removeStudent();
                break;
            case '4':
                hostel.searchStudent();
                break;
            case '5':
                hostel.information(); // Display Hostel Information
                break;
            case '6':
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != '6');

    return 0;
}

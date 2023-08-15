#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <iomanip>
using namespace std;

// Data structure to store student information
struct Student {
    string name;
    int id;
};

// Data structure to store book information
struct Book {
    string title;
    string author;
    int id;
    bool available;
    time_t returnDate;
    int studentId; // ID of the student who borrowed the book
};

// Global variables
vector<Book> books; // Stores book records
map<int, Student> students; // Stores student records

// File names for data storage
const string BOOKS_DATA_FILE = "library_data.txt";
const string STUDENTS_DATA_FILE = "students_data.txt";

// Admin credentials
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "pass";

// Fine amount per day for late book returns
const double FINE_PER_DAY = 1.0;

// Function to clear the console screen
void ClearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to pause console until Enter key is pressed
void PauseConsole() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Function to load data from files into memory
void LoadData() {
    // Load book data
    ifstream booksFile(BOOKS_DATA_FILE);
    if (!booksFile) {
        cerr << "Error: Could not open books data file." << endl;
        return;
    }

    Book book;
    while (booksFile >> book.id >> book.available >> book.returnDate >> book.studentId) {
        booksFile.ignore(); // Ignore the newline character
        getline(booksFile, book.title);
        getline(booksFile, book.author);
        books.push_back(book);
    }
    booksFile.close();

    // Load student data
    ifstream studentsFile(STUDENTS_DATA_FILE);
    if (!studentsFile) {
        cerr << "Error: Could not open students data file." << endl;
        return;
    }

    Student student;
    while (studentsFile >> student.id) {
        studentsFile.ignore(); // Ignore the newline character
        getline(studentsFile, student.name);
        students[student.id] = student;
    }
    studentsFile.close();
}

// Function to save data from memory into files
void SaveData() {
    // Save book data
    ofstream booksFile(BOOKS_DATA_FILE);
    if (!booksFile) {
        cerr << "Error: Could not open books data file." << endl;
        return;
    }

    for (const Book& book : books) {
        booksFile << book.id << " " << book.available << " " << book.returnDate << " " << book.studentId << "\n";
        booksFile << book.title << "\n";
        booksFile << book.author << "\n";
    }
    booksFile.close();

    // Save student data
    ofstream studentsFile(STUDENTS_DATA_FILE);
    if (!studentsFile) {
        cerr << "Error: Could not open students data file." << endl;
        return;
    }

    for (const auto& student : students) {
        studentsFile << student.first << "\n";
        studentsFile << student.second.name << "\n";
    }
    studentsFile.close();
}

// Function to generate a unique book ID
int GenerateUniqueBookID() {
    int maxID = 0;
    for (const Book& book : books) {
        if (book.id > maxID) {
            maxID = book.id;
        }
    }
    return maxID + 1;
}

// Function to generate a unique student ID
int GenerateUniqueStudentID() {
    int maxID = 0;
    for (const auto& student : students) {
        if (student.first > maxID) {
            maxID = student.first;
        }
    }
    return maxID + 1;
}

// Function to add a new book to the library
void AddBook() {
    ClearConsole();
    while (true) {
        Book newBook;
        cin.ignore(); // Clear the input buffer
        cout << "Add New Book\n";
        cout << "=============================\n";
        cout << "Enter book title: ";
        getline(cin, newBook.title);
        cout << "Enter author name: ";
        getline(cin, newBook.author);
        newBook.available = true;
        newBook.returnDate = 0;
        newBook.studentId = -1;
        newBook.id = GenerateUniqueBookID();
        books.push_back(newBook);
        SaveData();
        cout << "\nBook added successfully. ID: " << newBook.id << "\n";

        char choice;
        cout << "Do you want to add more books? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }
}

// Function to list all books in the library
void ListBooks() {
    ClearConsole();
    cout << "Library Books\n";
    cout << "====================================================================================================\n";
    cout << setw(10) << "ID" << setw(30) << "Title" << setw(25) << "Author" << setw(15) << "Available" << setw(20) << "Student ID" << setw(15) << "Days Late" << setw(15) << "Fine\n";
    cout << "====================================================================================================\n";
    for (const Book& book : books) {
        cout << setw(10) << book.id << setw(30) << book.title << setw(25) << book.author
                  << setw(15) << (book.available ? "Yes" : "No") << setw(20) << (book.studentId != -1 ? to_string(book.studentId) : "") << setw(15);
        if (!book.available) {
            time_t now = time(nullptr);
            double daysLate = difftime(now, book.returnDate) / (24 * 3600); // Calculate days late
            if (daysLate > 0) {
                double fine = daysLate * FINE_PER_DAY;
                cout << daysLate << setw(15) << "$" << fine << "\n";
            } else {
                cout << "0" << setw(15) << "-\n";
            }
        } else {
            cout << "-" << setw(15) << "-\n";
        }
    }
    cout << "====================================================================================================\n";
    PauseConsole();
}

// Function to list students and the books they have borrowed
void ListStudentsWithBooks() {
    ClearConsole();
    cout << "Students and Their Books\n";
    cout << "==============================================================================================\n";
    cout << setw(15) << "Student ID" << setw(30) << "Student Name" << setw(15) << "Book ID" << setw(30) << "Book Title\n";
    cout << "==============================================================================================\n";
    for (const auto& student : students) {
        const Student& s = student.second;
        bool studentFound = false;
        for (const Book& book : books) {
            if (book.studentId == s.id) {
                studentFound = true;
                cout << setw(15) << s.id << setw(30) << s.name << setw(15) << book.id << setw(30) << book.title << "\n";
            }
        }
        if (!studentFound) {
            cout << setw(15) << s.id << setw(30) << s.name << setw(15) << "-" << setw(30) << "No Books\n";
        }
    }
    cout << "==============================================================================================\n";
    PauseConsole();
}

// Function to add a new student to the library
void AddStudent() {
    ClearConsole();
    Student newStudent;
    cin.ignore(); // Clear the input buffer
    cout << "Add New Student\n";
    cout << "=============================\n";
    cout << "Enter student name: ";
    getline(cin, newStudent.name);
    newStudent.id = GenerateUniqueStudentID();
    students[newStudent.id] = newStudent;
    SaveData();
    cout << "\nStudent added successfully. ID: " << newStudent.id << "\n";
    PauseConsole();
}

// Function to lend a book to a student
void LendBook() {
    ClearConsole();
    int bookId, studentId;
    cout << "Lend Book\n";
    cout << "=============================\n";
    cout << "Enter book ID: ";
    cin >> bookId;
    cout << "Enter student ID: ";
    cin >> studentId;

    auto bookIter = find_if(books.begin(), books.end(), [bookId](const Book& book) {
        return book.id == bookId && book.available;
    });

    auto studentIter = students.find(studentId);

    if (bookIter != books.end() && studentIter != students.end()) {
        Book& book = *bookIter;
        Student& student = studentIter->second;
        book.available = false;
        time_t now = time(nullptr);
        book.returnDate = now + (15 * 24 * 3600); // 15 days from now
        book.studentId = student.id;
        SaveData();
        cout << "\nBook lent successfully to student: " << student.name << "\n";
    } else {
        cout << "\nBook or student not found or book already lent.\n";
    }
    PauseConsole();
}

// Function to deposit a book returned by a student
void DepositBook() {
    ClearConsole();
    int bookId;
    cout << "Deposit Book\n";
    cout << "=============================\n";
    cout << "Enter book ID: ";
    cin >> bookId;

    auto bookIter = find_if(books.begin(), books.end(), [bookId](const Book& book) {
        return book.id == bookId && !book.available;
    });

    if (bookIter != books.end()) {
        Book& book = *bookIter;
        time_t now = time(nullptr);
        double daysLate = difftime(now, book.returnDate) / (24 * 3600); // Calculate days late
        if (daysLate > 0) {
            double fine = daysLate * FINE_PER_DAY;
            cout << "Book is " << daysLate << " days late.\n";
            cout << "Fine: $" << fine << "\n";
        }
        book.available = true;
        book.returnDate = 0;
        book.studentId = -1;
        SaveData();
        cout << "\nBook deposited successfully.\n";
    } else {
        cout << "\nBook not found or already deposited.\n";
    }
    PauseConsole();
}

// Function to clear all student data and reset associated book records
void ClearStudentData() {
    ClearConsole();
    students.clear();

    // Clear associated student IDs from borrowed books
    for (Book& book : books) {
        book.studentId = -1;
        book.available = true;
        book.returnDate = 0;
    }

    SaveData();
    cout << "All student data cleared and borrowed book records reset.\n";
    PauseConsole();
}

// Function to clear all book data while keeping student IDs intact
void ClearBookData() {
    ClearConsole();
    books.clear();

    // Clear associated book IDs from books, but keep student IDs intact
    for (auto& book : books) {
        book.studentId = -1;
        book.available = true;
        book.returnDate = 0;
    }

    SaveData();
    cout << "All book data cleared.\n";
    PauseConsole();
}

// Function to handle admin login
bool AdminLogin() {
    string username, password;
    ClearConsole();
    cout << "Admin Login\n";
    cout << "=============================\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    return (username == ADMIN_USERNAME && password == ADMIN_PASSWORD);
}

// Function to display and manage the admin menu
void AdminMenu() {
    if (!AdminLogin()) {
        cout << "Login failed. Access denied.\n";
        PauseConsole();
        return;
    }

    int choice;
    while (true) {
        ClearConsole();
        cout << "Admin Menu\n";
        cout << "=============================\n";
        cout << "1. Add Book\n";
        cout << "2. List Books\n";
        cout << "3. List Students and Their Books\n";
        cout << "4. Add Student\n";
        cout << "5. Lend Book\n";
        cout << "6. Deposit Book\n";
        cout << "7. Clear Student Data\n";
        cout << "8. Clear Book Data\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character
        switch (choice) {
            case 1:
                AddBook();
                break;
            case 2:
                ListBooks();
                break;
            case 3:
                ListStudentsWithBooks();
                break;
            case 4:
                AddStudent();
                break;
            case 5:
                LendBook();
                break;
            case 6:
                DepositBook();
                break;
            case 7:
                ClearStudentData();
                break;
            case 8:
                ClearBookData();
                break;
            case 9:
                SaveData();
                cout << "\nExiting. Goodbye!\n";
                return;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                PauseConsole();
        }
    }
}

// Main function
int main() {
    LoadData();

    int choice;
    while (true) {
        ClearConsole();
        cout << "Library Management System\n";
        cout << "=============================\n";
        cout << "1. Admin\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character
        switch (choice) {
            case 1:
                AdminMenu();
                break;
            case 2:
                SaveData();
                cout << "\nExiting. Goodbye!\n";
                return 0;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                PauseConsole();
        }
    }

    return 0;
}

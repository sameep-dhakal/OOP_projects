#ifndef BOOKDETAILS_H
#define BOOKDETAILS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
class BookDetails
{
private:
    int S_No;
    string BookName;
    string AuthorName;
    bool approved;

public:

    void setBookDetails(string BookName, string AuthorName, int Serial_Number)
    {
        this->BookName = BookName;
        this->AuthorName = AuthorName;
        this->S_No = Serial_Number;
    }


    BookDetails(){}
    BookDetails(const std::string& bookName, const string& authorName, int serialNumber)
        : BookName(bookName), AuthorName(authorName), S_No(serialNumber) {}

    void insertBookDetails()
    {
        cout << "Inserting Book" << endl;
        cout << "Enter Book Name: " << endl;
        cin.ignore();
        getline(cin, BookName);
        cout << "Enter Author Name: " << endl;
        getline(cin, AuthorName);
    }

    int getSerialNumber()const
    {
        return this->S_No;
    }

    string getBookName()const
    {
        return this->BookName;
    }

    string getAuthorName()const
    {
        return this->AuthorName;
    }

    void displayBookDetails();

    void ShowBookList(const vector<BookDetails> &books)
    {
        cout << "Book List:\n";
        for (const BookDetails &book : books)//range based loop
        {
            cout << "Book Details" << endl;
            cout << "Book Name: " << getBookName() << endl;
            cout << "Author Name: " << getAuthorName() << endl;
            cout << endl;
        }
    }

    void set_approved(bool status)
    {
        approved = status;
    }

    bool isApproved() const
    {
        return approved;
    }
};

void BookDetails ::displayBookDetails()
{
    cout << "Book Details" << endl;
    cout << "Book Name: " << this->BookName << endl;
    cout << "Author Name: " << this->AuthorName << endl;
}
#endif

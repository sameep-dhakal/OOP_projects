#include <iostream>
#include <cstring>  
using namespace std;

class book {
private:
    int idno;
    char bookname[100];  
    char authorname[100];
    int price;
    char flag;

public:
    void addbookinfo() {
        cout << "enter book name: ";
        cin.ignore();
        cin.getline(bookname, 100);  
        cout << "enter author name: ";
        cin.getline(authorname, 100);
        cout << "enter book id.no: ";
        cin >> idno;
        cout << "enter the price of the book: ";
        cin >> price;
        cout << "is the book issued (y/n): ";
        cin >> flag;
    }

    void displaybookinfo() {
        cout << "\nbook information:\n";
        cout << "id number: " << idno << endl;
        cout << "title: " << bookname << endl;
        cout << "author: " << authorname << endl;
        cout << "price: " << price << endl;
        cout << "issued: " << flag << endl;
    }

    char* getauthorname() {
        return authorname;
    }

    char* getbookname() {
        return bookname;
    }

    int getidno() {
        return idno;
    }
};

class library {
private:
    book books[100];
    int bookcount;

public:
    library() : bookcount(0) {}

    void addbook() {
        books[bookcount].addbookinfo();
        bookcount++;
    }

    void displayallbooks() {
        for (int i = 0; i < bookcount; i++) {
            books[i].displaybookinfo();
        }
    }

    void displaybooksbyauthor(char* author) {
        for (int i = 0; i < bookcount; i++) {
            if (strcmp(books[i].getauthorname(), author) == 0) {
                books[i].displaybookinfo();
            }
        }
    }

    void displaybookcount() {
        cout << "total number of available books: " << bookcount << endl;
    }

    void displaybookbyname(char* bookname) {
        for (int i = 0; i < bookcount; i++) {
            if (strcmp(books[i].getbookname(), bookname) == 0) {
                books[i].displaybookinfo();
            }
        }
    }

    void displaybookbyid(int id) {
        for (int i = 0; i < bookcount; i++) {
            if (books[i].getidno() == id) {
                books[i].displaybookinfo();
            }
        }
    }
};

int main() {
    library library;

    while (true) {
        cout << "\tLIBRARY BOOK MANAGEMENT SYSTEM" << endl;
        cout << "============================================" << endl;
        cout << "press 1 to add book information" << endl;
        cout << "press 2 to display book information" << endl;
        cout << "press 3 to list all books of a given author" << endl;
        cout << "press 4 to list the count of books in the library" << endl;
        cout << "press 5 to list the title of a specified book" << endl;
        cout << "press 6 to list the book for a book id" << endl;
        cout << "press 7 to exit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                library.addbook();
                break;
            case 2:
                library.displayallbooks();
                break;
            case 3:
                char author[100];
                cout << "enter author name: ";
                cin.ignore();
                cin.getline(author, 100);
                library.displaybooksbyauthor(author);
                break;
            case 4:
                library.displaybookcount();
                break;
            case 5:
                char bookname[100];
                cout << "enter book name: ";
                cin.ignore();
                cin.getline(bookname, 100);
                library.displaybookbyname(bookname);
                break;
            case 6:
                int id;
                cout << "enter book id: ";
                cin >> id;
                library.displaybookbyid(id);
                break;
            case 7:
                return 0;
            default:
                cout << "invalid entry." << endl;
                break;
        }
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ... (Date, Room, and Guest classes are defined here)
class Date {
public:
    int day;
    int month;
    int year;

    Date() 
	{day=0;
	month=0;
	year=0;
	
	}
    Date(int d, int m, int y) 
	{day=d;
	month=m;
	year=y;
	}
};

class Room {
private:
    int roomNumber;
    string roomType;
    bool isAvailable;
    double price;

public:
    Room(int n, string t, double p)
	{roomNumber=n;
	 roomType=t;
	 price=p; 
	isAvailable=true; 
	
	}

    void displayDetails(){
        cout << "Room Number: " << roomNumber << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Price per night: $" << price << endl;
        cout << "Availability: " << (isAvailable ? "Available" : "Occupied") << endl;
    }

    bool checkAvailability()
	{
        return isAvailable;
    }

    void bookRoom()
	{
        isAvailable = false;
    }

    void freeRoom() 
	{
        isAvailable = true;
    }

    int getRoomNumber(){
        return roomNumber;
    }

    string getRoomType(){
        return roomType;
    }
};

class Guest {
private:
    string name;
    string contact;
    Date checkInDate;
    Date checkOutDate;
    int guestid;
    int roomNumber;
public:
    Guest(string n, string c, Date checkIn, Date checkOut,int id)
	{
     name=n; 
	 contact=contact; 
	 checkInDate=checkIn; 
	 checkOutDate=checkOut;
	 guestid=id;
	  }
	  void checkIn(Room& room) {
        cout << "Checking in guest: " << name << endl;
        room.bookRoom();
        roomNumber = room.getRoomNumber(); // Store the room number
    }

   
    void checkOut(Room& room) 
	{
        cout << "Checking out guest: " << name << endl;
        room.freeRoom();
    }

    string getName()
	{
        return name;
    }
    int getid()
    {
    	return guestid;
	}
	Date getCheckInDate() 
	 {
        return checkInDate;
    }
    Date getCheckOutDate()  {
        return checkOutDate;
    }

    bool isGuestInRoom(const Room& room) 
	{
        // Implement this function if needed
        return false;
    }
    int getRoomNumber() const {
        return roomNumber;
    }
};

class Hotel {
private:
    vector<Room> rooms;
    vector<Guest> guests;

public:
    Hotel() {
        // Initialize rooms with some sample data
        rooms.push_back(Room(101, "single", 100.0));
        rooms.push_back(Room(102, "single", 100.0));
        rooms.push_back(Room(201, "double", 150.0));
        rooms.push_back(Room(202, "double", 150.0));
        rooms.push_back(Room(301, "suite", 250.0));
        rooms.push_back(Room(302, "suite", 250.0));
    }

    void displayAvailableRooms(){
        cout << "Available Rooms:" << endl;
        for (size_t i = 0; i < rooms.size(); ++i) {
            if (rooms[i].checkAvailability()) {
                rooms[i].displayDetails();
                cout << endl;
            }
        }
    }

    void displayAllGuestDetails() {
        cout << "Guest Details:" << endl;
        for (size_t i = 0; i < guests.size(); ++i) {
            Guest& guest = guests[i];
            cout << "Guest ID: " << guest.getid() << endl;
            cout << "Name: " << guest.getName() << endl;
            cout << "Room Number: " << guest.getRoomNumber() << endl;
            cout << "Check-in Date: " << guest.getCheckInDate().day << "/" << guest.getCheckInDate().month << "/" << guest.getCheckInDate().year << endl;
            cout << "Check-out Date: " << guest.getCheckOutDate().day << "/" << guest.getCheckOutDate().month << "/" << guest.getCheckOutDate().year << endl;
            cout << "------------------------------------------" << endl;
        }
    }

   void checkInGuest(string name, string contact, Date checkIn, Date checkOut, string roomType, int guestid) {
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].checkAvailability() && roomType == rooms[i].getRoomType()) {
        	int a,b;
        	 b=rooms[i].getRoomNumber()/100;
            guestid=(rooms[i].getRoomNumber()/100)+(2*rooms[i].getRoomNumber()%100);
            Guest guest(name, contact, checkIn, checkOut, guestid);
            guest.checkIn(rooms[i]);
            guests.push_back(guest);
            a=rooms[i].getRoomNumber()%100;
            b=rooms[i].getRoomNumber()/100;
            guestid=(rooms[i].getRoomNumber()/100)+(2*rooms[i].getRoomNumber()%100);
            cout << "Guest " << name << " has been checked in to Room " << rooms[i].getRoomNumber() << "\nYour guest id is: " << guestid << ".\n";
            return;
        }
    }
    cout << "No available rooms of type " << roomType << " found." << endl;
}

    void checkOutGuest(int guestid) {
        for (size_t i = 0; i < guests.size(); ++i) {
            if (guests[i].getid() == guestid) {
                int roomNumber;
                cout << "Enter the room number to check out from: ";
                cin >> roomNumber;

                // Get the associated room using the room number
                Room& roomToCheckOut = getRoomByNumber(roomNumber);

                // Call checkOut method with the associated room
                guests[i].checkOut(roomToCheckOut);

                cout << "Guest " << guestid << " has been checked out from Room " << roomNumber << "." << endl;
                return;
            }
        }
        cout << "Guest with ID " << guestid << " not found or already checked out." << endl;
    }

   Room& getRoomByNumber(int roomNumber) {
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].getRoomNumber() == roomNumber) {
            return rooms[i]; // Return the room with matching room number
        }
    }
    // This should not happen if room information is managed correctly
    
}

    
};

int main() {
    Hotel hotel;

    int choice;
    do {
        cout << "Hotel Management System Menu:" << endl;
        cout << "1. Display available rooms" << endl;
        cout << "2. Check-in guest" << endl;
        cout << "3. Check-out guest" << endl;
        cout << "4. Display all guest details" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.displayAvailableRooms();
                break;

            case 2: {
                string name, contact, roomType;
                Date checkIn, checkOut;
                int guestid;
                cout << "Enter guest name: ";
                cin >> name;
                cout << "Enter contact information: ";
                cin >> contact;
                cout << "Enter check-in date (day month year): ";
                cin >> checkIn.day >> checkIn.month >> checkIn.year;
                cout << "Enter check-out date (day month year): ";
                cin >> checkOut.day >> checkOut.month >> checkOut.year;
                cout << "Enter room type (single, double, suite): ";
                cin >> roomType;
                // ... Input prompts for guest information
                hotel.checkInGuest(name, contact, checkIn, checkOut, roomType, guestid);
                break;
            }

            case 3: {
                int id;
                cout << "Enter guest ID to check-out: ";
                cin >> id;
                hotel.checkOutGuest(id);
                break;
            }

            case 4:
                hotel.displayAllGuestDetails();
                break;

            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}

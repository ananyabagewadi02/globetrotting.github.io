#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <limits> // for numeric_limits
#include <string> // for std::string
#include "colors.h" // for colored text

using namespace std;

// Accommodation structure to hold the data
struct Accommodation {
    string destination;
    string name;
    string roomType;
    int cost;
    int availability;

    Accommodation(string dest, string nm, string rt, int c, int avail)
        : destination(dest), name(nm), roomType(rt), cost(c), availability(avail) {}
};

// BookingHistory structure to hold the booking details
struct BookingHistory {
    string userName;
    string hotelName;
    string destination;
    string roomType;
    int cost;
    string dateBooked;

    BookingHistory(string user, string hotel, string dest, string rt, int c, string date)
        : userName(user), hotelName(hotel), destination(dest), roomType(rt), cost(c), dateBooked(date) {}
};

// Helper function to convert string to lowercase for case-insensitive comparison
string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Function to load accommodation data from file
void loadAccommodationData(map<string, vector<Accommodation>> &accommodationData, const string &filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string destination, type, name, roomType;
        int cost, availability;

        getline(ss, destination, ',');
        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, roomType, ',');
        ss >> cost;
        ss.ignore();
        ss >> availability;

        destination =(destination);
        name = (name);
        roomType = (roomType);

        accommodationData[destination].emplace_back(destination, name, roomType, cost, availability);
    }

    file.close();
}

void recommendAccommodation(map<string, vector<Accommodation>> &accommodationData, const string &destination, int budget) {
    string lowerDestination = toLowerCase(destination);

    if (accommodationData.find(lowerDestination) != accommodationData.end()) {
        cout << CYAN << "\n---------------------------------------\n";
        cout << MAGENTA << " Recommended accommodations in " << destination << " within your budget of " << budget << " INR:\n";
        cout << CYAN << "---------------------------------------\n";
        bool found = false;

        // Go through the accommodations for the given destination
        for (auto &acc : accommodationData[lowerDestination]) {
            if (acc.cost <= budget && acc.availability > 0) {
                cout << GREEN << "\nAccommodation Name: " << acc.name << "\n";
                cout << GREEN << "Room Type: " << acc.roomType << "\n";
                cout << GREEN << "Cost per Night: " << acc.cost << " INR\n";
                cout << GREEN << "Availability: " << acc.availability << " rooms\n";
                cout << CYAN << "-------------------------------\n";
                found = true;
            }
        }

        if (!found) {
            cout << RED << "\nSorry, no accommodations are available within your budget.\n";
        }
    } else {
        cout << RED << "\nNo accommodations found for the destination " << destination << ". Please ensure the spelling and case are correct.\n";
    }
}

// Function to check availability for a specific accommodation in a destination
void checkAccommodationAvailability(const map<string, vector<Accommodation>> &accommodationData, const string &destination, const string &accommodationName) {
    string lowerDestination = toLowerCase(destination);
    string lowerName = toLowerCase(accommodationName);

    if (accommodationData.find(lowerDestination) != accommodationData.end()) {
        bool found = false;
        for (const auto &acc : accommodationData.at(lowerDestination)) {
            if (toLowerCase(acc.name) == lowerName) {
                cout << CYAN << "\n---------------------------------------\n";
                cout << MAGENTA << "Accommodation Details:\n";
                cout << CYAN << "---------------------------------------\n";
                cout << GREEN << "Accommodation Name: " << acc.name << "\n";
                cout << GREEN << "Room Type: " << acc.roomType << "\n";
                cout << GREEN << "Cost per Night: " << acc.cost << " INR\n";
                cout << GREEN << "Availability: " << acc.availability << " rooms\n";
                cout << CYAN << "---------------------------------------\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << RED << "\nThe accommodation " << accommodationName << " was not found in " << destination << ".\n";
        }
    } else {
        cout << RED << "\nNo accommodations found for the destination " << destination << ".\n";
    }
}

// Function to sort accommodations by cost in ascending order
void sortAccommodationsByCost(map<string, vector<Accommodation>> &accommodationData, const string &destination) {
    string lowerDestination = toLowerCase(destination);

    if (accommodationData.find(lowerDestination) != accommodationData.end()) {
        vector<Accommodation> &accommodations = accommodationData[lowerDestination];
        sort(accommodations.begin(), accommodations.end(), [](const Accommodation &a, const Accommodation &b) {
            return a.cost < b.cost;
        });

        cout << CYAN << "\n---------------------------------------\n";
        cout << MAGENTA << "Accommodations in " << destination << " sorted by cost (ascending):\n";
        cout << CYAN << "---------------------------------------\n";

        for (const auto &acc : accommodations) {
            cout << GREEN << "Accommodation Name: " << acc.name << "\n";
            cout << GREEN << "Cost per Night: " << acc.cost << " INR\n";
            cout << CYAN << "---------------------------------------\n";
        }
    } else {
        cout << RED << "\nNo accommodations found for the destination " << destination << ".\n";
    }
}


void addNewAccommodation(map<string, vector<Accommodation>> &accommodationData, const string &destination) {
    string name, roomType;
    int cost, availability;

    cout << CYAN << "\n---------------------------------------\n";
    cout << MAGENTA << "Enter the details for the new accommodation:\n";
    cout << CYAN << "---------------------------------------\n";

    // Clear any leftover input in the buffer before calling getline()
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << GREEN << "Enter accommodation name: ";
    getline(cin, name);  // Read the full accommodation name

    // Debugging: Check if the name is captured correctly
    // cout << "Debug: Accommodation Name Entered: '" << name << "'\n";
    // cout << "Debug: Accommodation Name Entered: '" << name << "'\n";

    cout << GREEN << "Enter room type: ";
    getline(cin, roomType);  // Read the room type

    cout << GREEN << "Enter cost per night (INR): ";
    cin >> cost;  // Read the cost

    cout << GREEN << "Enter availability (number of rooms): ";
    cin >> availability;  // Read the availability

    // Add the new accommodation to the data structure
    Accommodation newAcc(destination, name, roomType, cost, availability);
    accommodationData[toLowerCase(destination)].push_back(newAcc);

    cout << CYAN << "\n---------------------------------------\n";
    cout << YELLOW << "New accommodation \"" << name << "\" added successfully in " << destination << ".\n";
    cout << CYAN << "---------------------------------------\n";
}

// Function to delete an existing accommodation
void deleteAccommodation(map<string, vector<Accommodation>> &accommodationData, const string &destination, const string &accommodationName) {
    string lowerDestination = toLowerCase(destination);
    string lowerName = toLowerCase(accommodationName);

    if (accommodationData.find(lowerDestination) != accommodationData.end()) {
        vector<Accommodation> &accommodations = accommodationData[lowerDestination];
        auto it = remove_if(accommodations.begin(), accommodations.end(), [&](const Accommodation &acc) {
            return toLowerCase(acc.name) == lowerName;
        });

        if (it != accommodations.end()) {
            accommodations.erase(it, accommodations.end());
            cout << CYAN << "\n---------------------------------------\n";
            cout << GREEN << "The accommodation \"" << accommodationName << "\" has been removed from " << destination << ".\n";
            cout << CYAN << "---------------------------------------\n";
        } else {
            cout << CYAN << "\n---------------------------------------\n";
            cout << RED << "Accommodation \"" << accommodationName << "\" not found in " << destination << ".\n";
            cout << CYAN << "---------------------------------------\n";
        }
    } else {
        cout << CYAN << "\n---------------------------------------\n";
        cout << RED << "No accommodations found for the destination " << destination << ".\n";
        cout << CYAN << "---------------------------------------\n";
    }
}


// Function to display all accommodations for a specific destination
void displayAllAccommodations(const map<string, vector<Accommodation>> &accommodationData, const string &destination) {
    string lowerDestination = toLowerCase(destination);

    if (accommodationData.find(lowerDestination) != accommodationData.end()) {
        cout << CYAN << "\n---------------------------------------\n";
        cout << MAGENTA << "All accommodations available in " << destination << ":\n";
        cout << CYAN << "---------------------------------------\n";

        for (const auto &acc : accommodationData.at(lowerDestination)) {
            cout << GREEN << "\nAccommodation Name: " << acc.name << "\n";
            cout << GREEN << "Room Type: " << acc.roomType << "\n";
            cout << GREEN << "Cost per Night: " << acc.cost << " INR\n";
            cout << GREEN << "Availability: " << acc.availability << " rooms\n";
            cout << CYAN << "---------------------------------------\n";
        }
    } else {
        cout << RED << "\nNo accommodations found for the destination " << destination << ". Please check the spelling or try another city.\n";
    }
}


void saveBookingHistory(const vector<BookingHistory> &bookingHistory, const string &filename);

void bookAccommodation(map<string, vector<Accommodation>> &accommodationData, vector<BookingHistory> &bookingHistory, const string &userName, const string &destination, const string &hotelName) {
    string lowerDestination = toLowerCase(destination);
    string lowerHotelName = toLowerCase(hotelName);

    if (accommodationData.find(lowerDestination) != accommodationData.end()) {
        for (auto &acc : accommodationData[lowerDestination]) {
            if (toLowerCase(acc.name) == lowerHotelName) {
                // Get the number of adults and children
                int adults, children;
                cout << GREEN << "\nEnter the number of adults: ";
                cin >> adults;
                cout << GREEN << "Enter the number of children: ";
                cin >> children;

                int totalGuests = adults + children;
                int requiredRooms = (totalGuests + 1) / 2; // Assuming 2 people per room

                if (acc.availability >= requiredRooms) {
                    // Booking successful
                    string currentDate = "2024-12-29"; // Placeholder for today's date (could be dynamic)
                    acc.availability -= requiredRooms; // Reduce availability

                    BookingHistory newBooking(userName, acc.name, destination, acc.roomType, acc.cost * requiredRooms, currentDate);
                    bookingHistory.push_back(newBooking);

                    cout << CYAN << "\n---------------------------------------\n";
                    cout << GREEN << "Your booking at " << acc.name << " in " << destination << " has been confirmed.\n";
                    cout << CYAN << "---------------------------------------\n";
                    cout << YELLOW << "Number of Adults: " << adults << "\n";
                    cout << YELLOW << "Number of Children: " << children << "\n";
                    cout << YELLOW << "Rooms Allocated: " << requiredRooms << "\n";
                    cout << YELLOW << "Room Type: " << acc.roomType << "\n"; // Displaying the type of room
                    cout << YELLOW << "Total Cost: " << (acc.cost * requiredRooms) << " INR\n";
                    cout << YELLOW << "Date of Booking: " << currentDate << "\n";
                    cout << CYAN << "---------------------------------------\n";
                    saveBookingHistory(bookingHistory, "booking_history.txt");
                    return;
                } else {
                    cout << RED << "\nSorry, only " << acc.availability << " rooms are available at " << acc.name << ".\n";
                    return;
                }
            }
        }
        cout << RED << "\nAccommodation " << hotelName << " not found in " << destination << ".\n";
    } else {
        cout << RED << "\nNo accommodations found for the destination " << destination << ".\n";
    }
}


// Function to load booking history from file
void loadBookingHistory(vector<BookingHistory> &bookingHistory, const string &filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string userName, hotelName, destination, roomType, dateBooked;
        int cost;

        getline(ss, userName, ',');
        getline(ss, hotelName, ',');
        getline(ss, destination, ',');
        getline(ss, roomType, ',');
        ss >> cost;
        ss.ignore();
        getline(ss, dateBooked, ',');

        bookingHistory.emplace_back(userName, hotelName, destination, roomType, cost, dateBooked);
    }

    file.close();
}

// Function to save booking history to file
void saveBookingHistory(const vector<BookingHistory> &bookingHistory, const string &filename) {
    ofstream file(filename);

    for (const auto &booking : bookingHistory) {
        file << booking.userName << ","
             << booking.hotelName << ","
             << booking.destination << ","
             << booking.roomType << ","
             << booking.cost << ","
             << booking.dateBooked << "\n";
    }

    file.close();
}

// Function to display booking history
void viewBookingHistory(const vector<BookingHistory> &bookingHistory) {
    if (bookingHistory.empty()) {
        cout << CYAN << "\n---------------------------------------\n";
        cout << RED << "No bookings have been made yet.\n";
        cout << CYAN << "---------------------------------------\n";
    } else {
        cout << CYAN << "\n---------------------------------------\n";
        cout << GREEN << "Booking History:\n";
        cout << CYAN << "---------------------------------------\n";

        for (const auto &booking : bookingHistory) {
            cout << YELLOW << "User: " << booking.userName << "\n";
            cout << YELLOW << "Hotel: " << booking.hotelName << "\n";
            cout << YELLOW << "Destination: " << booking.destination << "\n";
            cout << YELLOW << "Room Type: " << booking.roomType << "\n";
            cout << YELLOW << "Cost: " << booking.cost << " INR\n";
            cout << YELLOW << "Date of Booking: " << booking.dateBooked << "\n";
            cout << CYAN << "---------------------------------------\n";
        }
    }
}

// Function to save accommodation data to file
void saveAccommodationData(const map<string, vector<Accommodation>> &accommodationData, const string &filename) {
    ofstream file(filename);

    for (const auto &pair : accommodationData) {
        for (const auto &acc : pair.second) {
            file << acc.destination << ","
                 << "Hotel" << ","  // Assuming type is "Hotel"
                 << acc.name << ","
                 << acc.roomType << ","
                 << acc.cost << ","
                 << acc.availability << "\n";
        }
    }

    file.close();
}

// int main() {
//     map<string, vector<Accommodation>> accommodationData;
//     vector<BookingHistory> bookingHistory;
//     // Load the accommodation data from the file
//     loadAccommodationData(accommodationData, "accommodation.txt");
//     // Load the booking history from the file
//     loadBookingHistory(bookingHistory, "booking_history.txt");
//     string destination, accommodationName, userName;
//     int choice;
//     do {
//         // Clear screen and print the menu with colorful headers and spaces
//         cout << "\033[2J\033[1;1H";  // Clear screen command for Unix-based systems
//         cout << CYAN << "---------------------------------------\n";
//         cout << MAGENTA << "   Accommodation Management System Menu\n";
//         cout << CYAN << "---------------------------------------\n";
//         cout << BLUE << "1. Search accommodations by budget and destination\n";
//         cout << BLUE << "2. View all accommodations for a destination\n";
//         cout << BLUE << "3. Check availability for a specific accommodation\n";
//         cout << BLUE << "4. Sort accommodations by cost for a destination\n";
//         cout << BLUE << "5. Add a new accommodation\n";
//         cout << BLUE << "6. Delete an existing accommodation\n";
//         cout << BLUE << "7. Book accommodation\n";
//         cout << BLUE << "8. View booking history\n";
//         cout << BLUE << "9. Exit\n";
//         cout << CYAN << "---------------------------------------\n";
//         cout << "Enter your choice: ";
//         cin >> choice;
//         switch (choice) {
//             case 1:
//                 cout << GREEN << "\nEnter the destination city: ";
//                 cin.ignore();
//                 getline(cin, destination);
//                 cout << GREEN << "Enter your budget (in INR): ";
//                 cin >> choice;
//                 recommendAccommodation(accommodationData, destination, choice);
//                 break;
//             case 2:
//                 cout << GREEN << "\nEnter the destination city: ";
//                 cin.ignore();
//                 getline(cin, destination);
//                 displayAllAccommodations(accommodationData, destination);
//                 break;
//             case 3:
//                 cout << GREEN << "\nEnter the destination city: ";
//                 cin.ignore();
//                 getline(cin, destination);
//                 cout << GREEN << "Enter the accommodation name: ";
//                 getline(cin, accommodationName);
//                 checkAccommodationAvailability(accommodationData, destination, accommodationName);
//                 break;
//             case 4:
//                 cout << GREEN << "\nEnter the destination city: ";
//                 cin.ignore();
//                 getline(cin, destination);
//                 sortAccommodationsByCost(accommodationData, destination);
//                 break;
//             case 5:
//                 cout << GREEN << "\nEnter the destination city for the new accommodation: ";
//                 cin.ignore();
//                 getline(cin, destination);
//                 addNewAccommodation(accommodationData, destination);
//                 break;
//             case 6:
//                 cout << GREEN << "\nEnter the destination city: ";
//                 cin.ignore();
//                 getline(cin, destination);
//                 cout << GREEN << "Enter the accommodation name to delete: ";
//                 getline(cin, accommodationName);
//                 deleteAccommodation(accommodationData, destination, accommodationName);
//                 break;
//             case 7:
//                 cout << GREEN << "\nEnter your name: ";
//                 cin.ignore();
//                 getline(cin, userName);
//                 cout << GREEN << "Enter the destination city: ";
//                 getline(cin, destination);
//                 cout << GREEN << "Enter the accommodation name: ";
//                 getline(cin, accommodationName);
//                 bookAccommodation(accommodationData, bookingHistory, userName, destination, accommodationName);
//                 break;
//             case 8:
//                 viewBookingHistory(bookingHistory);
//                 break;
//             case 9:
//                 cout << GREEN << "\nThank you for using the Accommodation Management System. Goodbye!\n";
//                 break;
//             default:
//                 cout << RED << "\nInvalid choice! Please select a valid option.\n";
//         }
//         // Add spacing between choices for readability
//         cout << "\nPress Enter to continue...";
//         cin.ignore();
//         cin.get();
//     } while (choice != 9);
// // Save the accommodation data to the file before exiting
// saveAccommodationData(accommodationData, "accommodation.txt");
// saveBookingHistory(bookingHistory, "booking_history.txt");
// return 0;
// }

int acmenu()
{
    map<string, vector<Accommodation>> accommodationData;
    vector<BookingHistory> bookingHistory;

    // Load the accommodation data from the file
    loadAccommodationData(accommodationData, "accommodation.txt");

    // Load the booking history from the file
    loadBookingHistory(bookingHistory, "booking_history.txt");

    string destination, accommodationName, userName;
    int choice;

    do {
        // Clear screen and print the menu with colorful headers and spaces
        cout << "\033[2J\033[1;1H";  // Clear screen command for Unix-based systems
        cout << "\033[1;36m---------------------------------------\n";  // Cyan separator
        cout << "\033[1;35m   \033[1;4mAccommodation Management System Menu\033[0m\n";  // Magenta underlined menu title
        cout << "\033[1;36m---------------------------------------\n";  // Cyan separator

        // Menu options with color effects
        cout << "\033[1;33m1. \033[1;32mSearch accommodations by budget and destination\033[0m\n"; // Green text for option 1
        cout << "\033[1;33m2. \033[1;32mView all accommodations for a destination\033[0m\n"; // Green text for option 2
        cout << "\033[1;33m3. \033[1;32mCheck availability for a specific accommodation\033[0m\n"; // Green text for option 3
        cout << "\033[1;33m4. \033[1;32mSort accommodations by cost for a destination\033[0m\n"; // Green text for option 4
        cout << "\033[1;33m5. \033[1;32mAdd a new accommodation\033[0m\n"; // Green text for option 5
        cout << "\033[1;33m6. \033[1;32mDelete an existing accommodation\033[0m\n"; // Green text for option 6
        cout << "\033[1;33m7. \033[1;32mBook accommodation\033[0m\n"; // Green text for option 7
        cout << "\033[1;33m8. \033[1;32mView booking history\033[0m\n"; // Green text for option 8
        cout << "\033[1;33m9. \033[1;32mExit\033[0m\n"; // Green text for option 9
        cout << "\033[1;36m---------------------------------------\n";  // Cyan separator
        cout << "\033[1;34mEnter your choice: \033[0m"; // Blue text for user input prompt
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\033[1;32m\nEnter the destination city: "; // Green text
                cin.ignore();
                getline(cin, destination);
                cout << "\033[1;32mEnter your budget (in INR): "; // Green text
                cin >> choice;
                recommendAccommodation(accommodationData, destination, choice);
                break;

            case 2:
                cout << "\033[1;32m\nEnter the destination city: "; // Green text
                cin.ignore();
                getline(cin, destination);
                displayAllAccommodations(accommodationData, destination);
                break;

            case 3:
                cout << "\033[1;32m\nEnter the destination city: "; // Green text
                cin.ignore();
                getline(cin, destination);
                cout << "\033[1;32mEnter the accommodation name: "; // Green text
                getline(cin, accommodationName);
                checkAccommodationAvailability(accommodationData, destination, accommodationName);
                break;

            case 4:
                cout << "\033[1;32m\nEnter the destination city: "; // Green text
                cin.ignore();
                getline(cin, destination);
                sortAccommodationsByCost(accommodationData, destination);
                break;

            case 5:
                cout << "\033[1;32m\nEnter the destination city for the new accommodation: "; // Green text
                cin.ignore();
                getline(cin, destination);
                addNewAccommodation(accommodationData, destination);
                break;

            case 6:
                cout << "\033[1;32m\nEnter the destination city: "; // Green text
                cin.ignore();
                getline(cin, destination);
                cout << "\033[1;32mEnter the accommodation name to delete: "; // Green text
                getline(cin, accommodationName);
                deleteAccommodation(accommodationData, destination, accommodationName);
                break;

            case 7:
                cout << "\033[1;32m\nEnter your name: "; // Green text
                cin.ignore();
                getline(cin, userName);
                cout << "\033[1;32mEnter the destination city: "; // Green text
                getline(cin, destination);
                cout << "\033[1;32mEnter the accommodation name: "; // Green text
                getline(cin, accommodationName);
                bookAccommodation(accommodationData, bookingHistory, userName, destination, accommodationName);
                break;

            case 8:
                viewBookingHistory(bookingHistory);
                break;

            case 9:
                cout << "\033[1;36m\nThank you for using the Accommodation Management System.\033[0m\n";  // Cyan text
                cout << "\033[1;32mWe hope you had a great experience booking your stay!\033[0m\n"; // Green text
                cout << "\033[1;33mGoodbye, and have a wonderful day ahead!\033[0m\n";  // Yellow text
                break;

            default:
                cout << "\033[1;31m\nInvalid choice! Please select a valid option.\n"; // Red text for error
        }

        // Add spacing between choices for readability
        cout << "\n\033[1;33mPress Enter to continue... \033[0m";  // Yellow text for prompt
        cin.ignore();
        cin.get();

    } while (choice != 9);

    // Save the accommodation data to the file before exiting
    saveAccommodationData(accommodationData, "accommodation.txt");
    saveBookingHistory(bookingHistory, "booking_history.txt");

    return 0;
}

// int acmenu();

//  int main() {
//     acmenu();
//     return 0;
// }

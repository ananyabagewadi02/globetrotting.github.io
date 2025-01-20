#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "login.cpp"               // For login-related functionality
#include "accommodation.cpp"      // For accommodation allocation
#include "travelrouteopt.cpp"     // For travel route optimization
#include "tourpackage.cpp"        // For tour package management
#include "feedback.cpp"           // For tourist feedback analysis
#include "destrecommendation.cpp"
#include"colors.h"


// ANSI color codes for styling

using namespace std;
// Function to display a decorative title banner
void displayTitleBanner() {
    cout << MAGENTA << "=============================================" << endl;
    cout << MAGENTA << "          GLOBE TROTTING                   " << endl;
    cout << MAGENTA << "    TOURISM MANAGEMENT SYSTEM                " << endl;
    cout << MAGENTA << "=============================================" << endl << endl;
}

// Function to display section banners dynamically
void displaySectionBanner(const string& sectionTitle) {
    cout <<RED << "\n---------------------------------------------\n";
    cout << RED << "           " << sectionTitle << "           \n";
    cout << RED<< "---------------------------------------------\n\n";
}

// Function to display the main menu aesthetically
void displayMainMenu() {
    cout << "\n=============================================" << endl;
    cout << "                 MAIN MENU                    " << endl;
    cout << "=============================================" << endl;
    cout << "1. Destination Recommendation\n";
    cout << "2. Accommodation Allocation\n";
    cout << "3. Travel Route Optimization\n";
    cout << "4. Tour Package Management\n";
    cout << "5. Tourist Feedback Analysis\n";
    cout << "6. Logout\n";
    cout << "---------------------------------------------\n";
    cout << "Enter your choice: ";
}

void displayTourismMenu(map<string, vector<Accommodation>> &accommodationData) 
{
    while (true) {
        displayMainMenu();

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: 
                menu();
                break;
            case 2:
                acmenu();
                break;

            case 3:
                tmenu();
                break;
            
            case 4: 
                tpmenu();
                break;
            case 5: 
                fmenu();
                break;
            case 6:
                // Logout
                displaySectionBanner("Logging Out");
  
                // Display a beautiful logout message
                cout << CYAN << "----------------------------------------\n";
                cout << CYAN << "   Thank you for using Travel Route Optimization! \n";
                cout << CYAN << "        Your journey is important to us.\n";
                cout << CYAN << "            See you again soon! \n";
                cout << CYAN << "----------------------------------------\n";


                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() 
{
    // Display the initial banner once
    displayTitleBanner();

    // Load accommodation data
    map<string, vector<Accommodation>> accommodationData;
    loadAccommodationData(accommodationData, "accommodation.txt");  // Load data from file

    int choice;

    do {
        cout << BLUE  << "\n--- Tourism Management System: Login Page ---\n" << RESET;
        cout << BLUE << "1. User Login\n";
        cout << "2. Admin Login\n";
        cout << "3. Exit\n";
        cout << BLUE << "Enter your choice: " << RESET;
        cin >> choice;

        switch (choice) {
            case 1: {
                int userChoice;
                do {
                    cout << BLUE  << "\n--- User Menu ---\n" << RESET;
                    cout << "1. Register\n";
                    cout << "2. Login\n";
                    cout << "3. Forget Password\n";
                    cout << "4. Back\n";
                    cout << BLUE << "Enter your choice: " << RESET;
                    cin >> userChoice;

                    switch (userChoice) {
                        case 1:
                            registerUser();
                            break;
                        case 2:
                            loginUser();
                            displayTourismMenu(accommodationData) ;
                            break;
                        case 3:
                            forgetPassword();
                            break;
                        case 4:
                            cout << GREEN << "Returning to main menu...\n" << RESET;
                            break;
                        default:
                            cout << RED << "Invalid choice. Please try again.\n" << RESET;
                    }
                } while (userChoice != 4);
                break;
            }
            case 2: {
                adminLoginOrRegister(); 
                int adminChoice;
                if (adminLogin()) {
                    adminMenu(); 
                }
                break;
            }
            case 3:
                cout << GREEN << "Exiting...\n" << RESET;
                exitMessage();
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    } while (choice != 3);

    return 0;
}


int pmenu() {
    int choice;

    while (true) {
        // Display the headline
        std::cout << BLUE 
                  << "============================================================\n"
                  << "                  TOUR MANAGEMENT SYSTEM                    \n"
                  << "============================================================"
                  << RESET << "\n\n";
        // Display the menu with colors
        std::cout  << BLUE << "\n1. Add Tour Package\n" << RESET;
        std::cout  << BLUE << "2. Display Tour Packages\n" << RESET;
        std::cout  << BLUE << "3. Delete Tour Package\n" << RESET;
        std::cout  << BLUE << "4. Update Tour Package\n" << RESET;
        std::cout  << BLUE << "5. View Tour Packages by Season\n" << RESET;  // Added
        std::cout  << BLUE << "6. View Tour Packages by Weather\n" << RESET;  // Added
        std::cout  << BLUE << "7. Book a Trip\n" << RESET;  // Added booking option
        std::cout  << BLUE << "8. View Booking History\n" << RESET;  // Added booking history option
        std::cout  << BLUE << "9. Sort Tour Packages by Price\n" << RESET;  // Added sort option
        std::cout  << RED << "10. Exit\n" << RESET;
        std::cout  << YELLOW << "Enter your choice: " << RESET;
        std::cin >> choice;
        std::cin.ignore();  // To ignore any leftover newline character

        // Load tour packages from the file
        std::vector<TourPackage> packages;
        std::ifstream file("tour_packages.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                TourPackage package;
                std::getline(iss, package.destination, ',');
                std::string price;
                std::getline(iss, price, ',');
                package.price = std::stod(price);
                std::getline(iss, package.duration, ',');
                std::getline(iss, package.season, ',');
                std::getline(iss, package.weather, ',');
                packages.push_back(package);
            }
            file.close();
        } else {
            std::cerr  << RED << "Unable to open file!" << RESET << std::endl;
        }

        // Execute the selected option
        switch (choice) {
            case 1:
                std::cout  << GREEN << "Adding a new tour package..." << RESET << std::endl;
                addTourPackage();  // Function to add a new tour package
                break;
            case 2:
                std::cout  << CYAN << "Displaying all tour packages..." << RESET << std::endl;
                displayTourPackages(packages.data(), packages.size());  // Display all tour packages
                break;
            case 3:
                std::cout << YELLOW << "Deleting a tour package..." << RESET << std::endl;
                deleteTourPackage();  // Function to delete a tour package
                break;
            case 4:
                std::cout << RED << "Updating a tour package..." << RESET << std::endl;
                updateTourPackage();  // Function to update a tour package
                break;
            case 5:
                std::cout << MAGENTA << "Viewing tour packages by season..." << RESET << std::endl;
                viewTourPackagesBySeason();  // Call the function for viewing by season
                break;
            case 6:
                std::cout << BLUE << "Viewing tour packages by weather..." << RESET << std::endl;
                viewTourPackagesByWeather();  // Call the function for viewing by weather
                break;
            case 7:
                std::cout << CYAN << "Booking a trip..." << RESET << std::endl;
                bookTourPackage();  // Call the booking function
                break;
            case 8:
                std::cout << GREEN << "Viewing booking history..." << RESET << std::endl;
                bookingHistory();  // Call the view booking history function
                break;
            case 9:
                std::cout  << CYAN << "Sorting tour packages by price..." << RESET << std::endl;
                sortTourPackagesByPrice();  // Call the sorting function
                break;
            case 10:
                std::cout  << RED << "Exiting..." << RESET << std::endl;
                std::cout  << RED 
                          << "\n============================================================\n"
                          << "                Thank You for Using Our System!             \n"
                          << "                    Have a Great Day Ahead!                 \n"
                          << "============================================================\n"
                          << RESET << std::endl;
                return 0;  // Exit the program
            default:
                std::cout  << YELLOW << "Invalid choice! Please enter a valid option." << RESET << std::endl;
        }
    }

    return 0;
}

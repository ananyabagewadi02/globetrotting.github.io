int tpmenu() {
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

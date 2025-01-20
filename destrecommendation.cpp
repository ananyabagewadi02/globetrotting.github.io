#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> // Include this header for sort function
#include <stdexcept> // Include this header for invalid_argument and out_of_range exceptions
#include <iomanip>
#include <ios> // Include this header for ios_base
#include "colors.h" // Include this header for colored text

using namespace std;

struct Destination {
    string name;
    string type;
    int budget;
    int days;
    string description;
};

void recommendDestinationsByTimeOfYear();  // Added declaration
void sortDestinationsByBudget();  // Added declaration
void filterDestinationsByBudget();
void filterDestinationsByDuration();
void viewAllDestinations();
void searchDestinationByName();


vector<Destination> loadDestinations(const string& filePath) {
    vector<Destination> destinations;
    ifstream file(filePath);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name, type, budgetStr, daysStr, description;

        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, budgetStr, ',');
        getline(ss, daysStr, ',');
        getline(ss, description); // The rest of the line is the description

        try {
            Destination dest = {name, type, stoi(budgetStr), stoi(daysStr), description};
            destinations.push_back(dest);
        } catch (const invalid_argument& e) {
            cerr << RED << "Error: Invalid data in destinations.txt: " << line << RESET << endl;
        } catch (const out_of_range& e) {
            cerr << RED << "Error: Budget or days value out of range in destinations.txt: " << line << RESET << endl;
        }
    }

    return destinations;
}

void recommendDestinations() {
    string name;
    int budget, days;
    string destinationType;

    cout << CYAN << "Enter your name: " << RESET;
    cin >> name;
    cout << CYAN << "Enter your budget: " << RESET;
    cin >> budget;
    cout << CYAN << "Enter the number of days you want to spend: " << RESET;
    cin >> days;
    cout << CYAN << "Enter the type of destination (e.g., beach, historical, hillstation, religious): " << RESET;
    cin >> destinationType;
    cout<<GREEN<<"Welcome "<<name<<"!"<<RESET<<endl;

    vector<Destination> destinations = loadDestinations("destinations.txt");
    bool found = false;

    // Printing header for the table
    cout << GREEN << "+--------------------------------------------------------------------------+" << endl;
    cout << "| " << setw(20) << left << "Destination Name" 
         << "| " << setw(15) << left << "Budget" 
         << "| " << setw(10) << left << "Days" 
         << "| " << setw(20) << left << "Description" << " |" << endl;
    cout << GREEN << "+--------------------------------------------------------------------------+" << endl;

    for (const auto& dest : destinations) {
        if (dest.budget <= budget && dest.days <= days && dest.type == destinationType) {
            // Printing destination details in a row of the table
            cout << BLUE << "| " << setw(20) << left << dest.name
                 << "| " << setw(15) << left << dest.budget
                 << "| " << setw(10) << left << dest.days
                 << "| " << setw(20) << left << dest.description << " |" << RESET << endl;
            found = true;
        }
    }

    if (!found) {
    }

    // Closing the table
    cout << GREEN << "+--------------------------------------------------------------------------+" << endl;
}

void showCityDetails() {
    string city;
    cout << CYAN << "Enter the name of the destination: " << RESET;
    cin >> city;

    ifstream file("city_details.txt");
    string line;
    bool found = false;

    // Adding a table header
    cout << GREEN << "+------------------------+-----------------------------------------------+" << endl;
    cout << "| " << setw(22) << left << "City Name" << "| " << setw(45) << left << "Key Attractions" << " |" << endl;
    cout << "+------------------------+-----------------------------------------------+" << RESET;

    while (getline(file, line)) {
        stringstream ss(line);
        string cityName, type, keyAttractions, additionalInfo;

        getline(ss, cityName, ',');
        getline(ss, type, ',');
        getline(ss, keyAttractions, ',');
        getline(ss, additionalInfo);

        if (cityName == city) {
            found = true;

            // City information in a neat table
            cout << GREEN << "\n+-------------------------------------------------------+" << endl;
            cout << "| " << setw(22) << left << "City Name" << "| " << setw(45) << left << cityName << " |" << endl;
            cout << "+-------------------------------------------------------+" << endl;
            cout << "| " << setw(22) << left << "Type" << "| " << setw(45) << left << type << " |" << endl;
            cout << "| " << setw(22) << left << "Key Attractions" << "| " << setw(45) << left << keyAttractions << " |" << endl;
            cout << "| " << setw(22) << left << "Additional Info" << "| " << setw(45) << left << additionalInfo << " |" << endl;
            cout << "+-------------------------------------------------------+" << endl;

            // If the description has multiple lines, split it and display each part
            cout << YELLOW << "\nAdditional Description: " << RESET << endl;
            stringstream descriptionStream(additionalInfo);
            string descriptionLine;
            while (getline(descriptionStream, descriptionLine, ',')) {
                cout << "  * " << descriptionLine << endl;
            }
        }
    }

    if (!found) {
        cout << RED << "\nSorry, details for this city are not available.\n" << RESET;
    }
}

void recommendDestinationsByType() {
    string type;
    cout << BLUE << "Enter the type of destination (e.g., beach, historical, hillstation, religious): " << RESET;
    cin >> type;

    vector<Destination> destinations = loadDestinations("destinations.txt");
    bool found = false;

    cout << CYAN << "\nRecommended destinations of type \"" << type << "\":\n" << RESET;

    // Print table header
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "| Destination Name       | Type             | Budget | Days  | Description                           |\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    for (const auto& dest : destinations) {
        if (dest.type == type) {
            found = true;
            cout << GREEN << "| " << setw(22) << left << dest.name
                 << "| " << setw(16) << left << dest.type
                 << "| " << setw(6) << right << dest.budget
                 << "| " << setw(6) << right << dest.days
                 << "| " << setw(37) << left << dest.description << "|\n";
        }
    }

    if (!found) {
        cout << RED << "\nNo destinations found for the type \"" << type << "\".\n" << RESET;
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

void menu() {
    cout << GREEN << "+-----------------------------------------------------------+" << endl;
    cout << "| " << setw(20) << left << "Destination Recommendation" << " |" << endl;
    cout << "+-----------------------------------------------------------+" << RESET;

    while (true) {
        cout << CYAN << "\n1. Recommend Destinations" << RESET << endl;
        cout << CYAN << "2. Show City Details" << RESET << endl;
        cout << CYAN << "3. View All Destinations" << RESET << endl;
        cout << CYAN << "4. Search Destination by Name" << RESET << endl;
        cout << CYAN << "5. Filter Destinations by Budget" << RESET << endl;
        cout << CYAN << "6. Filter Destinations by Duration" << RESET << endl;
        cout << CYAN << "7. Filter Destinations by Type" << RESET << endl;
        cout << CYAN << "8. Filter Destinations by Time of Year" << RESET << endl;  // Added option
        cout << CYAN << "9. Sort Destinations by Budget" << RESET << endl;  // Added option
        cout << CYAN << "10. Exit" << RESET << endl;
        cout << YELLOW << "Enter your choice: " << RESET;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << GREEN << "You chose to recommend destinations!" << RESET << endl;
                recommendDestinations();
                break;
            case 2:
                cout << GREEN << "You chose to show city details!" << RESET << endl;
                showCityDetails();
                break;
            case 3:
                cout << GREEN << "You chose to view all destinations!" << RESET << endl;
                viewAllDestinations();
                break;
            case 4:
                cout << GREEN << "You chose to search a destination by name!" << RESET << endl;
                searchDestinationByName();
                break;
            case 5:
                cout << GREEN << "You chose to filter destinations by budget!" << RESET << endl;
                filterDestinationsByBudget();
                break;
            case 6:
                cout << GREEN << "You chose to filter destinations by duration!" << RESET << endl;
                filterDestinationsByDuration();
                break;
            case 7:
                cout << GREEN << "You chose to filter destinations by type!" << RESET << endl;
                recommendDestinationsByType();
                break;
            case 8:
                cout << GREEN << "You chose to filter destinations by time of year!" << RESET << endl;
                recommendDestinationsByTimeOfYear();  // Added option
                break;
            case 9:
                cout << GREEN << "You chose to sort destinations by budget!" << RESET << endl;
                sortDestinationsByBudget();  // Added option
                break;
            case 10:

                cout << CYAN << "Thank you for using our destination recommendation service!" << RESET << endl;
                cout << "\033[1;33mGoodbye, and have a wonderful day ahead!\033[0m\n";  // Yellow text
  
                cout << MAGENTA << "Goodbye!" << RESET << endl;
                return;
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
        }
    }
}

void menu();
// int main() {
//     menu();
//     return 0;
// }

void viewAllDestinations() {
    vector<Destination> destinations = loadDestinations("destinations.txt");

    cout << CYAN << "\nAll Available Destinations:\n" << RESET;

    // Print table header
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "| Destination Name       | Type             | Budget | Days  | Description                           |\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    for (const auto& dest : destinations) {
        cout << GREEN << "| " << setw(22) << left << dest.name
             << "| " << setw(16) << left << dest.type
             << "| " << setw(6) << right << dest.budget
             << "| " << setw(6) << right << dest.days
             << "| " << setw(37) << left << dest.description << "|\n";
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

void searchDestinationByName() {
    string searchName;
    cout << BLUE << "Enter the name of the destination to search: " << RESET;
    cin >> searchName;

    vector<Destination> destinations = loadDestinations("destinations.txt");
    bool found = false;

    cout << CYAN << "\nSearch results for \"" << searchName << "\":\n" << RESET;

    // Print table header
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "| Destination Name       | Type             | Budget | Days  | Description                           |\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    for (const auto& dest : destinations) {
        if (dest.name == searchName) {
            found = true;
            cout << GREEN << "| " << setw(22) << left << dest.name
                 << "| " << setw(16) << left << dest.type
                 << "| " << setw(6) << right << dest.budget
                 << "| " << setw(6) << right << dest.days
                 << "| " << setw(37) << left << dest.description << "|\n";
        }
    }

    if (!found) {
        cout << RED << "\nNo destination found with the name \"" << searchName << "\".\n" << RESET;
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

void filterDestinationsByBudget() {
    int budget;
    cout << BLUE << "Enter your budget: " << RESET;
    cin >> budget;

    vector<Destination> destinations = loadDestinations("destinations.txt");
    bool found = false;

    cout << CYAN << "\nDestinations within your budget of " << budget << ":\n" << RESET;
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "+ Destination Name       | Type             | Budget | Days  | Description                           +\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    for (const auto& dest : destinations) {
        if (dest.budget <= budget) {
            found = true;
            cout << GREEN << "| " << setw(22) << left << dest.name
                 << "| " << setw(16) << left << dest.type
                 << "| " << setw(6) << right << dest.budget
                 << "| " << setw(6) << right << dest.days
                 << "| " << setw(37) << left << dest.description << "|\n";
        }
    }

    if (!found) {
        cout << RED << "\nNo destinations found within your budget.\n" << RESET;
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

void filterDestinationsByDuration() {
    int days;
    cout << BLUE << "Enter the number of days you want to travel: " << RESET;
    cin >> days;

    vector<Destination> destinations = loadDestinations("destinations.txt");
    bool found = false;

    cout << CYAN << "\nDestinations for " << days << " days or less:\n" << RESET;
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "+ Destination Name       | Type             | Budget | Days  | Description                           +\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    for (const auto& dest : destinations) {
        if (dest.days <= days) {
            found = true;
            cout << GREEN << "| " << setw(22) << left << dest.name
                 << "| " << setw(16) << left << dest.type
                 << "| " << setw(6) << right << dest.budget
                 << "| " << setw(6) << right << dest.days
                 << "| " << setw(37) << left << dest.description << "|\n";
        }
    }

    if (!found) {
        cout << RED << "\nNo destinations found for your selected duration.\n" << RESET;
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

void recommendDestinationsByTimeOfYear() {
    string timeOfYear;
    cout << BLUE << "Enter the time of year you want to travel (e.g., summer, winter, monsoon): " << RESET;
    cin >> timeOfYear;

    vector<Destination> destinations = loadDestinations("destinations.txt");
    bool found = false;

    cout << CYAN << "\nRecommended destinations for " << timeOfYear << " travel:\n" << RESET;
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "+ Destination Name       | Type             | Budget | Days  | Description                           +\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    for (const auto& dest : destinations) {
        if (dest.description.find(timeOfYear) != string::npos) {  // Check if description contains the time of year
            found = true;
            cout << GREEN << "| " << setw(22) << left << dest.name
                 << "| " << setw(16) << left << dest.type
                 << "| " << setw(6) << right << dest.budget
                 << "| " << setw(6) << right << dest.days
                 << "| " << setw(37) << left << dest.description << "|\n";
        }
    }

    if (!found) {
        cout << RED << "\nNo destinations found for travel during the " << timeOfYear << " season.\n" << RESET;
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

void sortDestinationsByBudget() {
    vector<Destination> destinations = loadDestinations("destinations.txt");

    // Sorting destinations by budget in ascending order
    sort(destinations.begin(), destinations.end(), [](const Destination& a, const Destination& b) {
        return a.budget < b.budget;
    });

    cout << CYAN << "\nDestinations sorted by Budget (ascending):\n" << RESET;
    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n";
    cout << "+ Destination Name       | Type             | Budget | Days  | Description                           +\n";
    cout << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;

    // Loop through destinations and display in a tabular format
    for (const auto& dest : destinations) {
        cout << GREEN << "| " << setw(22) << left << dest.name
             << "| " << setw(16) << left << dest.type
             << "| " << setw(6) << right << dest.budget
             << "| " << setw(6) << right << dest.days
             << "| " << setw(37) << left << dest.description << "|\n";
    }

    cout << GREEN << "+------------------------+------------------+--------+-------+---------------------------------------+\n" << RESET;
}

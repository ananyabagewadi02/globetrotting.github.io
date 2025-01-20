// Include the necessary header files for I/O, file handling, and string manipulations
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "colors.h"

// Use the standard namespace to avoid prefixing std::
using namespace std;


// Class to manage and analyze tourist feedback
class TouristFeedbackAnalysis {
public:


    // Function to submit feedback from a tourist
    void submitFeedback(const string &touristName, const string &destination, int rating, const string &comment) {
        ofstream file("tourist_feedback.txt", ios::app);
        file << touristName << "," << destination << "," << rating << "," << comment << endl;
        cout << GREEN << "Feedback submitted successfully!" << RESET << endl;
        file.close();
    }

    // Function to analyze feedback for all destinations
    void analyzeFeedback() {
        ifstream file("tourist_feedback.txt");
        string line;
        map<string, pair<int, int>> destinationFeedback;

        while (getline(file, line)) {
            stringstream ss(line);
            string touristName, destination, comment;
            int rating;

            getline(ss, touristName, ',');
            getline(ss, destination, ',');
            ss >> rating;
            ss.ignore();
            getline(ss, comment);

            destinationFeedback[destination].first += rating;
            destinationFeedback[destination].second += 1;
        }
        file.close();

        cout << BLUE << "\nTourist Feedback Analysis:" << RESET << endl;
        for (const auto &entry : destinationFeedback) {
            string destination = entry.first;
            int totalRating = entry.second.first;
            int numRatings = entry.second.second;
            double avgRating = (numRatings > 0) ? static_cast<double>(totalRating) / numRatings : 0.0;
            cout << YELLOW << "Destination: " << destination << RESET << "\n";
            cout << "Number of Ratings: " << numRatings << "\n";
            cout << "Average Rating: " << avgRating << "/5\n\n";
        }
    }

    // Function to print feedback for a specific destination
    void printFeedbackForDestination(const string &destination) {
        // Open the feedback file in read mode
        ifstream file("tourist_feedback.txt");
        // Declare a string variable to store each line from the file
        string line;
        
        // Print the header for feedback for a specific destination
        cout << BLUE << "\nFeedback for " << destination << ":" << RESET << endl;
        // Read the file line by line
        while (getline(file, line)) {
            // Create a stringstream to parse the line into components
            stringstream ss(line);
            // Declare variables to hold tourist name, destination, comment, and rating
            string touristName, feedbackDestination, comment;
            int rating;

            // Extract tourist name, destination, rating, and comment from the line
            getline(ss, touristName, ',');
            getline(ss, feedbackDestination, ',');
            ss >> rating;
            ss.ignore();  // Ignore the comma after rating
            getline(ss, comment);

            // If the destination in the feedback matches the input destination, print the feedback
            if (feedbackDestination == destination) {
                cout << YELLOW << "Tourist: " << touristName << RESET 
                     << ", Rating: " << rating << "/5, Comment: " << comment << "\n";
            }
        }
        // Close the file after reading all feedback
        file.close();
    }

    // Rank destinations by popularity
    void rankDestinationsByPopularity() {
        ifstream file("tourist_feedback.txt");
        string line;
        map<string, int> destinationPopularity;

        while (getline(file, line)) {
            stringstream ss(line);
            string touristName, destination, comment;
            int rating;

            getline(ss, touristName, ',');
            getline(ss, destination, ',');
            ss >> rating;
            ss.ignore();
            getline(ss, comment);

            destinationPopularity[destination]++;
        }
        file.close();

        // Sort destinations by popularity
        vector<pair<string, int>> rankedDestinations(destinationPopularity.begin(), destinationPopularity.end());
        sort(rankedDestinations.begin(), rankedDestinations.end(),
             [](const pair<string, int> &a, const pair<string, int> &b) {
                 return a.second > b.second;
             });

        cout << BLUE << "\nRanking of Destinations by Popularity:" << RESET << endl;
        for (const auto &entry : rankedDestinations) {
            cout << YELLOW << "Destination: " << entry.first << RESET << ", Feedback Count: " << entry.second << endl;
        }
    }

    // Perform sentiment analysis on feedback
    void performSentimentAnalysis() {
        ifstream file("tourist_feedback.txt");
        string line;

        map<string, pair<int, int>> sentimentCounts;

        while (getline(file, line)) {
            stringstream ss(line);
            string touristName, destination, comment;
            int rating;

            getline(ss, touristName, ',');
            getline(ss, destination, ',');
            ss >> rating;
            ss.ignore();
            getline(ss, comment);

            int sentimentScore = 0;

            // Basic sentiment analysis using keyword matching
            if (comment.find("good") != string::npos || comment.find("excellent") != string::npos ||
                comment.find("amazing") != string::npos) {
                sentimentScore = 1;
            } else if (comment.find("bad") != string::npos || comment.find("poor") != string::npos ||
                       comment.find("terrible") != string::npos) {
                sentimentScore = -1;
            }

            sentimentCounts[destination].first += sentimentScore > 0 ? 1 : 0; // Positive sentiments
            sentimentCounts[destination].second += sentimentScore < 0 ? 1 : 0; // Negative sentiments
        }
        file.close();

        cout << BLUE << "\nSentiment Analysis of Feedback:" << RESET << endl;
        for (const auto &entry : sentimentCounts) {
            cout << YELLOW << "Destination: " << entry.first << RESET << "\n";
            cout << "Positive Comments: " << entry.second.first << "\n";
            cout << "Negative Comments: " << entry.second.second << "\n\n";
        }
    }

    // Export feedback analysis to a file
    void exportFeedbackAnalysisToFile() {
        ifstream file("tourist_feedback.txt");
        string line;
        map<string, pair<int, int>> destinationFeedback;

        while (getline(file, line)) {
            stringstream ss(line);
            string touristName, destination, comment;
            int rating;

            getline(ss, touristName, ',');
            getline(ss, destination, ',');
            ss >> rating;
            ss.ignore();
            getline(ss, comment);

            destinationFeedback[destination].first += rating;
            destinationFeedback[destination].second += 1;
        }
        file.close();

        ofstream outFile("feedback_analysis.txt");
        outFile << "Destination,Number of Ratings,Average Rating\n";

        for (const auto &entry : destinationFeedback) {
            string destination = entry.first;
            int totalRating = entry.second.first;
            int numRatings = entry.second.second;
            double avgRating = (numRatings > 0) ? static_cast<double>(totalRating) / numRatings : 0.0;
            outFile << destination << "," << numRatings << "," << avgRating << "\n";
        }

        outFile.close();
        cout << GREEN << "Feedback analysis exported to 'feedback_analysis.txt'." << RESET << endl;
    }
};

// Main function to demonstrate tourist feedback submission and analysis
int fmenu() {
    TouristFeedbackAnalysis feedbackAnalysis;
    int choice;

    do {
        cout << "\033[1;36m---------------------------------------\n";  // Cyan separator
        cout << "\033[1;35m   \033[1;4mFeedback Analysis Menu\033[0m\n";  // Magenta underlined menu title
        cout << "\033[1;36m---------------------------------------\n";  // Cyan separator        cout << BLUE<< "1. Submit Feedback\n";
        cout << BLUE<< "1. Submit Feedback1\n";
        cout << BLUE<< "2. Analyze Feedback for All Destinations\n";
        cout << BLUE<< "3. View Feedback for a Destination\n";
        cout << BLUE<< "4. Rank Destinations by Popularity\n";
        cout << BLUE<< "5. Export Feedback Analysis to File\n";
        cout << BLUE<< "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {
            case 1: {
                string touristName, destination, comment;
                int rating;
                cout << YELLOW << "Enter your name: " << RESET;
                getline(cin, touristName);
                cout << YELLOW << "Enter the destination you visited: " << RESET;
                getline(cin, destination);
                cout << YELLOW << "Rate the destination (1-5): " << RESET;
                cin >> rating;
                cin.ignore();
                cout << YELLOW << "Leave a comment: " << RESET;
                getline(cin, comment);

                feedbackAnalysis.submitFeedback(touristName, destination, rating, comment);
                break;
            }
            case 2:
                feedbackAnalysis.analyzeFeedback();
                break;
            case 3: {
                string destination;
                cout << YELLOW << "Enter the destination to view feedback: " << RESET;
                getline(cin, destination);
                feedbackAnalysis.printFeedbackForDestination(destination);
                break;
            }
            case 4:
                feedbackAnalysis.rankDestinationsByPopularity();
                break;

            case 5:
                feedbackAnalysis.exportFeedbackAnalysisToFile();
                break;
            case 6:
                cout << GREEN << "Thank you for using the Tourist Feedback Analysis system!" << RESET << endl;
                return 0;
            default:
                cout << RED << "Invalid choice! Please try again." << RESET << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}

int fmenu();
// int main() {
//     fmenu();
//     return 0;
// }

int fmeu() {
    TouristFeedbackAnalysis feedbackAnalysis;
    int choice;

    do {
        cout << BLUE << "\nTourist Feedback Analysis Menu" << RESET << endl;
        cout << "1. Submit Feedback\n";
        cout << "2. Analyze Feedback for All Destinations\n";
        cout << "3. View Feedback for a Destination\n";
        cout << "4. Rank Destinations by Popularity\n";
        cout << "5. Perform Sentiment Analysis\n";
        cout << "6. Export Feedback Analysis to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice) {
            case 1: {
                string touristName, destination, comment;
                int rating;
                cout << YELLOW << "Enter your name: " << RESET;
                getline(cin, touristName);
                cout << YELLOW << "Enter the destination you visited: " << RESET;
                getline(cin, destination);
                cout << YELLOW << "Rate the destination (1-5): " << RESET;
                cin >> rating;
                cin.ignore();
                cout << YELLOW << "Leave a comment: " << RESET;
                getline(cin, comment);

                feedbackAnalysis.submitFeedback(touristName, destination, rating, comment);
                break;
            }
            case 2:
                feedbackAnalysis.analyzeFeedback();
                break;
            case 3: {
                string destination;
                cout << YELLOW << "Enter the destination to view feedback: " << RESET;
                getline(cin, destination);
                feedbackAnalysis.printFeedbackForDestination(destination);
                break;
            }
            case 4:
                feedbackAnalysis.rankDestinationsByPopularity();
                break;
            case 5:
                feedbackAnalysis.performSentimentAnalysis();
                break;
            case 6:
                feedbackAnalysis.exportFeedbackAnalysisToFile();
                break;
            case 7:
                cout << GREEN << "Thank you for using the Tourist Feedback Analysis system!" << RESET << endl;
                break;
            default:
                cout << RED << "Invalid choice! Please try again." << RESET << endl;
                break;
        }
    } while (choice != 7);

    return 0;
}


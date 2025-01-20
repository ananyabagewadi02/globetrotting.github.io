#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip> // For formatting table
#include <sstream> // For string manipulation
#include <conio.h>
#include <algorithm> // For transform function to handle case insensitivity
#include <regex> // For password strength check
#include"colors.h"

// ANSI color codes for styling

using namespace std;

// Utility function to trim whitespace from a string
void trim(string& str) {
    str.erase(0, str.find_first_not_of(' '));  // Trim leading whitespace
    str.erase(str.find_last_not_of(' ') + 1);  // Trim trailing whitespace
}

// Function prototypes
void registerUser();
void loginUser();
void viewLoginHistory();
void searchHistoryByName();
void viewAllHistory();
void forgetPassword();
void resetPassword(const string& username);
void lockAccount(string username);
bool isPasswordStrong(string password);
void updateProfile(string username);
void viewProfile(string username);
void deleteUserAccount(string username);
void logUserAction(const string& username, const string& action);
void changePassword(string username);
void logout();
void adminControlPanel();
void exitMessage();
string getCurrentTimestamp();
string getMaskedInput();
void adminRegister();
bool adminLogin();
void adminLoginOrRegister();
void adminMenu();



int login() {
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


void adminLoginOrRegister() {
    int choice;
    do {
        cout << BLUE << "\n--- Admin Login/Register ---\n" << RESET;
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Back\n";
        cout << BLUE << "Enter your choice: " << RESET;
        cin >> choice;

        switch (choice) {
            case 1:
                adminRegister();
                break;
            case 2:
                if (!adminLogin()) {
                    cout << RED << "Login failed. Returning to menu.\n" << RESET;
                }
                else {
                    adminMenu();
                }
                break;
            case 3:
                cout << GREEN << "Returning to main menu...\n" << RESET;
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    } while (choice != 3);
}


bool adminLogin() {
    string username, password, storedUser, storedPass;
    cout << YELLOW << "\nEnter Admin Username: " << RESET;
    cin >> username;
    cout << YELLOW << "Enter Password: " << RESET;
    password = getMaskedInput();

    ifstream inFile("admin.txt");
    if (inFile.is_open()) {
        while (inFile >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == password) {
                cout << GREEN << "\nLogin successful!\n" << RESET;
                inFile.close();
                return true;
            }
        }
        inFile.close();
    }
    cout << RED << "\nInvalid username or password.\n" << RESET;
    return false;
}


void adminRegister() {
    string username, password;
    cout << YELLOW << "\nEnter Admin Username: " << RESET;
    cin >> username;

    do {
        cout << YELLOW << "Enter Password: " << RESET;
        password = getMaskedInput();

        if (!isPasswordStrong(password)) {
            cout << RED << "\nPassword is not strong enough. Please use a password with: \n";
            cout << "- At least one uppercase letter\n";
            cout << "- At least one lowercase letter\n";
            cout << "- At least one number\n";
            cout << "- At least one special character (!@#$%^&*)\n";
            cout << "- Minimum length of 8 characters\n" << RESET;
        }
    } 
    while (!isPasswordStrong(password));

    ofstream outFile("admin.txt", ios::app);
    if (outFile.is_open()) {
        outFile << username << " " << password << endl;
        cout << GREEN << "\nAdmin registered successfully!\n" << RESET;
        outFile.close();
    } else {
        cout << RED << "\nError registering admin.\n" << RESET;
    }
}


void adminMenu() {
    int adminChoice;
    do {
        cout << BLUE  << "\n--- Admin Menu ---\n" << RESET;
        cout << "1. Search Login History\n";
        cout << "2. View Profile\n";
        cout << "3. Update Profile\n";
        cout << "4. Delete Account\n";
        cout << "5. Back\n";
        cout << BLUE << "Enter your choice: " << RESET;
        cin >> adminChoice;

        switch (adminChoice) {
            case 1: {
                int subChoice;
                cout << "\n" << BLUE  << "--- Search Login History ---\n" << RESET;
                cout << "1. Search by Username\n";
                cout << "2. View All Login History\n";
                cout << BLUE << "Enter your choice: " << RESET;
                cin >> subChoice;

                switch (subChoice) {
                    case 1:
                        searchHistoryByName();
                        break;
                    case 2:
                        viewAllHistory();
                        break;
                    default:
                        cout << RED << "Invalid choice. Returning to admin menu.\n" << RESET;
                }
                break; // Return to admin menu after viewing history
            }
            case 2: {
                string username;
                cout << "Enter the username: ";
                cin >> username;
                viewProfile(username);
                break;
            }
            case 3: {
                string username;
                cout << "Enter the username: ";
                cin >> username;
                updateProfile(username);
                break;
            }
            case 4: {
                string username;
                cout << "Enter the username: ";
                cin >> username;
                deleteUserAccount(username);
                break;
            }
            case 5:
                cout << GREEN << "Returning to main menu...\n" << RESET;
                break;
            default:
                cout << RED << "Invalid choice. Please try again.\n" << RESET;
        }
    } while (adminChoice != 5);
}


void exitMessage() {
    cout << GREEN << "\nThank you for using the Tourism Management System!" << RESET << endl;
    cout << BLUE  << "We hope you had a great experience." << RESET << endl;
    cout << GREEN << "We look forward to serving you again in the future. Safe travels!" << RESET << endl;
}


void registerUser() {
    string username, password, securityAnswer;
    int securityQuestionChoice;

    // Colorful and Large Header
    cout << "\033[1;36m--- \033[1;33mRegister \033[1;36m---\n\033[0m";  // Cyan title with yellow "Register"
    cout << "\033[1;32mEnter a username: \033[0m";  // Green text for prompt
    cin >> username;

    // Loop until a valid password is entered
    bool validPassword = false;
    while (!validPassword) {
        cout << "\033[1;32mEnter a password: \033[0m";  // Green text for prompt
        password = getMaskedInput();

        // Password strength check
        if (!isPasswordStrong(password)) {
            cout << RED << "\nPassword is not strong enough. Please use a password with: \n";
            cout << "- At least one uppercase letter\n";
            cout << "- At least one lowercase letter\n";
            cout << "- At least one number\n";
            cout << "- At least one special character (!@#$%^&*)\n";
            cout << "- Minimum length of 8 characters\n" << RESET;
        } else {
            validPassword = true;  // Exit the loop when the password is valid
        }
    }

    cout << "\n\033[1;32mChoose a security question:\n\033[0m";  // Green header for choices
    cout << "\033[1;34m1. What is your favorite color?\n";  // Blue choices
    cout << "2. What is the name of your first pet?\n";
    cout << "3. What is the name of the city where you were born?\n\033[0m";
    cout << "\033[1;32mEnter your choice (1/2/3): \033[0m";  // Green prompt
    cin >> securityQuestionChoice;

    while (securityQuestionChoice < 1 || securityQuestionChoice > 3) {
        cout << "\033[1;31mInvalid choice. Please choose 1, 2, or 3: \033[0m";  // Red message
        cin >> securityQuestionChoice;
    }

    cout << "\033[1;32mEnter your answer: \033[0m";  // Green prompt for answer
    cin.ignore(); // To ignore the newline character from previous input
    getline(cin, securityAnswer);

    // Write to file with colorful output for success message
    ofstream outFile("users.txt", ios::app);
    if (outFile) {
        outFile << username << " " << password << " " << securityQuestionChoice << " " << securityAnswer << endl;
        cout << "\n\033[1;32mUser registered successfully!\033[0m\n";  // Success message in green
    } else {
        cout << "\033[1;31mError: Unable to open file for registration.\033[0m\n";  // Error message in red
    }
    outFile.close();
}

// Function to check password strength
bool isPasswordStrong(string password) {
    regex strongPasswordPattern("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d)(?=.*[!@#$%^&*]).{8,}$");
    return regex_match(password, strongPasswordPattern);
}

// Function to log user actions
void logUserAction(const string& username, const string& action) {
    ofstream outFile("login_history.txt", ios::app);  // Open file in append mode
    if (outFile) {
        // Get the current time for the timestamp
        time_t now = time(0);
        char* dt = ctime(&now);  // Convert time to string
        dt[strlen(dt) - 1] = '\0';  // Remove the newline at the end

        outFile << username << " " << action << " " << dt << endl;  // Log user action
        outFile.close();
    } else {
        cout << "Error: Unable to open file to log action.\n";
    }
}


// Function to update profile information
void updateProfile(string username) {
    string password, securityAnswer;
    int securityQuestionChoice;  // Change this to int
    cout << BLUE  << "\n--- Update Profile ---\n" << RESET;
    cout << YELLOW << "Enter your new password: " << RESET;
    password = getMaskedInput();

    // Password strength check
    if (!isPasswordStrong(password)) {
        cout << RED << "Password is not strong enough. Please try again.\n" << RESET;
        return;
    }

    cout << YELLOW << "\nChoose a new security question:\n" << RESET;
    cout << "1. What is your favorite color?\n";
    cout << "2. What is the name of your first pet?\n";
    cout << "3. What is the name of the city where you were born?\n";
    cout << YELLOW << "Enter your choice (1/2/3): " << RESET;
    cin >> securityQuestionChoice;  // Now it is an integer

    // Ensure valid input
    while (securityQuestionChoice < 1 || securityQuestionChoice > 3) {
        cout << RED << "Invalid choice. Please choose 1, 2, or 3: " << RESET;
        cin >> securityQuestionChoice;
    }

    cout << YELLOW << "Enter your new answer: " << RESET;
    cin.ignore(); // To ignore the newline character from the previous input
    getline(cin, securityAnswer);

    // Update the user profile in the file
    ifstream inFile("users.txt");
    stringstream buffer;
    bool found = false;
    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser == username) {
                buffer << storedUser << " " << password << " " << securityQuestionChoice << " " << securityAnswer << endl;
                found = true;
            } else {
                buffer << storedUser << " " << storedPass << " " << storedQuestionChoice << " " << storedAnswer << endl;
            }
        }
        inFile.close();

        if (found) {
            ofstream outFile("users.txt");
            outFile << buffer.str();
            outFile.close();
            cout << GREEN << "\nProfile updated successfully!\n" << RESET;
            logUserAction(username, "User updated profile");
        } else {
            cout << RED << "\nUsername not found.\n" << RESET;
        }
    }
}

// Function to view the user's profile
void viewProfile(string username) {
    ifstream inFile("users.txt");
    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        bool found = false;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser == username) {
                cout << BLUE << "\n--- User Profile ---\n" << RESET;
                cout << YELLOW << "Username: " << RESET << storedUser << endl;
                cout << YELLOW << "Password: " << RESET << storedPass << endl;
                cout << YELLOW << "Security Question: " << RESET << storedQuestionChoice << endl;
                cout << YELLOW << "Security Answer: " << RESET << storedAnswer << endl;
                found = true;
                break;
            }
        }
        inFile.close();

        if (!found) {
            cout << RED << "Profile not found for username: " << username << endl << RESET;
        }
    } else {
        cout << RED << "Error: Unable to open user file.\n" << RESET;
    }
}

// Function to delete a user account
void deleteUserAccount(string username) {
    ifstream inFile("users.txt");
    stringstream buffer;
    bool found = false;

    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser != username) {
                buffer << storedUser << " " << storedPass << " " << storedQuestionChoice << " " << storedAnswer << endl;
            } else {
                found = true;
            }
        }
        inFile.close();

        if (found) {
            ofstream outFile("users.txt");
            outFile << buffer.str();
            outFile.close();
            cout << GREEN << "\nAccount deleted successfully.\n" << RESET;
            logUserAction(username, "User account deleted");
        } else {
            cout << RED << "\nUsername not found.\n" << RESET;
        }
    } else {
        cout << RED << "Error: Unable to open user file.\n" << RESET;
    }
}

// Function to display a menu of available actions for the user
void displayUserMenu(string username) {
    int choice;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. View Profile\n";
        cout << "2. Update Profile\n";
        cout << "3. Change Password\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewProfile(username);  // Pass the username
                break;
            case 2:
                updateProfile(username);  // Pass the username
                break;
            case 3:
                changePassword(username);  // Pass the username
                break;
            case 4:
                logout();  // Ensure this function is declared
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

// Function to view user profile information
void viewProfile() {
    string username;
    cout << "\n--- View Profile ---\n";
    cout << "Enter your username: ";
    cin >> username;

    ifstream inFile("users.txt");
    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser == username) {
                cout << "\nProfile Information:\n";
                cout << "Username: " << storedUser << endl;
                cout << "Security Question: ";
                switch (stoi(storedQuestionChoice)) {
                    case 1:
                        cout << "What is your favorite color?\n";
                        break;
                    case 2:
                        cout << "What is the name of your first pet?\n";
                        break;
                    case 3:
                        cout << "What is the name of the city where you were born?\n";
                        break;
                    default:
                        cout << "Invalid security question.\n";
                        break;
                }
                cout << "Security Answer: " << storedAnswer << endl;
                break;
            }
        }
    } else {
        cout << "\nError: Unable to open user file.\n";
    }
}

// Function to update user profile information
void updateProfile() {
    string username, newAnswer;
    int newQuestionChoice;
    cout << "\n--- Update Profile ---\n";
    cout << "Enter your username: ";
    cin >> username;

    ifstream inFile("users.txt");
    stringstream buffer;
    bool found = false;

    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser == username) {
                found = true;
                cout << "\nCurrent Profile Information:\n";
                cout << "Username: " << storedUser << endl;
                cout << "Current Security Question: ";
                switch (stoi(storedQuestionChoice)) {
                    case 1:
                        cout << "What is your favorite color?\n";
                        break;
                    case 2:
                        cout << "What is the name of your first pet?\n";
                        break;
                    case 3:
                        cout << "What is the name of the city where you were born?\n";
                        break;
                    default:
                        cout << "Invalid security question.\n";
                        break;
                }
                cout << "Current Security Answer: " << storedAnswer << endl;

                cout << "\nChoose a new security question:\n";
                cout << "1. What is your favorite color?\n";
                cout << "2. What is the name of your first pet?\n";
                cout << "3. What is the name of the city where you were born?\n";
                cout << "Enter your choice (1/2/3): ";
                cin >> newQuestionChoice;

                cout << "Enter your new answer: ";
                cin.ignore(); // To ignore the newline character
                getline(cin, newAnswer);

                buffer << storedUser << " " << storedPass << " " << newQuestionChoice << " " << newAnswer << endl;
            } else {
                buffer << storedUser << " " << storedPass << " " << storedQuestionChoice << " " << storedAnswer << endl;
            }
        }
        inFile.close();

        if (found) {
            ofstream outFile("users.txt");
            outFile << buffer.str();
            outFile.close();
            cout << "\nProfile updated successfully!\n";
        } else {
            cout << "\nNo account found with username: " << username << endl;
        }
    } else {
        cout << "\nError: Unable to open user file.\n";
    }
}


void changePassword() {
    string username, oldPassword, newPassword;
    cout << "\n--- Change Password ---\n";
    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your current password: ";
    oldPassword = getMaskedInput();

    ifstream inFile("users.txt");
    stringstream buffer;
    bool found = false;

    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser == username && storedPass == oldPassword) {
                found = true;
                cout << "\nPassword matched. Enter your new password: ";
                newPassword = getMaskedInput();

                buffer << storedUser << " " << newPassword << " " << storedQuestionChoice << " " << storedAnswer << endl;
            } else {
                buffer << storedUser << " " << storedPass << " " << storedQuestionChoice << " " << storedAnswer << endl;
            }
        }
        inFile.close();

        if (found) {
            ofstream outFile("users.txt");
            outFile << buffer.str();
            outFile.close();
            cout << "\nPassword changed successfully!\n";
        } else {
            cout << "\nIncorrect current password. Returning to main menu...\n";
        }
    } else {
        cout << "\nError: Unable to open user file.\n";
    }
}

// Function to log out user and return to login page
void logout() {
    cout << "\nLogging out...\n";
    // You can add any necessary cleanup here before returning to the login page
    exit(0);
}

// Function to handle logout if user decides to log out from anywhere
void handleLogout() {
    char choice;
    cout << "\nDo you want to log out? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        logout();
    } else {
        cout << "\nReturning to previous menu...\n";
    }
}

// Function to display user activity logs
void displayUserActivityLogs() {
    string line;
    cout << "\n--- User Activity Logs ---\n";
    ifstream inFile("user_activity_log.txt");
    if (inFile) {
        cout << left << setw(20) << "Username" << setw(30) << "Activity" << "Timestamp" << endl;
        cout << string(70, '-') << endl;
        while (getline(inFile, line)) {
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string username = line.substr(0, firstSpace);
            string activity = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string timestamp = line.substr(secondSpace + 1);

            cout << left << setw(20) << username << setw(30) << activity << timestamp << endl;
        }
    } else {
        cout << "No activity logs found.\n";
    }
    inFile.close();
}

// Function to log user activity (used for tracking actions)
void logUserActivity(const string& username, const string& activity) {
    ofstream logFile("user_activity_log.txt", ios::app);
    if (logFile) {
        logFile << username << " " << activity << " at " << getCurrentTimestamp() << endl;
        logFile.close();
    } else {
        cout << "\nError: Unable to log activity.\n";
    }
}

// Function to delete user account
void deleteUserAccount() {
    string username;
    cout << "\n--- Delete Account ---\n";
    cout << "Enter your username to delete your account: ";
    cin >> username;

    ifstream inFile("users.txt");
    stringstream buffer;
    bool found = false;

    if (inFile) {
        string storedUser, storedPass, storedQuestionChoice, storedAnswer;
        while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
            if (storedUser == username) {
                found = true;
                cout << "\nAccount found. Deleting your account...\n";
                continue; // Skip writing this account to the new buffer
            } else {
                buffer << storedUser << " " << storedPass << " " << storedQuestionChoice << " " << storedAnswer << endl;
            }
        }
        inFile.close();

        if (found) {
            ofstream outFile("users.txt");
            outFile << buffer.str();
            outFile.close();
            cout << "\nAccount deleted successfully!\n";
        } else {
            cout << "\nNo account found with username: " << username << endl;
        }
    } else {
        cout << "\nError: Unable to open user file.\n";
    }
}

// Function to provide feedback about the system
void provideFeedback() {
    string username, feedback;
    cout << "\n--- Provide Feedback ---\n";
    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your feedback: ";
    cin.ignore(); // To ignore the newline character from previous input
    getline(cin, feedback);

    ofstream feedbackFile("user_feedback.txt", ios::app);
    if (feedbackFile) {
        feedbackFile << username << " provided feedback: " << feedback << " at " << getCurrentTimestamp() << endl;
        feedbackFile.close();
        cout << "\nFeedback submitted successfully!\n";
    } else {
        cout << "\nError: Unable to submit feedback.\n";
    }
}

// Function to view all feedback submitted by users
void viewAllFeedback() {
    string line;
    cout << "\n--- User Feedback ---\n";
    ifstream feedbackFile("user_feedback.txt");
    if (feedbackFile) {
        cout << left << setw(20) << "Username" << setw(50) << "Feedback" << "Timestamp" << endl;
        cout << string(90, '-') << endl;
        while (getline(feedbackFile, line)) {
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string username = line.substr(0, firstSpace);
            string feedback = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string timestamp = line.substr(secondSpace + 1);

            cout << left << setw(20) << username << setw(50) << feedback << timestamp << endl;
        }
    } else {
        cout << "No feedback found.\n";
    }
    feedbackFile.close();
}

// Function to send system notifications to users
void sendSystemNotification() {
    string username, notificationMessage;
    cout << "\n--- Send System Notification ---\n";
    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter notification message: ";
    cin.ignore(); // To ignore the newline character
    getline(cin, notificationMessage);

    ofstream notificationFile("system_notifications.txt", ios::app);
    if (notificationFile) {
        notificationFile << username << " received notification: " << notificationMessage << " at " << getCurrentTimestamp() << endl;
        notificationFile.close();
        cout << "\nNotification sent successfully!\n";
    } else {
        cout << "\nError: Unable to send notification.\n";
    }
}

// Function to view all system notifications
void viewAllNotifications() {
    string line;
    cout << "\n--- System Notifications ---\n";
    ifstream notificationFile("system_notifications.txt");
    if (notificationFile) {
        cout << left << setw(20) << "Username" << setw(50) << "Notification" << "Timestamp" << endl;
        cout << string(90, '-') << endl;
        while (getline(notificationFile, line)) {
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string username = line.substr(0, firstSpace);
            string notification = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string timestamp = line.substr(secondSpace + 1);

            cout << left << setw(20) << username << setw(50) << notification << timestamp << endl;
        }
    } else {
        cout << "No notifications found.\n";
    }
    notificationFile.close();
}


void loginUser() {
    string username, password;
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts) {
        cout << CYAN << "\nEnter username: " << RESET;
        cin >> username;
        cout << CYAN << "Enter password: " << RESET;
        password = getMaskedInput();

        ifstream inFile("users.txt");
        string storedUser, storedPass;
        bool found = false;

        while (inFile >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == password) {
                found = true;
                cout << GREEN << "Login successful!\n" << RESET;

                // Log login action
                logUserAction(username, "Login");  // Call this function to log the action
                inFile.close();
                return;
            }
        }
        inFile.close();

        // If invalid login attempt
        cout << RED << "Invalid username or password.\n" << RESET;
        attempts++;

        if (attempts == maxAttempts) {
            cout << RED << "You have exceeded the maximum number of attempts. Exiting...\n" << RESET;
            return;  // Exit after 3 failed attempts
        } else {
            cout << YELLOW << "You have " << (maxAttempts - attempts) << " attempt(s) left.\n" << RESET;
        }
    }
}


void forgetPassword() {
    string username, answer, storedUsername, storedPassword, storedAnswer;
    int storedQuestionChoice;
    bool found = false;

    // Security question mapping
    string question1 = "What is your favorite color?";
    string question2 = "What is the name of your first pet?";
    string question3 = "What is the name of the city where you were born?";

    // ASCII Art Title
    cout << "\033[1;36m========================================\n"; // Cyan
    cout << "           Forget Password\n";
    cout << "========================================\033[0m\n\n"; // Reset color

    cout << "\033[1;33mEnter your username: \033[0m"; // Yellow
    cin >> username;

    // Read the entire file into memory
    vector<string> fileLines;
    ifstream inFile("users.txt");
    if (!inFile) {
        cout << "\033[1;31mError: Unable to open users file.\033[0m\n"; // Red
        return;
    }

    string line;
    while (getline(inFile, line)) {
        fileLines.push_back(line);
    }
    inFile.close();

    // Process each line to find the user
    for (string& fileLine : fileLines) {
        stringstream ss(fileLine);
        ss >> storedUsername >> storedPassword >> storedQuestionChoice >> ws;
        getline(ss, storedAnswer); // Read the rest of the line for the answer

        if (storedUsername == username) {
            found = true;

            // Ask the correct security question based on the choice
            string questionToAsk;
            if (storedQuestionChoice == 1) {
                questionToAsk = question1;
            } else if (storedQuestionChoice == 2) {
                questionToAsk = question2;
            } else if (storedQuestionChoice == 3) {
                questionToAsk = question3;
            }

            cout << "\033[1;34mSecurity Question: \033[1;37m" << questionToAsk << "\033[0m\n"; // Blue question, white text
            cout << "\033[1;33mEnter your answer: \033[0m"; // Yellow
            cin.ignore();
            getline(cin, answer);

            if (answer == storedAnswer) {
                cout << "\033[1;32mAnswer correct!\033[0m Your current password is: \033[1;37m" << storedPassword << "\033[0m\n"; // Green success, white password
                cout << "\033[1;33mDo you want to change your password? (yes/no): \033[0m"; // Yellow
                string choice;
                cin >> choice;

                if (choice == "yes" || choice == "Yes") {
                    cout << "\033[1;33mEnter your new password: \033[0m"; // Yellow
                    string newPassword;
                    cin >> newPassword;

                    // Directly update the password in the memory
                    fileLine = storedUsername + " " + newPassword + " " + to_string(storedQuestionChoice) + " " + storedAnswer;
                    cout << "\033[1;32mPassword updated successfully.\033[0m\n"; // Green success
                } else {
                    cout << "\033[1;36mPassword change skipped.\033[0m\n"; // Cyan
                }
                break;
            } else {
                cout << "\033[1;31mIncorrect answer.\033[0m\n"; // Red
                break;
            }
        }
    }

    if (!found) {
        cout << "\033[1;31mUsername not found.\033[0m\n"; // Red
        return;
    }

    // Overwrite the file with updated content
    ofstream outFile("users.txt", ios::trunc);
    if (!outFile) {
        cout << "\033[1;31mError: Unable to open users file for writing.\033[0m\n"; // Red
        return;
    }

    for (const string& fileLine : fileLines) {
        outFile << fileLine << endl;
    }
    outFile.close();

    // Closing success message
    cout << "\033[1;36m========================================\n"; // Cyan
    cout << "         Process Completed\n";
    cout << "========================================\033[0m\n"; // Reset color
}

// functions.cpp
void changePassword(string username) {
    string oldPassword, newPassword;
    cout << "Enter your old password: ";
    oldPassword = getMaskedInput();

    ifstream inFile("users.txt");
    ofstream outFile("temp.txt");
    bool found = false;
    string storedUser, storedPass, storedQuestionChoice, storedAnswer;

    while (inFile >> storedUser >> storedPass >> storedQuestionChoice >> storedAnswer) {
        if (storedUser == username && storedPass == oldPassword) {
            cout << "Old password matched. Enter new password: ";
            cin >> newPassword;
            outFile << storedUser << " " << newPassword << " " << storedQuestionChoice << " " << storedAnswer << endl;
            found = true;
        } else {
            outFile << storedUser << " " << storedPass << " " << storedQuestionChoice << " " << storedAnswer << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("users.txt");
        rename("temp.txt", "users.txt");
        cout << "Password changed successfully.\n";
    } else {
        cout << "Old password incorrect. Try again.\n";
    }
}

// Function to get a masked password input (for password security)
string getMaskedInput() {
    string password;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) { // Enter key
            break;
        } else if (ch == 8) { // Backspace
            if (password.length() > 0) {
                password.pop_back();
                cout << "\b \b"; // Erase the last character on the screen
            }
        } else {
            password.push_back(ch);
            cout << "*"; // Display '*' for the typed character
        }
    }
    return password;
}


string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}


void viewLoginHistory() {
    string line;
    cout << "\n";
    cout << CYAN << string(80, '=') << RESET << endl;
    cout << MAGENTA << "                 LOGIN HISTORY                 " << RESET << endl;
    cout << CYAN << string(80, '=') << RESET << endl;

    ifstream inFile("login_history.txt");  // Open login history file
    if (inFile) {
        cout << GREEN << left << setw(20) << "USERNAME" << setw(30) << "ACTION" << "TIMESTAMP" << RESET << endl;
        cout << CYAN << string(80, '-') << RESET << endl;
        while (getline(inFile, line)) {
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string username = line.substr(0, firstSpace);
            string action = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string timestamp = line.substr(secondSpace + 1);

            cout << YELLOW << left << setw(20) << username << setw(30) << action << RESET << WHITE << timestamp << RESET << endl;
        }
        cout << CYAN << string(80, '=') << RESET << endl;
    } else {
        cout << RED << "No login history found.\n" << RESET;
    }
    inFile.close();
}

// Function to search login history by username
void searchHistoryByName() {
    string line, searchName;
    cout << "\n";
    cout << CYAN << string(80, '=') << RESET << endl;
    cout << MAGENTA << "          SEARCH LOGIN HISTORY BY USERNAME         " << RESET << endl;
    cout << CYAN << string(80, '=') << RESET << endl;

    cout << "Enter the username to search history: " << RESET;
    cin >> searchName;

    // Transform searchName to lowercase for case-insensitive comparison
    transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

    ifstream inFile("login_history.txt");
    if (inFile) {
        bool found = false;
        cout << GREEN << left << setw(20) << "USERNAME" << setw(30) << "ACTION" << "TIMESTAMP" << RESET << endl;
        cout << CYAN << string(80, '-') << RESET << endl;
        while (getline(inFile, line)) {
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string username = line.substr(0, firstSpace);
            string action = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string timestamp = line.substr(secondSpace + 1);

            // Transform the username to lowercase for case-insensitive comparison
            transform(username.begin(), username.end(), username.begin(), ::tolower);

            if (username == searchName) {
                cout  << YELLOW << left << setw(20) << username << setw(30) << action << RESET << WHITE << timestamp << RESET << endl;
                found = true;
            }
        }
        if (!found) {
            cout << RED << "\nNo history found for user: " << searchName << RESET << endl;
        }
        cout << CYAN << string(80, '=') << RESET << endl;
    } else {
        cout << RED << "No login history found.\n" << RESET;
    }
    inFile.close();
}

// Function to view all login history
void viewAllHistory() {
    viewLoginHistory();
}
// int main()
// {
//     login();
// }
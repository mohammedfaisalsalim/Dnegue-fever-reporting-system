#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Doctor.h"
#include "User.h"

struct Admin {
    string adminUsername;
    string adminPassword;

};

// An array of Doctor structures to store details
Admin admin[] = {
    {"admin","admin"}
};

void viewReports() {
    std::ifstream file("Annual number of dengue cases by state.csv");
    std::string line;
    std::string stateNames[15] = { "JOHOR", "KEDAH", "KELANTAN", "MELAKA", "NEGERI SEMBILAN", "PAHANG", "PERAK", "PERLIS", "PULAU PINANG", "SABAH", "SARAWAK", "SELANGOR", "TERENGGANU", "WP KUALA LUMPUR", "WP LABUAN" };
    int stateTotals[15] = { 0 };
    int grandTotal = 0;

    if (file.is_open()) {
        // Skip the first line
        std::getline(file, line);

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            // Skip the first two columns
            for (int i = 0; i < 2; i++) {
                std::string value;
                std::getline(ss, value, ',');
            }

            // Read and accumulate the values for each column
            for (int i = 0; i < 15; i++) {
                std::string value;
                std::getline(ss, value, ',');
                int columnValue = std::stoi(value);
                stateTotals[i] += columnValue;
                grandTotal += columnValue;
            }
        }
        std::cout << "--------------------------------------------------";
        std::cout << "\n" << "ONE * REPRESENT ONE PERSENT" << "\n";
        std::cout << "Total Cases in Malaysia: " << grandTotal << "\n";
        std::cout << "--------------------------------------------------";
        std::cout << "\n";

        // Display the totals for each column as a percentage of the grand total
        for (int i = 0; i < 15; i++) {
            int percentage = (stateTotals[i] * 100) / grandTotal;
            std::cout << stateNames[i] << ": ";
            if (percentage == 0) {
                std::cout << "*"; // At least one "*"
            }
            else {
                for (int j = 0; j < percentage; j++) {
                    std::cout << "*";
                }
            }
            std::cout << "\n";
        }
    }
    else {
        std::cout << "Unable to open file\n";
    }

    std::cout << "Viewing reports from previous to latest...\n";
}

void ViewWeeklyCases() {

    std::ifstream file("Number of dengue fever cases weekly by state.csv");
    if (file.is_open()) {

        // Variables to store the total numbers in each of the 15 columns
        int totalNumbers[15] = { 0 };

        std::string line;

        // Skip the first line (header)
        if (std::getline(file, line)) {
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string value;

                // Skip the first two columns
                for (int i = 0; i < 2; i++) {
                    std::getline(ss, value, ',');
                }

                // Read and accumulate the values for each column
                for (int i = 0; i < 15; i++) {
                    std::getline(ss, value, ',');
                    int columnValue = std::stoi(value);
                    totalNumbers[i] += columnValue;
                }
            }
        }

        file.close();

        // Define the column names
        std::string columnNames[15] = {
            "JOHOR", "KEDAH", "KELANTAN", "MELAKA", "NEGERI SEMBILAN",
            "PAHANG", "PERAK", "PERLIS", "PULAU PINANG", "SABAH",
            "SARAWAK", "SELANGOR", "TERENGGANU", "WP KUALA LUMPUR", "WP LABUAN"
        };

        // Sort the columns in ascending order and print
        for (int i = 0; i < 15; i++) {
            int minIndex = -1;
            int minValue = INT_MAX;

            // Find the minimum value and its index
            for (int j = 0; j < 15; j++) {
                if (totalNumbers[j] < minValue) {
                    minValue = totalNumbers[j];
                    minIndex = j;
                }
            }

            if (minIndex != -1) {
                std::cout << columnNames[minIndex] << ": " << minValue << std::endl;
                // Set the minimum value to INT_MAX to ignore it in the next iteration
                totalNumbers[minIndex] = INT_MAX;
            }
        }
    }
    else {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }
    file.close();
}

void sendAlertMessage() {
    std::string username;
    std::cout << "Enter the username of the user to send an alert message: ";
    std::cin >> username;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].userUsername == username) {
            std::cout << "Enter alert message for " << users[i].userName << ": ";
            std::cin.ignore(); // To clear the newline character from the buffer
            std::getline(std::cin, users[i].alertmessage[(users[i].totalAlertMessages)++]); // Read the full line including spaces
            std::cout << "Alert message set successfully.\n";
            return;
        }
    }
    std::cout << "User not found.\n";
}

void manageDoctorAccount() {
    string doctorId;
    cout << "Enter Doctor ID to search: ";
    cin >> doctorId;

    // Searching for the doctor by ID
    bool found = false;
    for (Doctor& doctor : doctors) {
        if (doctor.doctorId == doctorId) {
            found = true;

            // Display current details
            cout << "Current Details:" << endl;
            cout << "Name: " << doctor.doctorName << ", Address: " << doctor.doctorAddress << ", Phone: " << doctor.doctorPhone << endl;

            // Prompt for new details
            cout << "Enter new name: ";
            cin.ignore(); // Clear the newline character from the stream
            getline(cin, doctor.doctorName);
            cout << "Enter new address: ";
            getline(cin, doctor.doctorAddress);
            cout << "Enter new phone: ";
            cin >> doctor.doctorPhone;

            // Displaying updated details
            cout << "\nUpdated Doctor Details:" << endl;
            cout << "Name: " << doctor.doctorName << endl;
            cout << "Address: " << doctor.doctorAddress << endl;
            cout << "Phone: " << doctor.doctorPhone << endl;

            cout << "\nDoctor details updated successfully." << endl;
            break;
        }
    }

    if (!found) {
        cout << "Doctor with ID " << doctorId << " not found." << endl;
    }
}

void listUsers() {
    cout << "\nList of Users:\n";
    for (int i = 0; i < numUsers; i++) {
        if (!users[i].userUsername.empty()) {
            cout << "Username: " << users[i].userUsername << ", Name: " << users[i].userName << ", Address: " << users[i].userState << endl;
        }
    }
}

void manageUserAccount() {
    cout << "\nManaging user account...\n";

    // Option to list all users
    listUsers();

    // Continue with user management
    string username;
    cout << "\nEnter username of user to manage: ";
    cin >> username;

    // Search for the user
    User* foundUser = nullptr;
    for (int i = 0; i < numUsers; i++) {
        if (users[i].userUsername == username) {
            foundUser = &users[i];
            break;
        }
    }

    if (!foundUser) {
        cout << "User not found.\n";
        return;
    }

    // Display user details
    cout << "User found: " << foundUser->userName << "\n";

    // User management options
    cout << "1. Edit User\n";
    cout << "2. Delete User\n";
    cout << "3. Do Nothing\n";
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: // Edit user
        cout << "Editing User...\n";
        cout << "Enter new name: ";
        cin >> foundUser->userName;
        cout << "Enter new address: ";
        cin >> foundUser->userState;
        cout << "User details updated.\n";
        break;
    case 2: // Delete user
        foundUser->userUsername = ""; // Mark as deleted
        cout << "User deleted.\n";
        break;
    case 3: // Do nothing
        cout << "No changes made.\n";
        break;
    default:
        cout << "Invalid choice.\n";
    }
}

#pragma once

#include <iostream>
#include <string>
#include "Doctor.h"
#include "Admin.h"
#include "User.h"
#include <limits>


enum class AccountType {
    None,
    Doctor,
    Admin,
    User
};

AccountType Login(string& name) {
    string username, password;

    cout << "--------------------------------------------------\n";
    cout << "   DENGUE FEVER SURVEILLANCE AND ALERT SYSTEM\n";
    cout << "     FOR MALAYSIAN MINISTRY OF HEALTH(MOH)\n";
    cout << "         ----------------\n";
    cout << "        |   __      __   |     ---------------\n";
    cout << "        |  |  |    |  |  |    | PLEASE login! |\n";
    cout << "        |   TT      TT   |     ---------------\n";
    cout << "        |      (O O)     |\n";
    cout << "        |      -----     |\n";
    cout << "         ----------------\n";
    cout << "   __ __ __            __ __ __\n";
    cout << "  |  |  |  |          |  |  |  |\n";
    cout << "--------------------------------------------------\n";
    
    

    cout << "Please enter your username: ";
    cin >> username;
    cout << "Please enter your password: ";
    cin >> password;

    // Check Doctor login
    for (const Doctor& doctor : doctors) {
        if (doctor.doctorUser == username && doctor.doctorPassword == password) {
            name = doctor.doctorName;
            return AccountType::Doctor;
        }
    }

    // Check Admin login
    for (const Admin& admin : admin) {
        if (admin.adminUsername == username && admin.adminPassword == password) {
            name = admin.adminUsername;
            return AccountType::Admin;
        }
    }

    // Check User login
    for (const User& user : users) {
        if (user.userUsername == username && user.userPassword == password) {
            name = user.userName;
            return AccountType::User;
        }
    }

    return AccountType::None; // Login failed
}


class UserInterface {
private:
    string loggedInUserName;
    YearStates* yearStates;
    WeeklyStates* weeklyStates;

public:
    string name;
    UserInterface(
        const string& userName,
        YearStates* yearStates,
        WeeklyStates* weeklyStates
        ) : loggedInUserName(userName), yearStates(yearStates), weeklyStates(weeklyStates) {}

    void showMenu() {
        int choice;
        do {
            cout << "--------------------------------------------------\n";
            std::cout << "\nUser Interface Menu\n";
            std::cout << "1. Manage Personal Information\n";
            std::cout << "2. View total dengue cases based on selected years\n";
            std::cout << "3. View total dengue cases based on selected states\n";
            std::cout << "4. View daily dengue cases for all states in descending order\n";
            std::cout << "5. View dengue alert messages from the MOH admin\n";
            std::cout << "6. View personal past dengue fever status\n";
            std::cout << "7. Exit\n";
            std::cout << "Enter your choice (1-6): ";
            std::cin >> choice;

            // Check if input failed
            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
                std::cout << "Invalid input. Please enter a number.\n";
                continue; // Prompt the user again
            }

            switch (choice) {
            case 1: // Manage Personal Information
                userManagePersonalInformation(loggedInUserName);
                break;
            case 2: // View total dengue cases based on selected years
                userViewTotalDengueCasesBasedOnSelectedYears(yearStates);
                break;
            case 3: // View total dengue cases based on selected states
                userViewTotalDengueCasesBasedOnSelectedStates(yearStates);
                break;
            case 4: // View daily dengue cases for all states in descending order
                userViewDailyDengueCasesForAllStatesInDescendingOrder();
                break;
            case 5: // View dengue alert messages from the MOH admin
                userViewDengueAlertMessagesFromTheMOHAdmin(loggedInUserName);
                break;
            case 6: // View personal past dengue fever status
                userViewPersonalPastDengueFeverStatus(loggedInUserName);
                break;
            case 7:
                std::cout << "Exiting...\n";
                std::cout << "\n";
                Login(name);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 7);
    }
};

class DoctorInterface {
private:
    string loggedInDoctorName;

public:
    string name;
    DoctorInterface(const string& doctorName) : loggedInDoctorName(doctorName) {}

    void showMenu(const string& doctorName) {
        int choice;
        do {
            cout << "--------------------------------------------------\n";
            std::cout << "\nDoctor Interface Menu\n";
            std::cout << "1. Manage Personal Information\n";
            std::cout << "2. Report Patient Infected by Dengue Fever\n";
            std::cout << "3. View All Dengue Cases Reported by Current Doctors\n";
            std::cout << "4. Filter System\n";
            std::cout << "5. Find Patient\n";
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice (1-5): ";
            std::cin >> choice;

            // Check if input failed
            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
                std::cout << "Invalid input. Please enter a number.\n";
                continue; // Prompt the user again
            }

            switch (choice) {
            case 1:
                managePersonalInformation(doctorName);
                break;
            case 2:
                reportDenguePatient(loggedInDoctorName);
                break;
            case 3:
                viewAllDengueCases();
                break;
            case 4:
                filterSystem();
                break;
            case 5:
                Finddenguefever();
                break;
            case 6:
                std::cout << "Exiting...\n";
                std::cout << "\n";
                Login(name);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 6);
    }
};

class AdminInterface {
public:
    string name;
    void showMenu() {
        int choice;
        do {
            cout << "--------------------------------------------------\n";
            std::cout << "\nAdmin Interface Menu\n";
            std::cout << "1. View Reports from Previous to Latest\n";
            std::cout << "2. View Weekly Dengue Cases by Ascending Order\n";
            std::cout << "3. Send Alert Message to Users\n";
            std::cout << "4. Manage Doctor Account\n";
            std::cout << "5. Manage User Account\n";
            std::cout << "6. Exit\n";
            std::cout << "Enter your choice (1-5): ";
            std::cin >> choice;

            // Check if input failed
            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
                std::cout << "Invalid input. Please enter a number.\n";
                continue; // Prompt the user again
            }

            switch (choice) {
            case 1:
                viewReports();
                break;
            case 2:
                ViewWeeklyCases();
                break;
            case 3:
                sendAlertMessage();
                break;
            case 4:
                manageDoctorAccount();
                break;
            case 5:
                manageUserAccount();
                break;
            case 6:
                std::cout << "Exiting...\n";
                std::cout << "\n";
                Login(name);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }

};

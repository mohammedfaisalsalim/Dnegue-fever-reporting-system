#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include "YearStates.h"
#include "WeeklyStates.h"
#include "Interface.h"
#include <limits>

using namespace std;

// Simplified YearStates class


int main() {

    // Read yearly
    YearStates yearStates("Annual number of dengue cases by state");
    yearStates.readFromFile("Annual number of dengue cases by state.csv");

    // Read weekly
    WeeklyStates weeklyStates("Weekly number of dengue cases by state");
    weeklyStates.readFromFile("Number of dengue fever cases weekly by state.csv");

    string name;
    AccountType accountType;

    while (true) {
        while (true) {
            accountType = Login(name);

            if (accountType != AccountType::None) {
                // Successful login
                break;
            }

            char tryAgain;
            cout << "Failed to login. Would you like to try again? (Y/N): ";
            cin >> tryAgain;

            if (tryAgain != 'Y' && tryAgain != 'y') {
                cout << "Exiting program.\n";
                return 0;
            }
        }

        // Handle the successful login based on the account type
        switch (accountType) {
        case AccountType::Doctor:
            cout << endl <<  "Welcome Doctor " << name << "!\n";
            {
                DoctorInterface doctorInterface(name); // Pass the logged-in doctor's name
                doctorInterface.showMenu(name);
            }
            break;
        case AccountType::Admin:
            cout << endl << "Welcome " << name << "!\n";
            {
                AdminInterface adminInterface;
                adminInterface.showMenu();
            }
            break;
        case AccountType::User:
            cout << endl << "Welcome User " << name << "!\n";
            {
                UserInterface userInterface(name, &yearStates, &weeklyStates);
                userInterface.showMenu();
            }
            break;
        default:
            // This case should never be reached if the loop above is working correctly
            cout << "Unexpected error. Exiting program.\n";
            return 1;
        }

        cout << "\nReturning to login screen...\n";
    }

    return 0;
    

    /*
    //display yearly
    YearStates yearStates("Annual number of dengue cases by state");
    yearStates.readFromFile("Annual number of dengue cases by state.csv");
    yearStates.displayList();

    // Display weekly
    WeeklyStates weeklyStates("Weekly number of dengue cases by state");
    weeklyStates.readFromFile("Number of dengue fever cases weekly by state.csv");
    weeklyStates.displayList();
    */

    return 0;
}

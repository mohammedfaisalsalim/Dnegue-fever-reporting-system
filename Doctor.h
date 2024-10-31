#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Interface.h"
#include "User.h"
#include "Denguecase.h"
#include "YearStates.h"

using namespace std;



// To get the number of users
extern int numDoctor;


struct Doctor {
    string doctorName;
    string doctorId;
    string doctorUser;
    string doctorPassword;
    string doctorAddress;
    string doctorPhone;
};



// An array of Doctor structures to store details
Doctor doctors[] = {
    {"Dr. Kagoya", "DC000", "Kagoya", "Kagoya123", "Jalan Kagoya", "0108203844"},
    {"Dr. Marikao", "DC001", "Marikao", "Marikao123", "Jalan Marikao", "01928834733"},
    {"Dr. Saitama", "DC002", "Saitama", "Saitama123", "Jalan Saitama", "0187836274"}
};

int numDoctor = sizeof(doctors) / sizeof(doctors[0]);





void managePersonalInformation(const string& loggedInDoctorName) {
    // Searching for the doctor by name
    bool found = false;
    for (Doctor& doctor : doctors) {
        if (doctor.doctorName == loggedInDoctorName) {
            found = true;

            // Display current details
            cout << "--------------------------------------------------\n";
            cout << "               Current Details\n";
            cout << "Name    : " << doctor.doctorName << endl;
            cout << "Address : " << doctor.doctorAddress << endl;
            cout << "Phone   : " << doctor.doctorPhone << endl;
            cout << "--------------------------------------------------\n";


            // Prompt for new details
            cout << "Enter new address  : ";
            cin.ignore(); // Clear the newline character from the stream
            getline(cin, doctor.doctorAddress);
            cout << "Enter new phone    : ";
            cin >> doctor.doctorPhone;

            // Displaying updated details
            cout << "--------------------------------------------------\n";
            cout << "           Updated Doctor Details\n";
            cout << "Name: " << doctor.doctorName << endl;
            cout << "Address: " << doctor.doctorAddress << endl;
            cout << "Phone: " << doctor.doctorPhone << endl;

            cout << "\nDoctor details updated successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Doctor " << loggedInDoctorName << " not found.\n";
    }
}


void reportDenguePatient(const std::string& loggedInDoctorName) {
    if (numPatients >= MAX_PATIENTS) {
        cout << "--------------------------------------------------\n";
        cout << "Maximum number of patients reached. Cannot add more patients.\n";
        return;
    }

    cout << "\n--------------------------------------------------\n";
    cout << "  Reporting a patient infected by dengue fever" << endl << endl;

    // Declare variables for patient details
    string patientName, dateOfTreatment, status;
    int age;

    // Prompt for and input patient details
    bool validUser = false;
    bool firstTime = true;
    cin.ignore(); // Clear any leftover characters in the input stream
    do
    {
        if (firstTime) {
            firstTime = false;
        }
        else {
            cout << "Invalid name. User does not exist.";
        }

        validUser = false;

        cout << "Enter patient's name: ";

        getline(cin, patientName);

        for (int i = 0; i < numUsers; i++) {
            if (users[i].userName == patientName) {
                validUser = true;
            }
        }
    } while (!validUser);

    // Handle age input with error checking
    cout << "Enter patient's age: ";
    while (!(cin >> age)) {
        cout << "Invalid input. Please enter a number for age: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(); // Clear newline character after entering a number

    cout << "Enter date of treatment (YYYY-MM-DD): ";
    getline(cin, dateOfTreatment);

    cout << "Enter status ('High risk', 'Low Rick', 'Recovered'): ";
    getline(cin, status);

    // Add the new patient to the array
    patients[numPatients++] = Patient(patientName, age, dateOfTreatment, loggedInDoctorName, status);

    cout << "Patient reported successfully.\n";
}

void viewAllDengueCases() {
    cout << "--------------------------------------------------\n";
    cout << "          Viewing all dengue cases" << endl;
    cout << "        reported by current doctors\n\n";

    // Assuming 'patients' and the number of patients 'numPatients' are accessible here
    for (int i = 0; i < numPatients; i++) {
        std::cout << "Patient Name: " << patients[i].patientName << "\n";
        std::cout << "Age: " << patients[i].age << "\n";
        std::cout << "Date of Treatment: " << patients[i].dateOfTreatment << "\n";
        std::cout << "Doctor Name: " << patients[i].doctorName << "\n";
        std::cout << "Status: " << patients[i].status << "\n\n";
    }
}


void Finddenguefever() {
    std::string searchName;
    cout << "--------------------------------------------------\n";
    std::cout << "Enter the name of the patient to search: ";
    std::cin.ignore(); // Clear any leftover characters in the input stream
    getline(std::cin, searchName); // Get the full name including spaces

    bool found = false;
    for (int i = 0; i < numPatients; i++) {
        if (patients[i].patientName == searchName) {
            found = true;
            std::cout << "Patient found:\n";
            std::cout << "Name: " << patients[i].patientName << "\n";
            std::cout << "Age: " << patients[i].age << "\n";
            std::cout << "Date of Treatment: " << patients[i].dateOfTreatment << "\n";
            std::cout << "Doctor: " << patients[i].doctorName << "\n";
            std::cout << "Status: " << patients[i].status << "\n";
            break; // Exit the loop after finding the patient
        }
    }

    if (!found) {
        std::cout << "No patient found with the name '" << searchName << "'.\n";
    }
}

// Define states array globally
string states[] = { "Johor", "Kedah", "Kelantan", "Melaka", "Negeri Sembilan", "Pahang", "Perak", "Perlis", "Pulau Pinang", "Sabah", "Sarawak", "Selangor", "Terengganu", "WPKuala Lumpur", "WPLabuan" };

// Function prototype
void filterByStateAndAge(ifstream& file, const string& state, const string& ageRange);

void filterSystem() {
    cout << "--------------------------------------------------\n";
    cout << "Filtering system...\n";

    // Present a menu of age range options
    string ageRanges[] = { "0-4", "5-9", "10-14", "15-19", "20-24", "25-29", "30-34", "35-39", "40-44", "45-49", "50-54", "55-59", "60-64", "65-69", "70-74", "75+" };
    cout << "Age Range Options:\n";
    for (int i = 0; i < sizeof(ageRanges) / sizeof(ageRanges[0]); i++) {
        cout << i + 1 << ". Age " << ageRanges[i] << endl;
    }

    cout << "Enter your choice for age range: ";
    int ageOption;
    cin >> ageOption;
    string selectedAgeRange = ageRanges[ageOption - 1];

    // State selection
    cout << "\nState Options:\n";
    for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++) {
        cout << i + 1 << ". " << states[i] << endl;
    }

    string selectedState1, selectedState2;

    cout << "Enter first state option: ";
    int stateOption;
    cin >> stateOption;
    selectedState1 = states[stateOption - 1];

    cout << "Enter second state option (or the same for single state): ";
    cin >> stateOption;
    selectedState2 = states[stateOption - 1];

    // Read from CSV and filter data
    ifstream file("Annual number of dengue cases by state.csv");
    string line;
    getline(file, line);  // Skip the header line

    cout << "\nResults for " << selectedState1 << ":\n";
    filterByStateAndAge(file, selectedState1, selectedAgeRange);

    cout << "\nResults for " << selectedState2 << ":\n";
    filterByStateAndAge(file, selectedState2, selectedAgeRange);

    file.close();
}

void filterByStateAndAge(ifstream& file, const string& state, const string& ageRange) {
    string line, year, ageGroup, stateName;
    file.clear();  // Clear EOF flag
    file.seekg(0, ios::beg);  // Go to the beginning of the file
    getline(file, line);  // Skip the header line

    while (getline(file, line)) {
        stringstream iss(line);

        getline(iss, year, ',');
        getline(iss, ageGroup, ',');

        for (int i = 0; i < sizeof(states) / sizeof(states[0]); ++i) {
            getline(iss, stateName, ',');
            if (states[i] == state && ageGroup == ageRange) {
                int cases;
                iss >> cases;

                if (cases > 0) {
                    cout << "Year: " << year << ", Age Group: " << ageGroup << ", Cases: " << cases << endl;
                }
                break;
            }
        }
    }
}
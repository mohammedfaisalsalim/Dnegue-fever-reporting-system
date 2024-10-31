#pragma once
#include <string>
using namespace std;

struct Patient {
    string patientName;
    int age;
    string dateOfTreatment;
    string doctorName;
    string status;
    // Additional fields can be added as needed
     // Default constructor for creating empty Patient objects in the array
    Patient() : patientName(""), age(0), dateOfTreatment(""), doctorName(""), status("") {}

    // Constructor to initialize the patient data
    Patient(const string& name, int patientAge, const string& date, const string& docName, const string& status)
        : patientName(name), age(patientAge), dateOfTreatment(date), doctorName(docName), status(status) {}
};
extern const int MAX_PATIENTS;
const int MAX_PATIENTS = 100;

// Example of how to initialize an array of Patient structures
Patient patients[MAX_PATIENTS] = {
    {"User One", 30, "2023-10-30", "Dr. Kagoya", "High risk"},
    {"User Two", 45, "2023-10-30", "Dr. Kagoya", "Low risk"},
    {"User Three", 50, "2023-10-30", "Dr. Kagoya", "High risk"},
    {"User Two", 45, "2023-10-29", "Dr. Marikao", "Low risk"},
    {"User Three", 50, "2023-10-28", "Dr. Saitama","High risk"}
    // More patients can be added here
};

extern Patient patients[MAX_PATIENTS];
extern int numPatients;
int numPatients = 5;

#pragma once

#include <string>
#include <iostream>

#include "Dailycase.h"
#include "Denguecase.h"
#include "YearStates.h"
#include "WeeklyStates.h"

using namespace std;

struct User {
	string userName;
	string userId;
	string userUsername;
	string userPassword;
	string userState;
	string userPhone;
	string alertmessage[128];
	int totalAlertMessages = 0;
};

// An array of User structures to store details
extern User users[];

// To get the number of users
extern int numUsers;

// An array of User structures to store details
User users[] = {
	{"User One", "UC000", "userone", "user123", "Johor", "0123456789", {"Use insect repellent, wear loose-fitting, long-sleeved shirts and long pants, and control mosquitoes inside and outside your home."}, 1},
	{"User Two", "UC001", "usertwo", "user456", "Melaka", "9876543210", {}, 0},
	{"User Three", "UC002", "userthree", "user789", "Johor", "1234567890", {}, 0}
};

int numUsers = sizeof(users) / sizeof(users[0]);

void userManagePersonalInformation(const string& loggedInUserName)
{
	User* loggedInUser = nullptr;
	bool found = false;
	for (User& user : users) {
		if (user.userName == loggedInUserName) {
			loggedInUser = &user;
			found = true;
		}
	}

	if (!found) {
		std::cout << "User " << loggedInUserName << " not found.\n";
		return;
	}

	int option;

	do
	{
		std::cout << string(50, '-') << '\n';
		std::cout << "User Manage Personal Information" << '\n';
		std::cout << string(50, '-') << '\n';
		std::cout << '\n';
		std::cout << "Select field to modify" << '\n';
		std::cout << '\n';
		std::cout << "   User Name: " << loggedInUser->userName << '\n';
		std::cout << "   User ID: " << loggedInUser->userId << '\n';
		std::cout << "   Username: " << loggedInUser->userUsername << '\n';
		std::cout << "1. Address: " << loggedInUser->userState << '\n';
		std::cout << "2. Phone: " << loggedInUser->userPhone << '\n';
		std::cout << "3. DONE" << '\n';
		std::cout << '\n';

		do
		{
			std::cout << "Please enter your option: ";
			std::cin >> option;
			if (std::cin.fail()) {
				std::cin.clear(); // Clear the error state
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
				std::cout << "Invalid input. Please enter a number.\n";
				option = -1;
				continue; // Prompt the user again
			}
		} while (option < 1 || option > 3);

		if (option == 1)
		{
			string state;
			bool firstTime = true;
			do
			{
				if (!firstTime)
				{
					std::cout << "Invalid state!" << '\n';
				}
				firstTime = false;
				std::cout << "Options: Johor,Kedah,Kelantan,Melaka,Negeri Sembilan,Pahang,Perak,Perlis,Pulau Pinang,Sabah,Sarawak,Selangor,Terengganu,WPKuala Lumpur,WPLabuan" << '\n';
				std::cout << "Please enter your state: ";
				std::cin >> state;
			} while (state != "Johor" && state != "Kedah" && state != "Kelantan" && state != "Melaka" && state != "Negeri Sembilan" && state != "Pahang" && state != "Perak" && state != "Perlis" && state != "Pulau Pinang" && state != "Sabah" && state != "Sarawak" && state != "Selangor" && state != "Terengganu" && state != "WPKuala Lumpur" && state != "WPLabuan");

			loggedInUser->userState = state;
		}
		else if (option == 2)
		{
			string phoneNumber;

			std::cout << "Please enter your phone number: ";
			std::cin >> phoneNumber;

			loggedInUser->userPhone = phoneNumber;
		}
	} while (option != 3);
}

uint8_t yearToBitmask(int year)
{
	switch (year)
	{
	case 2018:
		return 0b00000001;
		break;
	case 2019:
		return 0b00000010;
		break;
	case 2020:
		return 0b00000100;
		break;
	case 2021:
		return 0b00001000;
		break;
	case 2022:
		return 0b00010000;
		break;
	case 2023:
		return 0b00100000;
		break;
	case 2024:
		return 0b01000000;
		break;
	case 2025:
		return 0b10000000;
		break;
	}
}

void userViewTotalDengueCasesBasedOnSelectedYears(YearStates* yearStates)
{
	/*
	Chronic laziness caused me to write this.
	I don't want to make another singly linked list for the year selection,
	so this is the next best option.

	Bit 1 - 2018
	Bit 2 - 2019
	Bit 3 - 2020
	Bit 4 - 2021
	Bit 5 - 2022
	Bit 6 - 2023
	Bit 7 - 2024
	Bit 8 - 2025

	AND operation with the bitmask, if its non-zero, there is a match
	*/
	uint8_t selectedYearsBitmask = 0;
	int year;

	do
	{
		std::cout << string(50, '-') << '\n';
		std::cout << "View total dengue cases based on selected years" << '\n';
		std::cout << string(50, '-') << '\n';
		std::cout << '\n';
		std::cout << "Current selected years: " << '\n';
		std::cout << "2018 - " << ((selectedYearsBitmask & 0b00000001) ? "Yes" : "No") << '\n';
		std::cout << "2019 - " << ((selectedYearsBitmask & 0b00000010) ? "Yes" : "No") << '\n';
		std::cout << "2020 - " << ((selectedYearsBitmask & 0b00000100) ? "Yes" : "No") << '\n';
		std::cout << "2021 - " << ((selectedYearsBitmask & 0b00001000) ? "Yes" : "No") << '\n';
		std::cout << "2022 - " << ((selectedYearsBitmask & 0b00010000) ? "Yes" : "No") << '\n';
		std::cout << "2023 - " << ((selectedYearsBitmask & 0b00100000) ? "Yes" : "No") << '\n';
		std::cout << '\n';

		do
		{
			std::cout << "Please enter a year to toggle (-1 to end): ";
			std::cin >> year;
			if (!std::cin.good())
			{
				std::cin.clear();
				std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				year = -2;
			}
		} while (year == -2);

		switch (year)
		{
		case 2018:
			selectedYearsBitmask ^= 0b00000001;
			break;
		case 2019:
			selectedYearsBitmask ^= 0b00000010;
			break;
		case 2020:
			selectedYearsBitmask ^= 0b00000100;
			break;
		case 2021:
			selectedYearsBitmask ^= 0b00001000;
			break;
		case 2022:
			selectedYearsBitmask ^= 0b00010000;
			break;
		case 2023:
			selectedYearsBitmask ^= 0b00100000;
			break;
		case 2024:
			selectedYearsBitmask ^= 0b01000000;
			break;
		case 2025:
			selectedYearsBitmask ^= 0b10000000;
			break;
		}

	} while (year != -1);

	// TODO: iterate through yearStates and check for bitmask
	YearStates::StateData* current = yearStates->head;
	while (current)
	{
		if (yearToBitmask(current->year) & selectedYearsBitmask) // Matching year
		{
			std::cout << string(50, '-') << std::endl;
			std::cout << "Year: " << current->year << ", Age Group: " << current->ageGroup << std::endl;
			std::cout << "Johor: " << current->Johor << ", Kedah: " << current->Kedah << std::endl;
			std::cout << "Kelantan: " << current->Kelantan << ", Melaka: " << current->Melaka << std::endl;
			std::cout << "Negeri Sembilan: " << current->NegeriSembilan << ", Pahang: " << current->Pahang << std::endl;
			std::cout << "Perak: " << current->Perak << ", Perlis: " << current->Perlis << std::endl;
			std::cout << ", Pulau Pinang: " << current->PulauPinang << std::endl;
			std::cout << "Sabah: " << current->Sabah << ", Sarawak: " << current->Sarawak << std::endl;
			std::cout << "Selangor: " << current->Selangor << ", Terengganu: " << current->Terengganu << std::endl;
			std::cout << "WPKuala Lumpur: " << current->WPKualaLumpur << ", WPLabuan: " << current->WPKualaLumpur << std::endl;
		}
		current = current->next;
	}
}

void userViewTotalDengueCasesBasedOnSelectedStates(YearStates* yearStates)
{
	/*
	Chronic laziness caused me to write this.
	I don't want to make another singly linked list for the state selection,
	so this is the next best option.

	Bit 1  - Johor
	Bit 2  - Kedah
	Bit 3  - Kelantan
	Bit 4  - Melaka
	Bit 5  - Negeri Sembilan
	Bit 6  - Pahang
	Bit 7  - Perak
	Bit 8  - Perlis
	Bit 9  - Pulau Pinang
	Bit 10 - Sabah
	Bit 11 - Sarawak
	Bit 12 - Selangor
	Bit 13 - Terengganu
	Bit 14 - WPKuala Lumpur
	Bit 15 - WPLabuan
	Bit 16 - Unused

	AND operation with the bitmask, if its non-zero, there is a match
	*/
	uint16_t selectedStatesBitmask = 0;
	string state;

	do
	{
		std::cout << string(50, '-') << '\n';
		std::cout << "View total dengue cases based on selected states" << '\n';
		std::cout << string(50, '-') << '\n';
		std::cout << '\n';
		std::cout << "Current selected states: " << '\n';
		std::cout << "Johor - " << ((selectedStatesBitmask & 0b1) ? "Yes" : "No") << '\n';
		std::cout << "Kedah - " << ((selectedStatesBitmask & 0b10) ? "Yes" : "No") << '\n';
		std::cout << "Kelantan - " << ((selectedStatesBitmask & 0b100) ? "Yes" : "No") << '\n';
		std::cout << "Melaka - " << ((selectedStatesBitmask & 0b1000) ? "Yes" : "No") << '\n';
		std::cout << "Negeri Sembilan - " << ((selectedStatesBitmask & 0b10000) ? "Yes" : "No") << '\n';
		std::cout << "Pahang - " << ((selectedStatesBitmask & 0b100000) ? "Yes" : "No") << '\n';
		std::cout << "Perak - " << ((selectedStatesBitmask & 0b1000000) ? "Yes" : "No") << '\n';
		std::cout << "Perlis - " << ((selectedStatesBitmask & 0b10000000) ? "Yes" : "No") << '\n';
		std::cout << "Pulau Pinang - " << ((selectedStatesBitmask & 0b100000000) ? "Yes" : "No") << '\n';
		std::cout << "Sabah - " << ((selectedStatesBitmask & 0b1000000000) ? "Yes" : "No") << '\n';
		std::cout << "Sarawak - " << ((selectedStatesBitmask & 0b10000000000) ? "Yes" : "No") << '\n';
		std::cout << "Selangor - " << ((selectedStatesBitmask & 0b100000000000) ? "Yes" : "No") << '\n';
		std::cout << "Terengganu - " << ((selectedStatesBitmask & 0b1000000000000) ? "Yes" : "No") << '\n';
		std::cout << "WPKuala Lumpur - " << ((selectedStatesBitmask & 0b10000000000000) ? "Yes" : "No") << '\n';
		std::cout << "WPLabuan - " << ((selectedStatesBitmask & 0b100000000000000) ? "Yes" : "No") << '\n';
		std::cout << '\n';

		std::cout << "Please enter a state to toggle ('end' to end): ";
		std::cin >> state;

		if (state == "Johor")
		{
			selectedStatesBitmask ^= 0b1;
		}
		else if (state == "Kedah")
		{
			selectedStatesBitmask ^= 0b10;
		}
		else if (state == "Kelantan")
		{
			selectedStatesBitmask ^= 0b100;
		}
		else if (state == "Melaka")
		{
			selectedStatesBitmask ^= 0b1000;
		}
		else if (state == "Negeri Sembilan")
		{
			selectedStatesBitmask ^= 0b10000;
		}
		else if (state == "Pahang")
		{
			selectedStatesBitmask ^= 0b100000;
		}
		else if (state == "Perak")
		{
			selectedStatesBitmask ^= 0b1000000;
		}
		else if (state == "Perlis")
		{
			selectedStatesBitmask ^= 0b10000000;
		}
		else if (state == "Pulau Pinang")
		{
			selectedStatesBitmask ^= 0b100000000;
		}
		else if (state == "Sabah")
		{
			selectedStatesBitmask ^= 0b1000000000;
		}
		else if (state == "Sarawak")
		{
			selectedStatesBitmask ^= 0b10000000000;
		}
		else if (state == "Selangor")
		{
			selectedStatesBitmask ^= 0b100000000000;
		}
		else if (state == "Terengganu")
		{
			selectedStatesBitmask ^= 0b1000000000000;
		}
		else if (state == "WPKuala Lumpur")
		{
			selectedStatesBitmask ^= 0b10000000000000;
		}
		else if (state == "WPLabuan")
		{
			selectedStatesBitmask ^= 0b100000000000000;
		}

	} while (state != "end");

	// TODO: iterate through yearStates and check for bitmask
	YearStates::StateData* current = yearStates->head;
	while (current)
	{
		std::cout << string(50, '-') << std::endl;
		std::cout << "Year: " << current->year << std::endl;
		std::cout << "Age Group: " << current->ageGroup << std::endl;
		if (selectedStatesBitmask & 0b1)
			std::cout << "Johor: " << current->Johor << std::endl;
		if (selectedStatesBitmask & 0b10)
			std::cout << "Kedah: " << current->Kedah << std::endl;
		if (selectedStatesBitmask & 0b100)
			std::cout << "Kelantan: " << current->Kelantan << std::endl;
		if (selectedStatesBitmask & 0b1000)
			std::cout << "Melaka: " << current->Melaka << std::endl;
		if (selectedStatesBitmask & 0b10000)
			std::cout << "Negeri Sembilan: " << current->NegeriSembilan << std::endl;
		if (selectedStatesBitmask & 0b100000)
			std::cout << "Pahang: " << current->Pahang << std::endl;
		if (selectedStatesBitmask & 0b1000000)
			std::cout << "Perak: " << current->Perak << std::endl;
		if (selectedStatesBitmask & 0b10000000)
			std::cout << "Perlis: " << current->Perlis << std::endl;
		if (selectedStatesBitmask & 0b100000000)
			std::cout << "Pulau Pinang: " << current->PulauPinang << std::endl;
		if (selectedStatesBitmask & 0b1000000000)
			std::cout << "Sabah: " << current->Sabah << std::endl;
		if (selectedStatesBitmask & 0b10000000000)
			std::cout << "Sarawak: " << current->Sarawak << std::endl;
		if (selectedStatesBitmask & 0b100000000000)
			std::cout << "Selangor: " << current->Selangor << std::endl;
		if (selectedStatesBitmask & 0b1000000000000)
			std::cout << "Terengganu: " << current->Terengganu << std::endl;
		if (selectedStatesBitmask & 0b10000000000000)
			std::cout << "WPKuala Lumpur: " << current->WPKualaLumpur << std::endl;
		if (selectedStatesBitmask & 0b100000000000000)
			std::cout << "WPLabuan: " << current->WPKualaLumpur << std::endl;
		current = current->next;
	}
}

void userViewDailyDengueCasesForAllStatesInDescendingOrder()
{
	std::cout << string(50, '-') << '\n';
	std::cout << "View daily dengue cases for all states in descending order" << '\n';
	std::cout << string(50, '-') << '\n';
	std::cout << '\n';

	std::string dates = "";

	for (int i = 0; i < numPatients; i++) {
		//if (!patients[i].dateOfTreatment)
		if (dates.find(patients[i].dateOfTreatment) == std::string::npos)
		{
			dates += patients[i].dateOfTreatment + "\n";
		}
	}

	std::cout << string(25, '-') << '\n';
	std::cout << "Dates with cases:\n";
	std::cout << dates;
	std::cout << string(25, '-') << '\n';

	string dateOfTreatment;
	std::cout << "Enter date to search for (YYYY-MM-DD): ";
	std::cin.ignore(); // Clear newline character after entering a number
	getline(std::cin, dateOfTreatment);

	Dailycase dailycase;
	dailycase.initializeStates();

	bool found = false;
	for (int i = 0; i < numPatients; i++) {
		if (patients[i].dateOfTreatment == dateOfTreatment)
		{
			bool foundUser = false;
			string state;
			for (int j = 0; j < numUsers; j++) {
				if (users[j].userName == patients[i].patientName) {
					state = users[j].userState;
					foundUser = true;
					found = true;
				}
			}

			if (foundUser)
			{
				dailycase.findDailycaseByState(state)->amount++;
			}
		}
	}

	if (found)
	{
		dailycase.sortDescending();
		std::cout << string(50, '-') << '\n';

		Dailycase::DailycaseNode* current = dailycase.head;
		while (current != nullptr) {
			//if (current->amount != 0) {
			std::cout << current->state << ": " << current->amount << '\n';
			//}
			current = current->next;
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "No patients found for the date '" << dateOfTreatment << "'.\n";
	}
}

void userViewDengueAlertMessagesFromTheMOHAdmin(const string& loggedInUserName)
{
	User* loggedInUser = nullptr;
	bool found = false;
	for (User& user : users) {
		if (user.userName == loggedInUserName) {
			loggedInUser = &user;
			found = true;
		}
	}

	if (!found) {
		std::cout << "User " << loggedInUserName << " not found.\n";
		return;
	}

	if (loggedInUser->totalAlertMessages == 0)
	{
		std::cout << "There are no messages.\n";
		return;
	}

	int currentIndex = 0;

	int option;

	do
	{
		std::cout << string(50, '-') << '\n';
		std::cout << "View dengue alert messages from the MOH admin" << '\n';
		std::cout << string(50, '-') << '\n';
		std::cout << '\n';
		std::cout << "Message " << currentIndex + 1 << " of " << loggedInUser->totalAlertMessages << '\n';
		std::cout << '\n';
		std::cout << "Message:" << '\n';
		std::cout << loggedInUser->alertmessage[currentIndex] << '\n';
		std::cout << '\n';
		std::cout << "1. Previous Message" << '\n';
		std::cout << "2. Next Message" << '\n';
		std::cout << "3. Exit" << '\n';
		std::cout << '\n';

		do
		{
			std::cout << "Please enter your option: ";
			std::cin >> option;
			if (std::cin.fail()) {
				std::cin.clear(); // Clear the error state
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
				std::cout << "Invalid input. Please enter a number.\n";
				option = -1;
				continue; // Prompt the user again
			}
		} while (option < 1 || option > 3);

		if (option == 1)
		{
			currentIndex--;
			if (currentIndex < 0)
			{
				currentIndex = 0;
			}
		}
		else if (option == 2)
		{
			currentIndex++;
			if (currentIndex >= loggedInUser->totalAlertMessages)
			{
				currentIndex = loggedInUser->totalAlertMessages - 1;
			}
		}
	} while (option != 3);
}

void userViewPersonalPastDengueFeverStatus(const string& loggedInUserName)
{
	User* loggedInUser = nullptr;
	bool found = false;
	for (User& user : users) {
		if (user.userName == loggedInUserName) {
			loggedInUser = &user;
			found = true;
		}
	}

	if (!found) {
		std::cout << "User " << loggedInUserName << " not found.\n";
		return;
	}

	bool foundPatient = false;
	for (int i = 0; i < numPatients; i++) {
		if (patients[i].patientName == loggedInUser->userName)
		{
			foundPatient = true;
			std::cout << string(50, '-') << '\n'
				<< "Patient Name: " << patients[i].patientName
				<< ", Age: " << patients[i].age
				<< ", Date of Treatment: " << patients[i].dateOfTreatment
				<< ", Doctor Name: " << patients[i].doctorName
				<< ", Status: " << patients[i].status
				<< std::endl;
		}
	}

	if (!foundPatient)
	{
		std::cout << "No personal records found.\n";
		return;
	}
}

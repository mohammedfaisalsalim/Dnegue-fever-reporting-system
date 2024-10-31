#pragma once
#include <iostream>
#include <string>

using namespace std;

class WeeklyStates {
public:
    struct StateData {
        int year, week;
        string Johor, Kedah, Kelantan, Melaka, NegeriSembilan, Pahang, Perak, Perlis, PulauPinang, Sabah, Sarawak, Selangor, Terengganu, WPKualaLumpur, WPLabuan;
        StateData* next;
        StateData* prev; // Add a prev pointer for doubly linked list
    };

    StateData* head;
    StateData* tail; // Add a tail pointer to maintain the last element.

public:
    WeeklyStates(const string& title) : head(nullptr), tail(nullptr) {
        cout << title << endl;
    }

    ~WeeklyStates() {
        while (head != nullptr) {
            StateData* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void readFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            istringstream iss(line);
            string tahun, minggu, Johor, Kedah, Kelantan, Melaka, NegeriSembilan, Pahang, Perak, Perlis, PulauPinang, Sabah, Sarawak, Selangor, Terengganu, WPKualaLumpur, WPLabuan;
            std::getline(iss, tahun, ',');
            std::getline(iss, minggu, ',');
            std::getline(iss, Johor, ',');
            std::getline(iss, Kedah, ',');
            std::getline(iss, Kelantan, ',');
            std::getline(iss, Melaka, ',');
            std::getline(iss, NegeriSembilan, ',');
            std::getline(iss, Pahang, ',');
            std::getline(iss, Perak, ',');
            std::getline(iss, Perlis, ',');
            std::getline(iss, PulauPinang, ',');
            std::getline(iss, Sabah, ',');
            std::getline(iss, Sarawak, ',');
            std::getline(iss, Selangor, ',');
            std::getline(iss, Terengganu, ',');
            std::getline(iss, WPKualaLumpur, ',');
            std::getline(iss, WPLabuan, ',');
            try {
                int tahunValue = stoi(tahun);
                int mingguValue = stoi(minggu);
                insertToEndList(tahunValue, mingguValue, Johor, Kedah, Kelantan, Melaka, NegeriSembilan, Pahang, Perak, Perlis, PulauPinang, Sabah, Sarawak, Selangor, Terengganu, WPKualaLumpur, WPLabuan);
            }
            catch (const exception& e) {
                cerr << "Error converting string to numeric value: " << e.what() << endl;
            }
        }
    }

    void insertToEndList(int year, int week, const string& Johor, const string& Kedah, const string& Kelantan, const string& Melaka, const string& NegeriSembilan, const string& Pahang, const string& Perak, const string& Perlis, const string& PulauPinang, const string& Sabah, const string& Sarawak, const string& Selangor, const string& Terengganu, const string& WPKualaLumpur, const string& WPLabuan) {
        StateData* newNode = new StateData;
        newNode->year = year;
        newNode->week = week;
        newNode->Johor = Johor;
        newNode->Kedah = Kedah;
        newNode->Kelantan = Kelantan;
        newNode->Melaka = Melaka;
        newNode->NegeriSembilan = NegeriSembilan;
        newNode->Pahang = Pahang;
        newNode->Perak = Perak;
        newNode->Perlis = Perlis;
        newNode->PulauPinang = PulauPinang;
        newNode->Sabah = Sabah;
        newNode->Sarawak = Sarawak;
        newNode->Selangor = Selangor;
        newNode->Terengganu = Terengganu;
        newNode->WPKualaLumpur = WPKualaLumpur;
        newNode->WPLabuan = WPLabuan;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            tail = newNode; // When the list is empty, both head and tail point to the new node.
        }
        else {
            newNode->prev = tail; // Update the previous pointer of the new node.
            tail->next = newNode;
            tail = newNode; // Update the tail to the new node.
        }
    }

    void displayList() {
        StateData* current = head;
        while (current != nullptr) {
            cout << string(50, '-') << endl;
            cout << "Year: " << current->year << ", Week: " << current->week << endl;
            std::cout << "Johor: " << current->Johor << ", Kedah: " << current->Kedah << std::endl;
            std::cout << "Kelantan: " << current->Kelantan << ", Melaka: " << current->Melaka << std::endl;
            std::cout << "Negeri Sembilan: " << current->NegeriSembilan << ", Pahang: " << current->Pahang << std::endl;
            std::cout << "Perak: " << current->Perak << ", Perlis: " << current->Perlis << std::endl;
            std::cout << "Perlis: " << current->Perlis << ", Pulau Pinang: " << current->PulauPinang << std::endl;
            std::cout << "Sabah: " << current->Sabah << ", Sarawak: " << current->Sarawak << std::endl;
            std::cout << "Selangor: " << current->Selangor << ", Terengganu: " << current->Terengganu << std::endl;
            std::cout << "WPKuala Lumpur: " << current->WPKualaLumpur << ", WPLabuan: " << current->WPKualaLumpur << std::endl;
            current = current->next;
        }
    }
};

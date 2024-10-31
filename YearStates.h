
#pragma once
#include <iostream>
#include <string>

using namespace std;

class YearStates {
public:
    struct StateData {
        int year;
        string ageGroup;
        string Johor, Kedah, Kelantan, Melaka, NegeriSembilan, Pahang, Perak, Perlis, PulauPinang, Sabah, Sarawak, Selangor, Terengganu, WPKualaLumpur, WPLabuan;
        StateData* next;
        StateData* prev;
    };

    StateData* head;
    StateData* tail; // Add a tail pointer to maintain the last element.

public:
    YearStates(const string& title) : head(nullptr), tail(nullptr) {
        cout << title << endl;
    }

    ~YearStates() {
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

        string line, tahun, ageGroup, Johor, Kedah, Kelantan, Melaka, NegeriSembilan, Pahang, Perak, Perlis, PulauPinang, Sabah, Sarawak, Selangor, Terengganu, WPKualaLumpur, WPLabuan;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            istringstream iss(line);
            getline(iss, tahun, ',');
            getline(iss, ageGroup, ',');
            getline(iss, Johor, ',');
            getline(iss, Kedah, ',');
            getline(iss, Kelantan, ',');
            getline(iss, Melaka, ',');
            getline(iss, NegeriSembilan, ',');
            getline(iss, Pahang, ',');
            getline(iss, Perak, ',');
            getline(iss, Perlis, ',');
            getline(iss, PulauPinang, ',');
            getline(iss, Sabah, ',');
            getline(iss, Sarawak, ',');
            getline(iss, Selangor, ',');
            getline(iss, Terengganu, ',');
            getline(iss, WPKualaLumpur, ',');
            getline(iss, WPLabuan);

            try {
                int year = stoi(tahun);
                insertToEndList(year, ageGroup, Johor, Kedah, Kelantan, Melaka, NegeriSembilan, Pahang, Perak, Perlis, PulauPinang, Sabah, Sarawak, Selangor, Terengganu, WPKualaLumpur, WPLabuan);
            }
            catch (const exception& e) {
                cerr << "Error converting string to numeric value: " << e.what() << endl;
            }
        }
    }

    void insertToEndList(int year, const string& ageGroup, const string& Johor, const string& Kedah, const string& Kelantan, const string& Melaka, const string& NegeriSembilan, const string& Pahang, const string& Perak, const string& Perlis, const string& PulauPinang, const string& Sabah, const string& Sarawak, const string& Selangor, const string& Terengganu, const string& WPKualaLumpur, const string& WPLabuan) {
        StateData* newNode = new StateData;
        newNode->year = year;
        newNode->ageGroup = ageGroup;
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
            cout << "Year: " << current->year << ", Age Group: " << current->ageGroup << endl;
            cout << "Johor: " << current->Johor << ", Kedah: " << current->Kedah << endl;
            cout << "Kelantan: " << current->Kelantan << ", Melaka: " << current->Melaka << endl;
            cout << "Negeri Sembilan: " << current->NegeriSembilan << ", Pahang: " << current->Pahang << endl;
            cout << "Perak: " << current->Perak << ", Perlis: " << current->Perlis << endl;
            cout << "Perlis: " << current->Perlis << ", Pulau Pinang: " << current->PulauPinang << endl;
            cout << "Sabah: " << current->Sabah << ", Sarawak: " << current->Sarawak << endl;
            cout << "Selangor: " << current->Selangor << ", Terengganu: " << current->Terengganu << endl;
            cout << "WPKuala Lumpur: " << current->WPKualaLumpur << ", WPLabuan: " << current->WPLabuan << endl;
            current = current->next;
        }
    }
};

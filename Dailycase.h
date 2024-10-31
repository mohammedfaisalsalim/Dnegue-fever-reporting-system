#pragma once

#include <string>
#include <iostream>

class Dailycase
{
public:
	struct DailycaseNode
	{
		std::string state = "";
		int amount = 0;
		DailycaseNode* prev = nullptr;
		DailycaseNode* next = nullptr;

		DailycaseNode() {}
		DailycaseNode(std::string state, int amount) : state(state), amount(amount) {}
		DailycaseNode(std::string state, int amount, DailycaseNode* next) : state(state), amount(amount), prev(prev), next(next) {}
	};

	DailycaseNode* head = nullptr;
	DailycaseNode* tail = nullptr;

	~Dailycase() {
		while (head != nullptr) {
			DailycaseNode* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void clear()
	{
		while (head != nullptr) {
			DailycaseNode* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void initializeStates()
	{
		insertToEndList("Johor", 0);
		insertToEndList("Kedah", 0);
		insertToEndList("Kelantan", 0);
		insertToEndList("Melaka", 0);
		insertToEndList("Negeri Sembilan", 0);
		insertToEndList("Pahang", 0);
		insertToEndList("Perak", 0);
		insertToEndList("Perlis", 0);
		insertToEndList("Pulau Pinang", 0);
		insertToEndList("Sabah", 0);
		insertToEndList("Sarawak", 0);
		insertToEndList("Selangor", 0);
		insertToEndList("Terengganu", 0);
		insertToEndList("WPKuala Lumpur", 0);
		insertToEndList("WPLabuan", 0);
	}

	void insertToEndList(
		std::string state,
		int amount
	) {
		DailycaseNode* newNode = new DailycaseNode(state, amount);

		if (head == nullptr) {
			head = newNode;
			tail = newNode;
		}
		else {
			DailycaseNode* current = tail;
			current->next = newNode;
			newNode->prev = current;
			tail = newNode;
		}
	}

	DailycaseNode* at(int index)
	{
		int transversed = 0;
		DailycaseNode* current = head;
		while (current != nullptr) {
			if (transversed == index)
			{
				return current;
			}
			transversed++;
			current = current->next;
		}
		return nullptr;
	}

	int size()
	{
		int transversed = 0;
		DailycaseNode* current = head;
		while (current != nullptr) {
			transversed++;
			current = current->next;
		}
		return transversed;
	}

	DailycaseNode* findDailycaseByState(string state)
	{
		DailycaseNode* current = head;
		while (current != nullptr) {
			if (current->state == state)
			{
				return current;
			}
			current = current->next;
		}

		return nullptr;
	}

	void sortDescending()
	{
		DailycaseNode key;
		int j;

		// Iterate through the array
		for (int i = 1; i < size(); ++i)
		{
			key.state = at(i)->state; // Save the key for comparison later on
			key.amount = at(i)->amount;
			j = i - 1;

			// Move elements greater than key that are before index i to 1 position ahead
			// (Technically not moving but overwriting the data)
			while (j >= 0 && at(j)->amount < key.amount) // If you want to change ascending/descending, change the comparison here
			{
				at(j + 1)->state = at(j)->state;
				at(j + 1)->amount = at(j)->amount;
				--j;
			}

			at(j + 1)->state = key.state;
			at(j + 1)->amount = key.amount;
		}
	}
};
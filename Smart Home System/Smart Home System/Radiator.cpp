#include "Radiator.h"
#include <iostream>
#include <random>
#include <ctime>

Radiator::Radiator(const string& deviceType, const string& chosenName, bool state, float currentTemp, int start, int end) : Device(state, deviceType, chosenName), currentTemp(currentTemp), start(start), end(end) {

	CheckSchedule(start, end); // Check that the radiator is on during scheduled time

	cout << "Radiator added. Name: " << GetChosenName() << " State : ";
	GetState() ? cout << "ON Current tempurature: " << currentTemp << "C " : cout << "OFF ";

	DisplaySchedule(start, end);
}


void Radiator::FullView() {
	cout << "Device Type: Radiator" << endl;
	cout << "Device Name: " << GetChosenName() << endl;
	
	if (GetState() == true) {
		cout << "State: ON" << endl;
		cout << "Current tempurature: " << currentTemp << "C" << endl;
	}
	else cout << "State: OFF" << endl;

	DisplaySchedule(start, end);
}

void Radiator::DeviceManager(vector<unique_ptr<Device>>& devices) {

	bool modifying = true;

	while (modifying) {

		cout << endl;

		FullView();

		// Menu
		cout << "\n\nWhat would you like to do?\n" << endl;

		cout << "1. Change Name" << endl;
		GetState() ? cout << "2. Turn off" << endl : cout << "2. Turn on" << endl;
		cout << "3. Remove Device" << endl;
		cout << "4. Change Schedule" << endl;
		cout << "0. Return" << endl;

		int input;
		cin >> input;
		if (cin.fail()) input = -1; // Error handling - if user puts in characters display error

		switch (input) {
			case 1: ChangeName(devices); break;
			case 2:
				TurnOnTurnOff();
				if (GetState() == true) currentTemp = rand() % 45;
				break;
			case 3: if (Delete(devices) == true) modifying = false; break;
			case 4: ChangeSchedule(); break;
			case 0:
				system("cls");
				modifying = false;
				break;
			default:
				system("cls");
				cout << "\nPlease choose a valid option." << endl;
				break;
		}
		cout << endl;
	} 
}

void Radiator::ChangeSchedule() {

	bool changed = false;
	cout << "Current ";
	DisplaySchedule(start, end);

	while (!changed) {

		int newStart, newEnd;

		// Get the start time
		cout << "When would you like the radiator to turn on? (e.g., 11am, 4pm)" << endl;
		newStart = GetTimeInput();

		// Get the end time
		cout << "When would you like the radiator to turn off? (e.g., 11am, 4pm)" << endl;
		newEnd = GetTimeInput();

		// Validate schedule
		if (newStart < newEnd) {

			start = newStart;
			end = newEnd;

			CheckSchedule(start, end);

			changed = true;
		}
		else cout << "Invalid input. The start time must be earlier than the end time.\n";
	}
}
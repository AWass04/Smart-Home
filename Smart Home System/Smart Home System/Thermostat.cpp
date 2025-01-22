#include "Thermostat.h"
#include <iostream>
#include <cctype>
#include <ctime>
#include <random>


Thermostat::Thermostat(const string& deviceType, const string& chosenName, bool state, time_t start, time_t end) : Device(state, deviceType, chosenName), start(start), end(end) {

	CheckSchedule(start, end); // Make sure its not turned on when its not in scheduled time
	
	cout << "Thermostat added. Name: " << GetChosenName() << " State: ";
	GetState() ? cout << "ON " : cout << "OFF ";

	DisplaySchedule(start, end);
}

void Thermostat::FullView() {

	cout << "Device Type: Thermostat" << endl;
	cout << "Device Name: " << GetChosenName() << endl;
	
	GetState() == true ? cout << "State: ON" << endl : cout << "State: OFF" << endl;

	if (boostHeating == true) cout << "Heating Boost: ON" << endl;
	else cout << "Heating Boost: OFF" << endl;

	DisplaySchedule(start, end);
}

void Thermostat::DeviceManager(vector<unique_ptr<Device>>& devices) {

	bool modifying = true;

	while (modifying) {

		cout << endl;

		FullView();

		// Menu
		cout << "\n\nWhat would you like to do?\n" << endl;

		cout << "1. Change Name" << endl;
		GetState() ? cout << "2. Turn off" << endl : cout << "2. Turn on" << endl;
		cout << "3. Change Schedule" << endl;
		cout << "4. Remove Device" << endl;
		GetState() ? cout << "" << endl : cout << "5. Apply Heating Boost for 1 Hour" << endl;
		cout << "0. Return" << endl;

		int input;
		cin >> input;

		if (cin.fail()) input = -1; // Error handling - if user puts in characters display error

		switch (input) {
			case 1: ChangeName(devices); break;
			case 2: TurnOnTurnOff(); break;
			case 3: ChangeSchedule(); break;
			case 4: if (Delete(devices) == true) modifying = false; break;
			case 5:
				if (GetState()) {

					system("cls");
					cout << "\nPlease choose a valid option." << endl;
				}
				else {
					TurnOnHeatingBoost();
					TurnOnTurnOff();
				}
				break;
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

void Thermostat::ChangeSchedule() {

	bool changed = false;
	cout << "Current ";
	DisplaySchedule(start, end);

	while (!changed) {

		int newStart, newEnd;

		// Get the start time
		cout << "When would you like the thermostat to turn on? (e.g., 11am, 4pm)" << endl;
		newStart = GetTimeInput();

		// Get the end time
		cout << "When would you like the thermostat to turn off? (e.g., 11am, 4pm)" << endl;
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
#include "PlugSocket.h"
#include <iostream>
#include <ctime>

PlugSocket::PlugSocket(const string& deviceType, const string& chosenName, bool state, int start, int end, int sleepTimer) : Device(state, deviceType, chosenName), start(start), end(end), sleepTimer(sleepTimer) {

	CheckSchedule(start, end); // Check its on when supposed to

	cout << "Plug Socket added. Name: " << GetChosenName() << " State: ";
	GetState() ? cout << "ON Timer: " << sleepTimer : cout << "OFF ";

	DisplaySchedule(start, end);
}

void PlugSocket::FullView() {
	
	// Get current date and time
	time_t timestamp = time(nullptr);
	struct tm dateTime = *localtime(&timestamp);

	cout << "Device Type: Plug Socket" << endl;
	cout << "Device Name: " << GetChosenName() << endl;

	if (GetState() == true) {
		cout << "State: ON" << endl;
		CurrentEnergyUsage();

		if (sleepTimer > 0) cout << "Sleep Timer: " << sleepTimer << " Minutes" << endl;
		else cout << "Timer: N/A" << endl;
	}
	else cout << "State: OFF" << endl;
	
	DisplaySchedule(start, end);

	// display historic information for the last 3 days
	cout << "\n                Historic infromation               " << endl;
	cout << "---------------------------------------------------" << endl;

	for (int i = 0; i < 3; ++i) {
		char output[50];

		dateTime.tm_mday -= 1;// reduce current day by 1
		mktime(&dateTime);

		strftime(output, 50, "%B %e, %Y", &dateTime); // format

		cout << output << " Hours Active: " << end - start << " hrs Cost: " << (end - start) * energyCost << endl;
	}
	cout << "---------------------------------------------------" << endl;
}

void PlugSocket::CurrentEnergyUsage() {

	// get current date and time
	time_t timestamp = time(&timestamp);
	struct tm dateTime = *localtime(&timestamp);

	const int adverageUsagePerHour = 3;
	int timeActive = dateTime.tm_hour - start; // Get how long the plug socket has been on for

	double cost = timeActive * energyCost;

	cout << "Time active: " << timeActive << "hrs Current cost: " << cost << endl;
}

void PlugSocket::DeviceManager(vector<unique_ptr<Device>>& devices) {
	
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
		GetState() ? cout << "4. Adjust Sleep Timer" << endl : cout << "";
		cout << "0. Return" << endl;

		int input;
		cin >> input;
		if (cin.fail()) input = -1; // Error handling - if user puts in characters display error

		switch (input) {
			case 1: ChangeName(devices); break;
			case 2: TurnOnTurnOff(); break;
			case 3: if (Delete(devices) == true) modifying = false; break;
			case 4: ChangeSchedule(); break;
			case 5:
				
				if (GetState()) AdjustSleepTimer();
				else {

					system("cls");
					cout << "\nPlease choose a valid option." << endl;
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

void PlugSocket::AdjustSleepTimer() {

	int min = -1;

	cout << "\nHow many minutes would you like the light to turn off in? or enter 0 to turn off timer." << endl;

	do {
		cin >> min;

		// Error handling
		if (min < 0 || cin.fail()) {

			cout << "\nPlease enter a whole number:" << endl;
			cin.clear();
			cin.ignore();
		}
	} while (min < 0);

	sleepTimer = min;
}

void PlugSocket::ChangeSchedule() {

	bool changed = false;
	cout << "Current ";
	DisplaySchedule(start, end);

	while (!changed) {

		int newStart, newEnd;

		// Get the start time
		cout << "When would you like the plug socket to turn on? (e.g., 11am, 4pm)" << endl;
		newStart = GetTimeInput();

		// Get the end time
		cout << "When would you like the plug socket to turn off? (e.g., 11am, 4pm)" << endl;
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
#include "Light.h"
#include <iostream>

Light::Light::Light(const string& deviceType, const string& chosenName, bool state, int brightness, int sleepTimer) : Device(state, deviceType, chosenName), brightness(brightness), sleepTimer(sleepTimer)
{
	cout << "Light added. Name: " << GetChosenName() << " State: ";
	GetState() ? cout << "ON Brighness : " << brightness << " Timer: " << sleepTimer << endl: cout << "OFF" << endl;
}

void Light::FullView() {

	cout << "Device Type: Light" << endl;
	cout << "Device Name: " << GetChosenName() << endl;
	if (GetState() == true) {
		
		cout << "State: ON" << endl;
		cout << "Brightness: " << brightness << "%" << endl;

		if (sleepTimer > 0) cout << "Sleep Timer: " << sleepTimer << " Minutes" << endl;
		else cout << "Timer: N/A" << endl;
	}
	else cout << "State: OFF" << endl;
}

void Light::DeviceManager(vector<unique_ptr<Device>>& devices) {

	bool modifying = true;

	while (modifying) {

		cout << endl;

		FullView();

		cout << "\n\nWhat would you like to do?\n" << endl;

		cout << "1. Change Name" << endl;
		cout << "2. Turn" << (GetState() ? " Off" : " On") << endl;
		cout << "3. Remove Device" << endl;
		if (GetState()) {
			cout << "4. Set sleep timer" << endl;
			cout << "5. Adjust brightness" << endl;
		}
		cout << "0. Return" << endl;

		int input;
		cin >> input;

		if (cin.fail()) input = -1; // Error handling - if user puts in characters display error

		switch (input) {
			case 1: ChangeName(devices); break;
			case 2: TurnOnTurnOff(); break;			
			case 3: if (Delete(devices) == true) modifying = false; break;
			case 4:
				if (GetState()) AdjustSleepTimer();
				else cout << "\nPlease choose a valid option." << endl;
				break;
			case 5:		
				if (GetState()) AdjustBrightness();
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

void Light::AdjustBrightness() {

	cout << "What brightness level would you like to set the device too?" << endl;

	int newBrightness = ErrorCheck(1, 100, "\nInvalid Input. Please enter a whole number between 1 - 100.");
	AdjustBrightness(newBrightness);
}

void Light::AdjustSleepTimer() {
	cout << "\nHow many minutes would you like the light to turn off in? or enter 0 to turn off timer." << endl;

	int newTimer = ErrorCheck(0, INT_MAX, "\nInvalid input. Please enter a whole positive number or enter 0 to turn off the timer.");
	AdjustSleepTimer(newTimer);

}

int Light::ErrorCheck(int minimum, int maximum, const string& errorMessage) {

	int value;

	while (true) {
		cin >> value;

		if (value < minimum || value > maximum || cin.fail()) {

			cout << errorMessage << endl;
			cin.clear();
			cin.ignore();
		}
		else return value;
	}
}
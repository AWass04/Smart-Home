#include "Speaker.h"
#include <iostream>

Speaker::Speaker(const string& deviceType, const string& chosenName, bool state, int volume) : Device(state, deviceType, chosenName), volume(volume){
	
	cout << "Speaker added. Name: " << GetChosenName() << " State: ";
	GetState() ? cout << "ON Volume: " << volume << "%" << endl : cout << "OFF " << endl;
}

void Speaker::FullView() {

	cout << "Device Type: Speaker" << endl;
	cout << "Device Name: " << GetChosenName() << endl;

	if (GetState() == true) {
		cout << "State: ON" << endl;
		cout << "Current Volume: " << volume << endl;
	}
	else cout << "State: OFF" << endl;
}

void Speaker::DeviceManager(vector<unique_ptr<Device>>& devices) {

	bool modifying = true;

	while (modifying) {

		cout << endl;

		FullView();

		// Menu
		cout << "\n\nWhat would you like to do?\n" << endl;

		cout << "1. Change Name" << endl;
		GetState() ? cout << "2. Turn off" << endl : cout << "2. Turn on" << endl;
		cout << "3. Remove Device" << endl;
		GetState() ? cout << "4. Change Volume"<< endl : cout << "";
		cout << "0. Return" << endl;

		int input;
		cin >> input;
		if (cin.fail()) input = -1; // Error handling - if user puts in characters display error

		switch (input) {
			case 1: ChangeName(devices); break;
			case 2: TurnOnTurnOff(); break;
			case 3: if (Delete(devices) == true) modifying = false; break;
			case 4:			
				if (GetState()) ChangeVolume();
				else {

					system("cls");
					cout << "\nPlease choose a valid option.\n" << endl;
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

void Speaker::ChangeVolume()
{
	int newVolume = -1;

	cout << "\nWhat would you like to chnage the volume level too?" << endl;
	
	do {
		cin >> newVolume;

		// Error handling - for an invalid input
		if (cin.fail() || newVolume < 0 || newVolume > 100) {

			cout << "\nPlease enter a whole number between 0 - 100:" << endl;
			cin.clear();
			cin.ignore();
		}
	} while (newVolume < 0 || newVolume > 100);

	volume = newVolume;
}

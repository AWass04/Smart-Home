#include "TempSensor.h"
#include <iostream>
#include <random>

TempSensor::TempSensor(const string& deviceType, const string& chosenName, bool state) : Device(state, deviceType, chosenName) {
	
	humidity = rand() % 101;
	temp = rand() % 31;

	cout << "Tempature and humidity sensor added. Name: " << GetChosenName() << " " << temp << "C / " << humidity << "% humidity" << endl;
}

void TempSensor::FullView() {
	
	time_t timestamp = time(nullptr);
	struct tm dateTime = *localtime(&timestamp);
	int historicTemp = temp;
	int historicHumidity = humidity;
	
	cout << "Device Type: Tempurature and Humidity Sensor" << endl;
	cout << "Device Name: " << GetChosenName() << endl;

	cout << "Current Tempurature: " << temp << "C " << endl;
	cout << "Current Humidity: " << humidity << "% " << endl;

	cout << "\n---------------------------------------------------" << endl;

	for (int i = 0; i < 3; ++i) {
		char output[50];

		dateTime.tm_hour -= 1;
		mktime(&dateTime);

		strftime(output, 50, "%I %p", &dateTime);

		if (rand() % 2 == 0) {
			historicTemp += rand() % 11;
			historicHumidity += rand() % 11;
		}
		else {

			historicTemp -= rand() % 11;
			historicHumidity -= rand() % 11;
		}

		cout << output <<  ": Tempurature: " << historicTemp << "C Humidity: " << historicHumidity << "% " << endl;
	}
	cout << "---------------------------------------------------" << endl;
}

void TempSensor::DeviceManager(vector<unique_ptr<Device>>& devices) {
	bool modifying = true;
	string answer;
	int input;

	do {

		cout << endl;

		FullView();

	
		cout << "\n\nWhat would you like to do?\n" << endl;

		cout << "1. Change Name" << endl;
		cout << "2. Remove Device" << endl;
		cout << "0. Return" << endl;

		cin >> input;
		
		switch (input) {
			case 1:
				ChangeName(devices);
				break;
			case 2:
				if (Delete(devices) == true) modifying = false;
				break;
			case 0:
				system("cls");
				modifying = false;
				break;
			default:
				cout << "\nPlease choose a valid option.\n" << endl;
				break;
		}

		cout << endl;

	} while (modifying);

}

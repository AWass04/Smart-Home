#include "Device.h"
#include "PlugSocket.h"
#include "Radiator.h"
#include "Light.h"
#include "Thermostat.h"
#include "TempSensor.h"
#include "Speaker.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <iterator>
#include <stdlib.h> 
#include <algorithm>
#include <cstring>
#include <cctype>
#include <map>
#include <unordered_map>
#include <functional>

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  BLUE STICKER 

void LoadDevices(vector<unique_ptr<Device>>& devices);
void AddDevice(vector<unique_ptr<Device>>& devices);
void ModifyDevice(vector<unique_ptr<Device>>& devices);
void StoreDevices(const vector<unique_ptr<Device>>& devices);
string LowerCase(string word);
bool NameExists(string name, vector<unique_ptr<Device>>& devices);
void Display(string sortType, vector<unique_ptr<Device>>& devices);

using namespace std;

int main() {

	#ifdef _DEBUG
		//_CrtSetBreakAlloc();
		_onexit(_CrtDumpMemoryLeaks);
	#endif

	// Load from file
	vector<unique_ptr<Device>> devices;
	LoadDevices(devices);

	unordered_map<string, function<void()>> menu;

	menu["1"] = [&] {Display("None", devices);};
	menu["2"] = [&] {Display("Name", devices);};
	menu["3"] = [&] {Display("Device", devices);};
	menu["4"] = [&] {ModifyDevice(devices);};
	menu["5"] = [&] {AddDevice(devices);};
	menu["0"] = nullptr;

	string input;

	do {

		//Menu
		cout << "                      Menu                      " << endl;
		cout << "=================================================\n" << endl;

		cout << "Enter a devices name to do interact:\n" << endl;
		
		// Diaplaying devices One click actions
		for (vector<unique_ptr<Device>>::iterator it = devices.begin(); it != devices.end(); ++it) {

			(*it)->Display(true);
		}

		cout << "\nOptions:\n" << endl;
		cout << "1. List all devices" << endl;
		cout << "2. Sort by name" << endl;
		cout << "3. Sort by device type" << endl;
		cout << "4. Interact with all device features" << endl;
		cout << "5. Add device" << endl;
		cout << "0. Exit" << endl;
		cout << "=================================================\n" << endl;

		cin >> input;
		input = LowerCase(input);

		// Check if exists in map
		if (menu.count(input) > 0) {

			if (menu[input]) {

				menu[input]();  // Call the corresponding method
			}
			else {
				cout << "Goodbye! :)" << endl;
			}
		}
		else { // Check to see if its a one click action

			// if device found interact
			bool found = false;

			for (const auto& device : devices) {
				if (LowerCase(device->GetChosenName()) == LowerCase(input)) {
					found = true;
					device->TurnOnTurnOff(); 
				}
			}

			system("cls");
			
			// Error handling - If device isnt found produce error
			if (!found) {
				cout << "\nInvalid input. Try again.\n" << endl;
			}
		}
	} while (input != "0");

	StoreDevices(devices);
	return 0;
}

void AddDevice(vector<unique_ptr<Device>>& devices) {
	system("cls");

	unordered_map<string, int> map = {
		{"light", 1},
		{"thermostat", 2},
		{"temperature and humidity sensor", 3},
		{"speaker", 4},
		{"radiator", 5},
		{"plug socket", 6},
		{"0", 0}
	};

	string chosenName;
	int choice = -1;
	string input;

	do {
		// Menu
        cout << "\nWhat device would you like to add:\n" << endl;
        cout << "Light" << endl;
        cout << "Thermostat" << endl;
        cout << "Temperature and Humidity Sensor" << endl;
        cout << "Speaker" << endl;
        cout << "Radiator" << endl;
        cout << "Plug Socket" << endl;
        cout << "Enter 0 to Return\n" << endl;

		cin.ignore(); // stop it taking previous input as input for this menu
		getline(cin, input);
        input = LowerCase(input);

        if (map.count(input) > 0) { // Check input exists
			choice = map.find(input)->second;
			
			if (choice == 0) return;

            // Check for name uniqueness
            bool alreadyTaken = true;

            while (alreadyTaken) {
                cout << "\nPlease enter a name for the device:" << endl;
				getline(cin, chosenName);

				chosenName.erase(remove(chosenName.begin(), chosenName.end(), ' '), chosenName.end());

				// Error handling - making sure name is unoque and has at least one character
                if (NameExists(chosenName, devices) || chosenName.length() < 1) {
                    cout << "\nName is already taken. Enter a unique name." << endl;
                } else {
                    alreadyTaken = false;
                }
            }

			// Add the device, default to be turned off
            switch (choice) {
                case 1: devices.push_back(make_unique<Light>("Light", chosenName, false, 0, 0)); break;
                case 2: devices.push_back(make_unique<Thermostat>("Thermostat", chosenName, false, 11, 16)); break;
                case 3: devices.push_back(make_unique<TempSensor>("TempSensor", chosenName, false)); break;
                case 4: devices.push_back(make_unique<Speaker>("Speaker", chosenName, false, 0)); break;
                case 5: devices.push_back(make_unique<Radiator>("Radiator", chosenName, false, 0, 12, 22)); break;
                case 6: devices.push_back(make_unique<PlugSocket>("PlugSocket", chosenName, false, 12, 22, 0)); break;
                default: break;
            }
        } else {

			system("cls");
            cout << "\nInvalid input. Please try again.\n" << endl;
        }
    } while (true);

	system("cls");
}


void ModifyDevice(vector<unique_ptr<Device>>& devices) {
	
	cout << "\nWhat is the name of the device you would like to interact with?" << endl;
	
	string deviceName;
	cin >> deviceName;

	// Find device (case insensivite)
	bool found = false;
	for (const auto& device : devices) { 
		
		if (LowerCase(device->GetChosenName()) == LowerCase(deviceName)) { 
			found = true;
			device->DeviceManager(devices);
			break;
		}
	}
	
	// Error handling - If device isnt found produce error
	if (!found) {
		system("cls");
		cout << "\nError: Device with name '" << deviceName << "' not found. Returning...\n" << endl;
	}
}

void LoadDevices(vector<unique_ptr<Device>>& devices) {

	ifstream estabilishedDevices;
	estabilishedDevices.open(".\\EstabilishedDevices.txt");

	if (!estabilishedDevices.is_open()) {
		cout << "Cannot open file for reading";
		return;
	}

	unordered_map<string, int> map = {
		{"Light", 1},
		{"Speaker", 2},
		{"TempSensor", 3},
		{"Radiator", 4},
		{"PlugSocket", 5},
		{"Thermostat", 6}
	};

	int choice = -1;
	string line;

	cout << "Loading devices... \n" << endl;
	
	while (getline(estabilishedDevices, line)) {
			
		string deviceType, chosenName;
		bool state;
		int brightness, sleepTimer, volume, start, end;
		double startTime;
		float currentTemp;

		istringstream lineStream(line);
		lineStream >> deviceType;

		choice = map.find(deviceType)->second;

		switch (choice) { // Creating devices

			case 1:
				lineStream >> chosenName >> state >> brightness >> sleepTimer;
				devices.push_back(make_unique<Light>(deviceType, chosenName, state, brightness, sleepTimer));
				break;
			case 2:
				lineStream >> chosenName >> state >> volume;
				devices.push_back(make_unique<Speaker>(deviceType, chosenName, state, volume));
				break;
			case 3:
				lineStream >> chosenName >> state;
				devices.push_back(make_unique<TempSensor>(deviceType, chosenName, state));
				break;
			case 4:
				lineStream >> chosenName >> state >> currentTemp >> start >> end;
				devices.push_back(make_unique<Radiator>(deviceType, chosenName, state, currentTemp, start, end));
				break;
			case 5:
				lineStream >> chosenName >> state >> start >> end >> sleepTimer;
				devices.push_back(make_unique<PlugSocket>(deviceType, chosenName, state, start, end, sleepTimer));
				break;
			case 6:
				lineStream >> chosenName >> state >> start >> end;
				devices.push_back(make_unique<Thermostat>(deviceType, chosenName, state, start, end));
				break;	
		}
	}

	estabilishedDevices.close();
	cout << endl;
}

void StoreDevices(const vector<unique_ptr<Device>>& devices) {

	ofstream estabilishedDevices;
	estabilishedDevices.open(".\\EstabilishedDevices.txt");

	if (!estabilishedDevices.is_open()) {
		cout << "Cannot open file for writing" << endl;
		return;
	}
	
	unordered_map<string, int> map = {
		{"Light", 1},
		{"Speaker", 2},
		{"TempSensor", 3},
		{"Radiator", 4},
		{"PlugSocket", 5},
		{"Thermostat", 6}
	};
	int choice = -1;

	cout << "Saving devices... \n" << endl;

	// Iterate through the devices
	for (auto it = devices.begin(); it != devices.end(); ++it) {
		string device = (*it)->GetDeviceType(); 

		choice = map.find(device)->second;
		
		switch (choice) { // Write in file
			case 1:
			{
				Light* light = dynamic_cast<Light*>(it->get());
				estabilishedDevices << light->SaveDevice() << "\n";
				break;
			}
			case 2:
			{
				Speaker* speaker = dynamic_cast<Speaker*>(it->get());
				estabilishedDevices << speaker->SaveDevice() << "\n";
				break;
			}
			case 3:
			{
				TempSensor* tempSensor = dynamic_cast<TempSensor*>(it->get());
				estabilishedDevices << tempSensor->SaveDevice() << "\n";
				break;
			}
			case 4:
			{
				Radiator* radiator = dynamic_cast<Radiator*>(it->get());
				estabilishedDevices << radiator->SaveDevice() << "\n";
				break;
			}
			case 5:
			{
				PlugSocket* plugSocket = dynamic_cast<PlugSocket*>(it->get());
				estabilishedDevices << plugSocket->SaveDevice() << "\n";
				break;
			}
			case 6:
			{
				Thermostat* thermostat = dynamic_cast<Thermostat*>(it->get());
				estabilishedDevices << thermostat->SaveDevice() << "\n";
				break;
			}		
		}
	}
	estabilishedDevices.close();
	cout << "Devices saved successfully!" << endl;
}

void Display(string sortType, vector<unique_ptr<Device>>& devices) {
	
	system("cls");
	cout << "                   Displaying                    " << endl;
	cout << "=================================================" << endl;

	if (sortType == "Name") { // Sort by name

		sort(devices.begin(), devices.end(), [](const unique_ptr<Device>& a, const unique_ptr<Device>& b) {
			return a->GetChosenName() < b->GetChosenName();
		});
	}
	else if (sortType == "Device") {// Sort by device

		sort(devices.begin(), devices.end(), [](const unique_ptr<Device>& a, const unique_ptr<Device>& b) {

			if (a->GetDeviceType() == b->GetDeviceType()) a->GetChosenName() < b->GetChosenName();

			return a->GetDeviceType() < b->GetDeviceType();
		});
	}

	// Display
	for (vector<unique_ptr<Device>>::iterator it = devices.begin(); it != devices.end(); ++it) {

		(*it)->Display(false);
	}

	cout << "\n=================================================" << endl;
}

string LowerCase(string word) {

	// make each character lowercase then return it
	for (int i = 0; i < word.size(); i++) {
		word[i] = tolower(word[i]);
	}

	return word;
}

bool NameExists(string name, vector<unique_ptr<Device>>& devices) {

	name = LowerCase(name);

	// See if name already exists (case insesnitive)
	auto it = find_if(devices.begin(), devices.end(), [&](const unique_ptr<Device>& device) {

		return LowerCase(device->GetChosenName()) == name;
	});

	if (it != devices.end()) return true;
	else return false;
}


/*
	Citation

	Displaying current date and time: https://www.w3schools.com/cpp/cpp_date.asp
	Map: https://www.youtube.com/watch?v=fsZ8k8Yv3Uw
	Modifing map to take function pointers: https://www.reddit.com/r/cpp_questions/comments/19592y6/creating_pointers_to_functions_with_stdmap/
*/ 

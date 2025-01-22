#include "Device.h"

Device::Device(bool state, const string& deviceType, const string& chosenName) : state(state), deviceType(deviceType), chosenName(chosenName)  
{
}

void Device::Display(bool menu) { 
    
    QuickView(); 
    
    if (menu) QuickViewMenu();
    cout << endl; 
}

void Device::ChangeName(vector<unique_ptr<Device>>& devices) {

	string newName;
    bool nameChanged = false;

    cout << "What would you like to re-name this device too?" << endl;

    do {
        cin >> newName;

        // Error handling - if the name already exists repromt
        if (NameExists(newName, devices)) cout << "\nName already exists. Please enter a unique name:" << endl;
        else {
            chosenName = newName;
            nameChanged = true;
        }
    } while (!nameChanged);
}

bool Device::Delete(vector<unique_ptr<Device>>& devices) {
    string answer;
    cout << "\nYou are going to remove this device. Are you sure? (Y/N)" << endl;
    cin >> answer;

    if (answer == "Y" || answer == "y") {

        // Delete
        auto it = find_if(devices.begin(), devices.end(),
            [this](const unique_ptr<Device>& device) { return device.get() == this; });

        if (it != devices.end()) {
            devices.erase(it); // Erase the device from the vector
            return true;
        }
    }
    else if (answer == "N" || answer == "n") {
        
        cout << "Cancelled." << endl;
        return false;
    }
    else {
        cout << "Invalid input. Aborting...." << endl;
        return false;
    }
}

bool Device::NameExists(string& name, vector<unique_ptr<Device>>& devices) {

    name = Lowercase(name);
    
    // Check no name already exists
    auto it = find_if(devices.begin(), devices.end(), [&](const unique_ptr<Device>& device) {

        return Lowercase(device->GetChosenName()) == chosenName;
    });

    if (it != devices.end()) return true;
    else return false;  
}

string Device::Lowercase(string word) {

    for (int i = 0; i < word.size(); i++) {
        word[i] = tolower(word[i]);
    }

    return word;
}

void Device::DisplaySchedule(int start, int end) {

    cout << "Schedule: ";

    if (start > 12) cout << start - 12 << "pm ";
    else if (start == 12) cout << end << "pm ";
    else cout << start << "am ";

    cout << "- ";

    if (end > 12) cout << end - 12 << "pm " << endl;
    else if (end == 12) cout << end << "pm " << endl;
    else cout << end << "am " << endl;
}

void Device::CheckSchedule(int start, int end) {

    time_t timestamp = time(&timestamp);
    struct tm dateTime = *localtime(&timestamp); // Get current hour

    if ((dateTime.tm_hour >= start && dateTime.tm_hour <= end) && state == false) state = true;    // If state = false when should be true set true
    else if ((dateTime.tm_hour < start || dateTime.tm_hour > end) && state == true) state = false; // If state = true when should be false set to false
}

int Device::GetTimeInput() {

    string input;
    int timeValue = -1;
    bool validInput = false;

    while (!validInput) {

        cin >> input;
        input = Lowercase(input);

        size_t pos = input.find("am");

        if (pos != string::npos) {

            input.erase(pos, 2); // Remove "am"
            timeValue = stoi(input);

            if (timeValue >= 1 && timeValue <= 12) validInput = true;
            else cout << "Invalid input. Please enter a value between 1 and 12.\n"; // Error handling 
        }
        else if ((pos = input.find("pm")) != string::npos) {

            input.erase(pos, 2); // Remove "pm"
            timeValue = stoi(input);

            if (timeValue >= 1 && timeValue <= 12) {

                if (timeValue != 12)  timeValue += 12; // Convert to 24-hour clock

                validInput = true;
            }
            else cout << "Invalid input. Please enter a value between 1 and 12.\n"; // Error handling 
        }
        else cout << "Missing AM/PM specifier. Please include 'am' or 'pm'.\n"; // Error handling 
    }

    return timeValue;
}
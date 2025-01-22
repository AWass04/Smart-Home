#pragma once
#include "Device.h"
#include <ctime>

class Thermostat : public Device
{
	public:
		Thermostat(const string& deviceType, const string& chosenName, bool state, time_t start, time_t end);

		void QuickView() override;
		void QuickViewMenu() override;
		void FullView() override;

		void DeviceManager(vector<unique_ptr<Device>>& devices) override;
		void TurnOnHeatingBoost();
		void ChangeSchedule();

		string GetType() override;

		string SaveDevice() override;

	private:
		bool boostHeating = false;
		int start;
		int end;
};

inline string Thermostat::GetType() { return "Thermostat"; }

inline void Thermostat::TurnOnHeatingBoost() { boostHeating = true; }

inline void Thermostat::QuickView() { GetState() ? cout << GetChosenName() << " State: ON" : cout << GetChosenName() << " Sate: OFF"; }
inline void Thermostat::QuickViewMenu() { GetState() == true ? cout << "                    [Turn Off]" : cout << "                    [Turn On]"; }

inline string Thermostat::SaveDevice() { string save = "Thermostat " + GetChosenName() + " " + to_string(GetState()) + " " + to_string(start) + " " + to_string(end); return save; }


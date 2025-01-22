#pragma once
#include "Device.h"

class TempSensor : public Device
{
	public:
		TempSensor(const string& deviceType, const string& chosenName, bool state);

		void QuickView() override;
		void QuickViewMenu() override;
		void FullView() override;

		void DeviceManager(vector<unique_ptr<Device>>& devices) override;

		string GetType() override;

		string SaveDevice() override;

	private:
		int temp;
		int humidity;
};

inline string TempSensor::GetType() { return "TempSensor"; }

inline void TempSensor::QuickView() { cout << GetChosenName() << ": " << temp << "C / " << humidity << "% humidity"; }
inline void TempSensor::QuickViewMenu() {}

inline string TempSensor::SaveDevice() { string save = "TempSensor " + GetChosenName() + " " + to_string(GetState()) + " " + to_string(temp) + " " + to_string(humidity); return save; }



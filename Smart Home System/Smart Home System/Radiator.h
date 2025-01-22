#pragma once
#include "Device.h"

class Radiator : public Device
{
	public:
		Radiator(const string& deviceType, const string& chosenName, bool state, float currentTemp, int start, int end);

		void QuickView() override;
		void QuickViewMenu() override;
		void FullView() override;

		void DeviceManager(vector<unique_ptr<Device>>& devices) override;

		void ChangeSchedule();

		string GetType() override;

		string SaveDevice() override;

	private:
		float currentTemp;
		int start;
		int end;
};

inline string Radiator::GetType() { return "Radiator"; }

inline void Radiator::QuickView() { GetState() ? cout << GetChosenName() << ": " << currentTemp << "C" : cout << GetChosenName() << ": OFF"; }
inline void Radiator::QuickViewMenu() { GetState() == true ? cout << "                          [Turn Off]" : cout << "                          [Turn On]";}

inline string Radiator::SaveDevice() { string save = "Radiator " + GetChosenName() + " " + to_string(GetState()) + " " + to_string(currentTemp) + " " + to_string(start) + " " + to_string(end); return save; }


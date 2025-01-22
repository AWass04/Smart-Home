#pragma once
#include "Device.h"

class PlugSocket : public Device
{
	public:
		PlugSocket(const string& deviceType, const string& chosenName, bool state, int start, int end, int sleepTimer);

		void QuickView() override;
		void QuickViewMenu() override;
		void FullView() override;

		void DeviceManager(vector<unique_ptr<Device>>& devices) override;

		void ChangeSchedule();
		void AdjustSleepTimer();
		void CurrentEnergyUsage();

		string GetType() override;

		string SaveDevice() override;

	protected:

	private:
		int start;
		int end;
		int sleepTimer;
		const double energyCost = 0.74;
};

inline string PlugSocket::GetType() { return "PlugSocket"; }

inline void PlugSocket::QuickView() { GetState() ? cout << GetChosenName() << ": ON" : cout << GetChosenName() << ": OFF"; }
inline void PlugSocket::QuickViewMenu() { GetState() == true ? cout << "                          [Turn Off]" : cout << "                         [Turn On]";}

inline string PlugSocket::SaveDevice() { string save = "PlugSocket " + GetChosenName() + " " + to_string(GetState()) + " " + to_string(start) + " " + to_string(end) + " " + to_string(sleepTimer); return save; }
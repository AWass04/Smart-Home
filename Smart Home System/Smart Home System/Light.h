#pragma once
#include "Device.h"


class Light : public Device
{
	public:
		Light(const string& deviceType, const string& chosenName, bool state, int brightness, int sleepTimer);

		void QuickView() override;
		void QuickViewMenu() override;
		void FullView() override;

		void DeviceManager(vector<unique_ptr<Device>>& devices) override;
		string SaveDevice() override;

		void AdjustBrightness();
		void AdjustBrightness(int newBrightness);
		void AdjustSleepTimer();
		void AdjustSleepTimer(int newTimer);

		int ErrorCheck(int minimum, int maximum, const string& errorMessage);

		string GetType() override;
		int GetBrightness() const;
		int GetSleepTimer() const;

	private:
		int brightness;   
		int sleepTimer; 
};

inline string Light::GetType() { return "Light"; }
inline int Light::GetBrightness() const { return brightness; }
inline int Light::GetSleepTimer() const { return sleepTimer; }

inline void Light::QuickView() { GetState() == true ? cout << GetChosenName() << ": " << brightness << "% brightness" : cout << GetChosenName() << ": OFF"; }
inline void Light::QuickViewMenu() { GetState() == true ? cout << "             [Turn Off]" : cout << "                         [Turn On]"; }

inline void Light::AdjustSleepTimer(int newTimer) { sleepTimer = newTimer; }
inline void Light::AdjustBrightness(int newBrightness) { brightness = newBrightness; }

inline string Light::SaveDevice() { string save = "Light " + GetChosenName() + " " + to_string(GetState()) + " " + to_string(brightness) + " " + to_string(sleepTimer); return save; }

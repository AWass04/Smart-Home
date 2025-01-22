#pragma once
#include "Device.h"

class Speaker : public Device
{
	public:
		Speaker(const string& deviceType, const string& chosenName, bool state, int volume);

		void QuickView() override;
		void QuickViewMenu() override;
		void FullView() override;

		void DeviceManager(vector<unique_ptr<Device>>& devices) override;
		
		void ChangeVolume();

		string GetType() override;

		string SaveDevice() override;

	private:
		int volume;
};

inline string Speaker::GetType() { return "Speaker"; }

inline void Speaker::QuickView() {GetState() ? cout << GetChosenName() << ": " << volume << "% volume" : cout << GetChosenName() << ": OFF"; }
inline void Speaker::QuickViewMenu() { GetState() == true ? cout << "                       [Turn Off]" : cout << "                              [Turn On]";}

inline string Speaker::SaveDevice() { string save = "Speaker " + GetChosenName() + " " + to_string(GetState()) + " " + to_string(volume); return save; } 



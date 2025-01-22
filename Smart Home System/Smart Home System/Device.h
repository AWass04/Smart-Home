#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Device
{
	public:
		Device(bool state,const string& deviceType, const string& chosenName);

		string GetChosenName() const;
		string GetDeviceType() const;
		bool GetState() const;

		void TurnOnTurnOff();

		virtual void DeviceManager(vector<unique_ptr<Device>>& devices) = 0;
		
		void Display(bool menu);

	protected:
		virtual string GetType() = 0;
		virtual void QuickView() = 0;
		virtual void QuickViewMenu() = 0;
		virtual void FullView() = 0;
		virtual string SaveDevice() = 0;

		void ChangeName(vector<unique_ptr<Device>>& devices);
		bool NameExists(string& name, vector<unique_ptr<Device>>& devices);

		bool Delete(vector<unique_ptr<Device>>& devices);

		string Lowercase(string word);

		void DisplaySchedule(int start, int end);
		void CheckSchedule(int start, int end);
		int GetTimeInput();

	private:
		bool state;
		string deviceType;
		string chosenName;

};

inline string Device::GetChosenName() const { return chosenName; }
inline bool Device::GetState() const { return state; }
inline string Device::GetDeviceType() const { return deviceType; }

inline void Device::TurnOnTurnOff() { state = !state; }

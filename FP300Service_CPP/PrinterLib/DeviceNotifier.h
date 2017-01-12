#pragma once

#ifndef WIN32
#include <unistd.h>
#include <libudev.h>  // sudo apt-get install libudev-dev
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>


using namespace std;
typedef unsigned char byte;

class DevInfo;

class IDevice
{
public:
	virtual void DeviceAdded(DevInfo& dev) = 0;
	virtual void DeviceRemoved(const string& DevNode) = 0;
};

class DeviceNotifier
{
	IDevice &pid;
	static bool _running;
public:
	DeviceNotifier(IDevice &id);
	~DeviceNotifier(void);
	void ThreadFunction() ;
	void Start();
	void Stop();
};

class DevInfo
{
public:
	string vendor ;
	string product ;
	string description ;
	string manufacturer;
	string serial;
	string Devtype;
	string DevNode;
	string Subsystem;

	DevInfo(struct udev_device *dev);
	static vector<DevInfo> GetDevices();
	string Print();

};

string RunCommand(const char* cmd);
void RunCommand(const char* cmd, vector<string> & output);

#endif
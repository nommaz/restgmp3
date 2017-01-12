#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "HSMessageContext.h"
#include "GMPMessage.h"
#include "MessageConstants.h"
#include "MessageBuilder.h"
using namespace std;

namespace ExDevice
{
	class HSState
	{
		static map<string, int> desktopVerTable;
		static map<double, int> vxVerTable;
	
	public :
		virtual GMPMessage* GetMessage() = 0;
		virtual int Process(vector<byte> &buffer) = 0;
		virtual HSState* NextState() = 0;
		virtual const char *StateName() = 0;

		static const int MAX_BUFFER_LEN = 2048;
		static DeviceInfo DevInfo;
		static int VERSION;
		
	public :		
		HSState(void);
		virtual ~HSState(void);

		void AddExDevInfo(GMPMessage &msg);
		void AddEcrDevInfo(GMPMessage &msg);
		static void SetVersion(DeviceInfo devInfo);
	};

	class Start : public HSState
	{

	public:
		Start(DeviceInfo devInfo);
		virtual int Process(vector<byte> &buffer);
		virtual HSState* NextState();
		virtual GMPMessage* GetMessage();
		virtual const char *StateName();
	};

	class KeyExchange : public HSState
	{

	public :
		static const string PRM_GMP3_PRF_LABEL;
		static const string COMPUTE_KEYS_LABEL;
		static const string CER_KAMU_SM_PRODUCER;

	public :
		virtual int Process(vector<byte> &buffer);
		virtual HSState* NextState();
		virtual GMPMessage* GetMessage();
		virtual const char *StateName();
	};


	class Close : public HSState
	{

	public :
		virtual int Process(vector<byte>& buffer);
		virtual HSState* NextState();
		virtual GMPMessage* GetMessage();
		virtual const char *StateName();

	};
}

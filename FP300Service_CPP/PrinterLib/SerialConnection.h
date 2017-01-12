#pragma once

#include "Connection.h"
#include "Logger.h"

#ifdef WIN32

class SerialConnection : public Connection
{
private:
	string		portName;
	int			baudRate;
	HANDLE		hFile;		
	OVERLAPPED  osRead;
	OVERLAPPED  osWrite;
	HANDLE		threadRecv;


public:
	// Logger serialLogger;
	
	SerialConnection(string portName, int baudRate);
	~SerialConnection();

	void SerialConnection::Set( string portName, int baudRate );
	bool Open();
	void Close();
	void RecvProc();
	bool Write(BYTE* buffer, DWORD writeBytes, DWORD& writtenBytes); 
};

#else

class SerialConnection : public Connection
{
private:
	string		portName;
	int			baudRate;

    int			tty_fd;
	pthread_t	threadRecv;

public:
	// Logger serialLogger;
	
	SerialConnection( string portName, int baudRate );
	~SerialConnection();

	void Set( string portName, int baudRate );
	bool Open();
	void Close();
	void RecvProc();
	bool Write(unsigned char* buffer, unsigned long writeBytes, unsigned long& writtenBytes); 
};
#endif


#pragma once


#ifdef WIN32
#include <windows.h>

#if defined(HUGINAPI_DLL_BUILD) // inside DLL
#   define HUGINAPI   __declspec(dllexport)
#elif defined __MINGW32__
#   define HUGINAPI
#else // outside DLL
#   define HUGINAPI   __declspec(dllimport)
#endif  // _WINDLL

#else

#define HUGINAPI 
#include <unistd.h>
typedef unsigned char byte;

#endif

using namespace std;

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

namespace Hugin
{
namespace GMPCommon
{
    class Logger
    {
	public:
		enum LogLevel
		{
			FATAL = 1,
			_ERROR = 2,
			WARN = 3,
			INFO = 4,
			Debug = 5,
			HIDE_BUG = 6
		};
	private:
		static bool fInit;
		static string logFileName;
		static bool isLoggingStart;
		static LogLevel Level;
		static string LogFileDirectory;
		static int logDay;

		static bool Initialize();
		static void CreateLogFile();

	public:		
		static void AddLog(string log);
		static void DebugLine(string strClass, string strFunc, int line);
		static void Enter(string strClass, string strFunc);
        static void Exit(string strClass, string strFunc);
        static void Log(LogLevel level, string log);
        static void Log(LogLevel level, const vector<byte> &buffer);
        static void Log(LogLevel level, const vector<byte> &buffer, string note);  
		static void Log(LogLevel level, const char *fmt, ...);
        static void Log(exception *ex);
		static void SetLogLevel(LogLevel level);
		static void SetDebugFolder( string folderPath );
	};
}

}

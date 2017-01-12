#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <stdlib.h>
typedef unsigned char byte;
typedef char *LPCWSTR;
int WideCharToMultiByte(int CodePage,int dwFlags,char*  lpWideCharStr,size_t      cchWideChar,char* lpMultiByteStr,size_t      cbMultiByte,char*   lpDefaultChar,int*  lpUsedDefaultChar);
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <stdarg.h>

using namespace std;

#ifdef WIN32
#define _GLIBCXX_USE_NOEXCEPT
#endif

class Exception : public exception
{
	string message;
public:
	Exception(const char *fmt, ...)
	{
		char buffer[1024] = {0};
		va_list arg;
		va_start(arg, fmt);
		vsnprintf(buffer, sizeof (buffer) - 1, fmt, arg);
		va_end(arg);

		this->message = buffer;
	}
	//Exception(const char *message)
	//{
	//	this->message = message;
	//}
	Exception(const string& message)
	{
		this->message = message;
	}
	~Exception() _GLIBCXX_USE_NOEXCEPT
	{
	}
	const char *what() const _GLIBCXX_USE_NOEXCEPT
	{
		return message.c_str();
	}
};

class Buffer : public vector<byte>
{
public:
	static void BlockCopy(vector<byte>& src, int srcOffset, vector<byte>& dst, int dstOffset, int count);
};

template <class T>
class List : public vector<T>
{
public:
	void AddRange(const vector<T>& collection)
	{
		for (int i = 0; i < collection.size(); ++i)
		{
			vector<T>::push_back(collection[i]);
		}
	}
	void Clear()
	{
		vector<T>::clear();
	}
	vector<T> ToArray()
	{
		return *this;
	}
	void InsertRange(int index, const vector<T>& collection )
	{
		for (int i = 0; i < collection.size(); ++i)
		{
			vector<T>::insert(this->begin() + index + i, collection[i]);
		}
	}
	void Add(const T& t)
	{
		vector<T>::push_back(t);
	}
};


class _Math
{
public:
	static double Round(double d);
	static double Round(double d, int digits);
	static int Min(int t1, int t2);
};

extern _Math Math;


vector<unsigned char> ToVector(string s);
vector<unsigned char> ToVector(const void *buffer, int size);
std::string ToString( vector<unsigned char> v );
bool GetMACaddress(string &mac);
string HexDump(const vector<byte> &buffer, int);
string HexDump(const void *buffer, int size);
string ToString(const wstring &str);

#pragma once

#include <string>
#include <vector>
#include "MessageBuilder.h"

using namespace std;

enum SFResponseLabel
{
    ERROR_CODE,
    STATUS1,
    PARAM,
    NULL2
};

class SFResponseObject
{
public:
	int errorCode;
    int statusCode;
    vector<string> paramList;

	SFResponseObject();
};

class SFResponse
{
private:
	static char SPEC_CHAR;
	SFResponseObject respObj;

public:
	SFResponse(void);

	~SFResponse(void);

    void AddParam(string value);
	void AddErrorCode(int value );
	void AddStatus(int value );

	string GetString();

	void AddNull(int count);
	static SFResponseObject GetObjectByString(string str);
};


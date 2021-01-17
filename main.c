#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define USERID "DE455gfdd"
#define INFO_BUFFER_SIZE 100

void printError(TCHAR* msg);


void main()
{
	/*
	* HEADER
	*/
	const char* headercom = "\n************************************************************";
	const char* copyright = "\n Instrument Daemon 1.0.0 - Copyright\xa9 2020 Signal Registry";
	printf(headercom);
	printf(copyright);
	printf(headercom);

	/*
	* SERVER REGISTER
	*/
	// computer and user name
	TCHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	TCHAR computerName[INFO_BUFFER_SIZE];
	TCHAR userName[INFO_BUFFER_SIZE];

	// computer name 
	bufCharCount = INFO_BUFFER_SIZE;
	if (!GetComputerName(infoBuf, &bufCharCount))
		printError(TEXT("GetComputerName"));
	strcpy_s(computerName, sizeof userName, infoBuf);

	// user name. 
	bufCharCount = INFO_BUFFER_SIZE;
	if (!GetUserName(infoBuf, &bufCharCount))
		printError(TEXT("GetUserName"));
	strcpy_s(userName, sizeof userName, infoBuf);

	// register
	printf("\n-> Connecting Signal Registry\xa9 with user id %s ...", USERID);

	
}

void printError(TCHAR* msg)
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n\t%s failed with error %d (%s)"), msg, eNum, sysMsg);
}
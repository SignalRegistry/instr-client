#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include <curl/curl.h>

#define INFO_BUFFER_SIZE 100
void printError(TCHAR* msg);
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp);
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
	printf("\n-> Registering client with computer and user name ...");
	_tprintf(TEXT("\n    - Computer name: %s"), computerName);
	_tprintf(TEXT("\n    - User name    : %s"), userName);
	
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://app.instr.signalregistry.net");
		/* example.com is redirected, so we tell libcurl to follow redirection */
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	
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

size_t write_data(char* buffer, size_t size, size_t nmemb, void* userp)
{
	printf("\nResponse: %s", buffer);
	return size * nmemb;
}
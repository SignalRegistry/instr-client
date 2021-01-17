#include <stdio.h>

#include <curl/curl.h>
#include "parson.h"



/*
* DECLARATIONS
*/
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

int main()
{
  /*
	* HEADER
	*/
  const char *headercom = "\n************************************************************";
  const char *copyright = "\n Instrument Daemon 1.0.0 - Copyright\xa9 2020 Signal Registry";
  printf(headercom);
  printf(copyright);
  printf(headercom);

  /*
	* SERVER REGISTER
	*/
  JSON_Value *root_value;
  JSON_Object *commit;
  root_value = json_parse_file(".\\config.json");
  if (json_value_get_type(root_value) != JSONObject)
  {
    printf("Error: Valid configuration file not found.");
    return 0;
  }
  commit = json_value_get_object(root_value);
  // printf(json_object_get_string(commit, "userid"));
  printf("\n-> Connecting Signal Registry\xa9 server with user id '%s' ...", json_object_get_string(commit, "userid"));

  CURL *curl;
  CURLcode res;
  const char *address_fmt = "https://app.instr.signalregistry.net/daemon?userid=%s";
  int len = snprintf(NULL, 0, address_fmt, USERID);
  char *address = (char *)malloc(len + 1);
  snprintf(address, len + 1, address_fmt, USERID);

  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, address);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
    free(address);
  }
}

size_t write_data(char *buffer, size_t size, size_t nmemb, void *userp)
{
  printf("\nResponse: %s", buffer);
  return size * nmemb;
}

#include "../main.h"
#include <curl/curl.h>

using namespace std;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, string *output)
{
  size_t total_size = size * nmemb;
  output->append(static_cast<char *>(contents), total_size);
  return total_size;
}

//i'll be honest, 
string Get_Public_ipv6(){

  string ipv6_response;
  CURL *curl = curl_easy_init();

  if (curl){
    curl_easy_setopt(curl, CURLOPT_URL, "https://ipv6.icanhazip.com/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ipv6_response);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
      cerr << "Curl error: " << curl_easy_strerror(res) << endl;
    }

    curl_easy_cleanup(curl);
  }
  return ipv6_response;
}
#include <curl/curl.h>
#include <iostream>
#include <string>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output);
std::string Get_Public_ipv4();

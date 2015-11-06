#include <iostream>
#include <string>
#include "curl/curl.h"

using namespace std;

string ipPrefix = "\"ip\": \"";
string ipSuffix = "\"";
string ipInfo;
    

size_t getData(char* rData, size_t size, size_t memN, void* c)
{
    for (int i = 0; i < size*memN; i++)
    {
        ipInfo.push_back(rData[i]);
    }
    return size*memN;
}

int main () {

    size_t ipPrefixLoc;
    size_t ipSuffixLoc;

    CURL* curl;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    
    curl_easy_setopt(curl, CURLOPT_URL, "http://ipinfo.io/json");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &getData);
    curl_easy_setopt(curl, CURLOPT_HEADER, 0);
    curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
    curl_easy_setopt(curl, CURLOPT_FILETIME, 1 ); 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "wanIP v0.1 (www.AyoobAli.com)");
    curl_easy_perform(curl);

    ipPrefixLoc = ipInfo.find(ipPrefix);
    if (ipPrefixLoc == string::npos){
      cout << "IP not found." << endl;
      return 1;
    }
    ipPrefixLoc = ipPrefixLoc+ipPrefix.length();

    ipSuffixLoc = ipInfo.find(ipSuffix, ipPrefixLoc);
    if (ipSuffixLoc == string::npos){
      cout << "IP not found." << endl;
      return 1;
    }

    cout << ipInfo.substr(ipPrefixLoc,ipSuffixLoc-ipPrefixLoc) << endl;

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return 0;
}

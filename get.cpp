#include <iostream>
#include <curl/curl.h>
#include <cpl_conv.h>
#include <windows.h>
#include "user.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "ru");
    
    //string outputFile = "output.xml"; // По желанию, можно оставить пустую строку

    server myServer("geologyscience", "WFS", "1.0.0","getCapabilities");
    string url = " https://service.geologyscience.ru/geoserver/sgm/ows";
    user user("Kirill");

    user.GetCapabilities(url, myServer, "");

    return 0;


}

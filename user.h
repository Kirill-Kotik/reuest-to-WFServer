#include <iostream>
#include <string>
#include <curl/curl.h>
#include "server.h"
#include <fstream>

using namespace std;

class user {

private:
    string username;
    bool is_logged_in;
    string path;

public:
    user() = default;

    user(const string& username): username(username), is_logged_in(false) {}
    
    void setName(const string& newName) {
        username = newName;
    }
    string getName() const {
        return username;
    }
    void login() {
        is_logged_in = true;
        cout << username << " has logged in." << endl;
    }

    void logout() {
        is_logged_in = false;
        cout << username << " has logged out." << endl;
    }

    void displayInfo() {
        cout << "Username: " << username << "\nLogged In: " << (is_logged_in ? "Yes" : "No") << endl;
    }
    /* size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* user_data) {
        size_t total_size = size * nmemb;
        string* response = static_cast<string*>(user_data);
        response->append(static_cast<char*>(contents), total_size);
        return total_size;
    }*/
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* user_data) {
        size_t total_size = size * nmemb;
        FILE* file = static_cast<FILE*>(user_data);
        fwrite(contents, 1, total_size, file);
        return total_size;
    }
    void GetCapabilities(const string& url, server  nameServer, const string& outputFile = "") {
        //string requestUrl = url + "?request=GetCapabilities&service=WFS";
        string requestUrl = url + nameServer.getServInfo();
        CURL* curl = curl_easy_init();

        if (curl) {
            string response;
            curl_easy_setopt(curl, CURLOPT_URL, requestUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

            CURLcode res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                std::cerr << "Failed to perform GetCapabilities request : " << curl_easy_strerror(res) << std::endl;
            }
            else {
                std::cout << "GetCapabilities response:\n" << response << std::endl;

                if (!outputFile.empty()) {
                    std::ofstream file(outputFile);
                    if (file.is_open()) {
                        file << response;
                        std::cout << "Response saved to " << outputFile << std::endl;
                    }
                    else {
                        std::cerr << "Failed to open output file for saving." << std::endl;
                    }
                }
            }

            curl_easy_cleanup(curl);
        }
    }


    
    void GetFeature(const string url) {
        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                cerr << "Failed to perform GET request: " << curl_easy_strerror(res) << endl;
            curl_easy_cleanup(curl);
        }
    }
    void performGetRequest(const string& url, const std::string& filename) {
        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            // Set callback to save response to a file
            std::ofstream outfile(filename);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outfile);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                std::cerr << "Failed to perform GET request: " << curl_easy_strerror(res) << std::endl;

            curl_easy_cleanup(curl);
            outfile.close();
        }
    }
    void saveRequest(string path,string& content) {
        ofstream outputFile(path);
        if (outputFile.is_open()) {
            outputFile << content;
            outputFile.close();
            std::cout << "Content written to file." << std::endl;
        }
        else {
            std::cout << "Unable to open file for writing." << std::endl;
        }
    }
    void writeToPath(const std::string& content) {
        ofstream outputFile(path);
        if (outputFile.is_open()) {
            outputFile << content;
            outputFile.close();
            std::cout << "Content written to file." << std::endl;
        }
        else {
            std::cout << "Unable to open file for writing." << std::endl;
        }
    }
    
};





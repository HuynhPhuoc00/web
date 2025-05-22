#include <iostream>
#include <curl/curl.h>
#include <string>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

size_t write_callback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    std::string device = "BULB_01";
    std::string url = "http://localhost:8080/device/" + device;

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "ERROR: Can't initialize CURL.\n";
        return 1;
    }

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "CURL FAILED: " << curl_easy_strerror(res) << "\n";
        return 1;
    }

    try {
        json j = json::parse(response);
        std::string state = j.at(device);
        std::cout << "Device: " << device << " | State: " << state << "\n";

        if (state == "ON") {
            std::cout << "==> ON!" << std::endl;
        } else {
            std::cout << "==> OFF!" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in analysis JSON: " << e.what() << std::endl;
    }

    curl_easy_cleanup(curl);
    return 0;
}

#include <iostream>
#include <curl/curl.h>
#include <string>
#include <thread>
#include <chrono>
#include "nlohmann/json.hpp"

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
        std::cerr << "Error: unable to initialize CURL.\n";
        return 1;
    }

    std::string old_state = ""; // previous device state

    while (true) {
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "CURL failed: " << curl_easy_strerror(res) << "\n";
        } else {
            try {
                json j = json::parse(response);
                std::string new_state = j.at(device);

                // Only process if the state changed
                if (new_state != old_state) {
                    std::cout << "Device: " << device << " | New state: " << new_state << "\n";

                    if (new_state == "ON") {
                        std::cout << "==> TURN ON device!" << std::endl;
                    } else {
                        std::cout << "==> TURN OFF device!" << std::endl;
                    }

                    old_state = new_state;  // update old state
                }
                // If no change, do nothing

            } catch (const std::exception& e) {
                std::cerr << "JSON parsing error: " << e.what() << std::endl;
            }
        }

        //std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    curl_easy_cleanup(curl);
    return 0;
}

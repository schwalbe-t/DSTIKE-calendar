
#include "wifi.hpp"
#include <Arduino.h>

namespace wifi {

    // const Network NETWORKS[] = {
    //     Network("Guests", "aS4!Sfv@"),
    //     Network("Google Pixel 4", "3%aSc@35!as"),
    //     Network("Potspot", "AS*#@HSA4X")
    // };
    const Network NETWORKS[] = {

    };
    const int NETWORK_COUNT = sizeof(NETWORKS) / sizeof(Network);


    bool is_connected() {
        return WiFi.status() == WL_CONNECTED;
    }

    void disconnect() {
        WiFi.disconnect();
        delay(1000);
    }

    const int CONNECT_TIMEOUT = 10000;
    const int CONNECT_LOOP_DELTA = 20;

    bool connect_to(const Network& network, int* channel, uint8_t* bssid) {
        if(is_connected()) { disconnect(); }
        if(channel == nullptr || bssid == nullptr) {
            WiFi.begin(network.ssid, network.password);
        } else {
            WiFi.begin(network.ssid, network.password, *channel, bssid);
        }
        for(int i = 0; i < CONNECT_TIMEOUT; i += CONNECT_LOOP_DELTA) {
            switch(WiFi.status()) {
                case WL_NO_SSID_AVAIL:
                case WL_CONNECT_FAILED:
                    return false;
                case WL_CONNECTED:
                    return true;
            }
            delay(CONNECT_LOOP_DELTA);
        }
        return false;
    }

    bool connect_to_any(const Network* networks, int network_c) {
        int found_c = WiFi.scanNetworks();
        for(int found_i = 0; found_i < found_c; found_i += 1) {
            String ssid = WiFi.SSID(found_i);
            for(int known_i = 0; known_i < network_c; known_i += 1) {
                if(ssid != networks[known_i].ssid) { continue; }
                int channel = WiFi.channel(found_i);
                uint8_t* bssid = WiFi.BSSID(found_i);
                if(connect_to(networks[known_i], &channel, bssid)) {
                    return true;
                }
            }
        }
        return false;
    }

}
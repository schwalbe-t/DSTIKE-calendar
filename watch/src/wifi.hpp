
#pragma once

#include <ESP8266WiFi.h>

namespace wifi {
    
    struct Network {
        String ssid;
        const char* password;

        Network(const char* ssid, const char* password):
            ssid(ssid), password(password) {}
    };

    extern const Network NETWORKS[];
    extern const int NETWORK_COUNT;


    bool is_connected();
    void disconnect();
    bool connect_to(
        const Network& network, 
        int* channel = nullptr, uint8_t* bssid = nullptr
    );
    bool connect_to_any(const Network* networks, int network_c);

}

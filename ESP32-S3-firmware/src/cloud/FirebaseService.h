#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "SensorData.h"

class FirebaseService {
public:
    void begin();
    bool upload(const SensorData& data);

private:
    FirebaseData fbdo;
    FirebaseAuth auth;
    FirebaseConfig config;

    bool ready = false;

    void connectWiFi();
};
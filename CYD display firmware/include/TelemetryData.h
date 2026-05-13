#pragma once

#include <Arduino.h>

struct TelemetryData {
    float indoorTemperature = 0.0;
    float indoorHumidity = 0.0;

    float outdoorTemperature = 0.0;
    float outdoorHumidity = 0.0;

    float lightVoltage = 0.0;
    float lightRaw = 0.0;

    double latitude = 0.0;
    double longitude = 0.0;

    int satellites = 0;
    bool gpsValid = false;

    bool wifiConnected = false;
    bool firebaseReady = false;

    String date = "--";
    String time = "--";

    bool dataReceived = false;
    unsigned long lastUpdate = 0;
};
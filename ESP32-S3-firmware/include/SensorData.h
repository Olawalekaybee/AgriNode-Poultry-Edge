#pragma once

#include <Arduino.h>

struct SensorData
{
    float indoorTemperature = 0.0;
    float indoorHumidity = 0.0;

    float outdoorTemperature = 0.0;
    float outdoorHumidity = 0.0;

    float lightIntensityRaw = 0.0;
    float lightVoltage = 0.0;

    double latitude = 0.0;
    double longitude = 0.0;

    int gpsSatellites = 0;
    bool gpsValid = false;

    String date = "";
    String time = "";

    bool wifiConnected = false;
    bool firebaseReady = false;

    unsigned long timestamp = 0;
};

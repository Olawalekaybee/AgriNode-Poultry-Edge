#pragma once

#include <Arduino.h>
#include <TinyGPS++.h>
#include "SensorData.h"

class GPSSensor {
public:
    void begin();
    void update();
    bool read(SensorData& data);

private:
    TinyGPSPlus gps;
    HardwareSerial gpsSerial = HardwareSerial(1);

    String formatDate();
    String formatTime();
};
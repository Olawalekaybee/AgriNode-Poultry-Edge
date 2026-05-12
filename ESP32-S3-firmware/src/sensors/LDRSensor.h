#pragma once

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "SensorData.h"

class LDRSensor {
public:
    void begin();
    bool read(SensorData& data);

private:
    Adafruit_ADS1115 ads;
    bool available = false;
};
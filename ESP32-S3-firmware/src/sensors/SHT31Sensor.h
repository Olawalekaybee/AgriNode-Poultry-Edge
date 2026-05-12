#pragma once

#include <Arduino.h>
#include <Adafruit_SHT31.h>
#include "SensorData.h"

class SHT31Sensor {
public:
    void begin();
    bool read(SensorData& data);

private:
    Adafruit_SHT31 sht31;
    bool available = false;
};
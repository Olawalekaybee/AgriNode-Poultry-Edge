#pragma once

#include <Arduino.h>
#include <DHT.h>
#include "SensorData.h"

class DHT22Sensor {
public:
    DHT22Sensor();

    void begin();
    bool read(SensorData& data);

private:
    DHT dht;
};
#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "SensorData.h"

class DisplayBridge {
public:
    void begin();
    bool send(const SensorData& data);

private:
    String buildPayload(const SensorData& data);
};
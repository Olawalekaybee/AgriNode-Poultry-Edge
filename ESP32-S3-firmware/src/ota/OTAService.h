#pragma once

#include <Arduino.h>

class OTAService {
public:
    void begin();
    void update();

private:
    bool initialized = false;
};
#pragma once

#include <Arduino.h>
#include "TelemetryData.h"
#include "communication/I2CReceiver.h"
#include "display/DashboardDisplay.h"

class CYDDisplayApp {
public:
    void begin();
    void update();

private:
    TelemetryData data;
    I2CReceiver receiver;
    DashboardDisplay display;

    unsigned long lastRender = 0;
    static constexpr unsigned long RENDER_INTERVAL_MS = 1000;
};
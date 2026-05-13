#pragma once

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "TelemetryData.h"

class DashboardDisplay {
public:
    void begin();
    void render(const TelemetryData& data);

private:
    TFT_eSPI tft = TFT_eSPI();

    void drawHeader(const TelemetryData& data);
    void drawCards(const TelemetryData& data);
    void drawFooter(const TelemetryData& data);
    void drawCard(int x, int y, int w, int h, const String& title, const String& value, const String& unit);
};
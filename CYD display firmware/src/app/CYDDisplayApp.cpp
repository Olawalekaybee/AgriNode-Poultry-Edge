#include "CYDDisplayApp.h"

void CYDDisplayApp::begin() {
    Serial.println("Starting AgriNode CYD Display Node...");

    display.begin();
    receiver.begin();

    display.render(data);

    Serial.println("CYD Display Node initialized successfully.");
}

void CYDDisplayApp::update() {
    if (receiver.hasNewData()) {
        if (receiver.readLatest(data)) {
            Serial.println("[CYD] New telemetry packet received");
        }
    }

    unsigned long now = millis();

    if (now - lastRender >= RENDER_INTERVAL_MS) {
        lastRender = now;
        display.render(data);
    }
}
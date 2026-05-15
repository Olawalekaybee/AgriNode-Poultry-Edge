#include <Arduino.h>
#include "app/PoultryMonitorApp.h"

PoultryMonitorApp app;

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.println();
    Serial.println("================================");
    Serial.println("AgriNode Poultry Edge Booting...");
    Serial.println("ESP32-S3 Firmware");
    Serial.println("================================");

    app.begin();

    Serial.println("[MAIN] Application started successfully.");
}

void loop()
{
    app.update();

    static unsigned long lastHeartbeat = 0;
    unsigned long now = millis();

    if (now - lastHeartbeat >= 5000)
    {
        lastHeartbeat = now;
        Serial.println("[MAIN] System running...");
    }
}
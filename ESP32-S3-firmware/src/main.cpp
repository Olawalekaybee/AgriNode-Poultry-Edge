#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("ESP32-S3 SERIAL TEST OK");
}

void loop() {
    Serial.println("heartbeat");
    delay(1000);
}
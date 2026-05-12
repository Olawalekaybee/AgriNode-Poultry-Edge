#include <Arduino.h>
#include "app/PoultryMonitorApp.h"

PoultryMonitorApp app;

void setup() {
    Serial.begin(115200);
    delay(1000);

    app.begin();
}

void loop() {
    app.update();
}
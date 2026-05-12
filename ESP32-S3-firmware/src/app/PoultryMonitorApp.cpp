#include "PoultryMonitorApp.h"
#include "AppConfig.h"

void PoultryMonitorApp::begin() {
    Serial.println("Starting AgriNode Poultry Edge...");

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY);

    Serial.println("[I2C] Bus initialized");

    dht22.begin();
    sht31.begin();
    ldr.begin();
    gps.begin();
    display.begin();
    firebase.begin();

    Serial.println("System initialized successfully.");
}

void PoultryMonitorApp::update() {
    gps.update();

    unsigned long now = millis();

    if (now - lastSensorRead >= SENSOR_READ_INTERVAL_MS) {
        lastSensorRead = now;
        readSensors();
    }

    if (now - lastDisplayUpdate >= DISPLAY_REFRESH_INTERVAL_MS) {
        lastDisplayUpdate = now;
        display.send(data);
    }

    if (now - lastFirebaseUpload >= FIREBASE_UPLOAD_INTERVAL_MS) {
        lastFirebaseUpload = now;
        firebase.upload(data);
    }
}

void PoultryMonitorApp::readSensors() {
    dht22.read(data);
    sht31.read(data);
    ldr.read(data);
    gps.read(data);

    data.timestamp = millis();
}
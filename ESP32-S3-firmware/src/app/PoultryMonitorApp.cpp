#include "PoultryMonitorApp.h"
#include "AppConfig.h"

void PoultryMonitorApp::begin() {
    Serial.println("[APP] Starting AgriNode Poultry Edge...");

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY);
    Serial.println("[APP] I2C initialized");

    Serial.println("[APP] Starting DHT22...");
    dht22.begin();

    Serial.println("[APP] Starting SHT31...");
    sht31.begin();

    Serial.println("[APP] Starting ADS1115/LDR...");
    ldr.begin();

    Serial.println("[APP] Starting GPS...");
    gps.begin();

    Serial.println("[APP] Starting display bridge...");
    display.begin();

    Serial.println("[APP] Starting Firebase...");
    firebase.begin();

    Serial.println("[APP] System initialized successfully.");
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

    data.wifiConnected = firebase.isWiFiConnected();
    data.firebaseReady = firebase.isFirebaseReady();

    data.timestamp = millis();
}
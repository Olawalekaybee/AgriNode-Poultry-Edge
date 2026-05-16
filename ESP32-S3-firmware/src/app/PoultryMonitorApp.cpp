#include "PoultryMonitorApp.h"
#include "AppConfig.h"

void PoultryMonitorApp::begin() {
    Serial.println("[APP] Starting AgriNode Poultry Edge...");

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY);

    Serial.println("[APP] I2C initialized");

    // =========================
    // Sensors
    // =========================
    Serial.println("[APP] Starting DHT22...");
    dht22.begin();

    Serial.println("[APP] Starting SHT31...");
    sht31.begin();

    Serial.println("[APP] Starting ADS1115/LDR...");
    ldr.begin();

    // =========================
    // GPS
    // =========================
    Serial.println("[APP] Starting GPS...");
    gps.begin();

    // =========================
    // Display Bridge
    // =========================
    Serial.println("[APP] Starting display bridge...");
    display.begin();

    // =========================
    // Cloud Services
    // =========================
    Serial.println("[APP] Starting Firebase...");
    firebase.begin();

    Serial.println("[APP] Starting MQTT...");
    mqtt.begin();

    Serial.println("[APP] System initialized successfully.");
}

void PoultryMonitorApp::update() {
    gps.update();
    mqtt.update();

    unsigned long now = millis();

    // =========================
    // Sensor Read Cycle
    // =========================
    if (now - lastSensorRead >= SENSOR_READ_INTERVAL_MS) {
        lastSensorRead = now;

        readSensors();
    }

    // =========================
    // Display Update Cycle
    // =========================
    if (now - lastDisplayUpdate >= DISPLAY_REFRESH_INTERVAL_MS) {
        lastDisplayUpdate = now;

        display.send(data);
    }

    // =========================
    // Firebase Upload Cycle
    // =========================
    if (now - lastFirebaseUpload >= FIREBASE_UPLOAD_INTERVAL_MS) {
        lastFirebaseUpload = now;

        firebase.upload(data);
    }

    // =========================
    // MQTT Publish Cycle
    // =========================
    if (now - lastMqttPublish >= 5000) {
        lastMqttPublish = now;

        mqtt.publishTelemetry(data);
    }
}

void PoultryMonitorApp::readSensors() {
    dht22.read(data);
    sht31.read(data);
    ldr.read(data);
    gps.read(data);

    // =========================
    // Connectivity Status
    // =========================
    data.wifiConnected = firebase.isWiFiConnected();
    data.firebaseReady = firebase.isFirebaseReady();

    data.timestamp = millis();

    // =========================
    // Debug Output
    // =========================
    Serial.println("-------- SENSOR DATA --------");

    Serial.print("Indoor Temperature: ");
    Serial.print(data.indoorTemperature);
    Serial.println(" °C");

    Serial.print("Indoor Humidity: ");
    Serial.print(data.indoorHumidity);
    Serial.println(" %");

    Serial.print("Outdoor Temperature: ");
    Serial.print(data.outdoorTemperature);
    Serial.println(" °C");

    Serial.print("Outdoor Humidity: ");
    Serial.print(data.outdoorHumidity);
    Serial.println(" %");

    Serial.print("LDR Raw A0: ");
    Serial.println(data.lightIntensityRaw);

    Serial.print("LDR Voltage A0: ");
    Serial.print(data.lightVoltage, 4);
    Serial.println(" V");

    Serial.print("WiFi Connected: ");
    Serial.println(data.wifiConnected ? "YES" : "NO");

    Serial.print("Firebase Ready: ");
    Serial.println(data.firebaseReady ? "YES" : "NO");

    Serial.print("MQTT Connected: ");
    Serial.println(mqtt.isConnected() ? "YES" : "NO");

    Serial.println("-----------------------------");
}
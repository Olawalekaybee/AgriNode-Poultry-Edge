#include "PoultryMonitorApp.h"
#include "AppConfig.h"

#include <WiFi.h>

void PoultryMonitorApp::begin()
{
    Serial.println();
    Serial.println("======================================");
    Serial.println(" AgriNode Poultry Edge Booting...");
    Serial.println("======================================");

    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    Serial.println("[APP] Initializing I2C...");
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(I2C_FREQUENCY);

    Serial.print("[APP] SDA: ");
    Serial.println(I2C_SDA_PIN);

    Serial.print("[APP] SCL: ");
    Serial.println(I2C_SCL_PIN);

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

    Serial.println("[APP] Starting MQTT...");
    mqtt.begin();

    Serial.println("[APP] Starting OTA...");
    ota.begin();

    Serial.println("[APP] Starting Task Manager...");
    TaskManager::begin(
        &mqtt,
        &ota,
        &gps
    );

    Serial.println("[APP] System initialized successfully.");
    Serial.println("======================================");
}

void PoultryMonitorApp::update()
{
    TaskManager::update();

    unsigned long now = millis();

    if (now - lastSensorRead >= SENSOR_READ_INTERVAL_MS)
    {
        lastSensorRead = now;
        readSensors();
    }

    if (now - lastDisplayUpdate >= DISPLAY_REFRESH_INTERVAL_MS)
    {
        lastDisplayUpdate = now;
        updateDisplay();
    }

    if (now - lastFirebaseUpload >= FIREBASE_UPLOAD_INTERVAL_MS)
    {
        lastFirebaseUpload = now;
        uploadFirebase();
    }

    if (now - lastMqttPublish >= MQTT_PUBLISH_INTERVAL_MS)
    {
        lastMqttPublish = now;
        publishMqtt();
    }

    if (now - lastHealthLog >= 15000)
    {
        lastHealthLog = now;
        logSystemHealth();
    }

    yield();
}

void PoultryMonitorApp::readSensors()
{
    unsigned long startTime = millis();

    dht22.read(data);
    yield();

    sht31.read(data);
    yield();

    ldr.read(data);
    yield();

    gps.read(data);
    yield();

    data.wifiConnected = firebase.isWiFiConnected();
    data.firebaseReady = firebase.isFirebaseReady();
    data.timestamp = millis();

    digitalWrite(STATUS_LED_PIN, mqtt.isConnected() ? HIGH : LOW);

#if ENABLE_DEBUG_LOGS
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

    Serial.print("[PERF] Sensor read took ");
    Serial.print(millis() - startTime);
    Serial.println(" ms");

    Serial.println("-----------------------------");
#endif
}

void PoultryMonitorApp::updateDisplay()
{
    unsigned long startTime = millis();

    display.send(data);
    yield();

#if ENABLE_DEBUG_LOGS
    Serial.print("[PERF] Display update took ");
    Serial.print(millis() - startTime);
    Serial.println(" ms");
#endif
}

void PoultryMonitorApp::uploadFirebase()
{
    if (WiFi.status() != WL_CONNECTED)
    {
#if ENABLE_DEBUG_LOGS
        Serial.println("[Firebase] Skipped: WiFi disconnected");
#endif
        data.wifiConnected = false;
        data.firebaseReady = false;
        return;
    }

    data.wifiConnected = true;

    if (!data.firebaseReady)
    {
#if ENABLE_DEBUG_LOGS
        Serial.println("[Firebase] Skipped: Firebase not ready");
#endif
        return;
    }

#if ENABLE_DEBUG_LOGS
    Serial.println("[Firebase] Upload attempt...");
#endif

    unsigned long startTime = millis();

    firebase.upload(data);
    yield();

#if ENABLE_DEBUG_LOGS
    Serial.print("[PERF] Firebase upload took ");
    Serial.print(millis() - startTime);
    Serial.println(" ms");
#endif
}

void PoultryMonitorApp::publishMqtt()
{
    if (!mqtt.isConnected())
    {
#if ENABLE_DEBUG_LOGS
        Serial.println("[MQTT] Publish skipped: MQTT disconnected");
#endif
        return;
    }

    unsigned long startTime = millis();

    mqtt.publishTelemetry(data);
    yield();

#if ENABLE_DEBUG_LOGS
    Serial.print("[PERF] MQTT publish took ");
    Serial.print(millis() - startTime);
    Serial.println(" ms");
#endif
}

void PoultryMonitorApp::logSystemHealth()
{
#if ENABLE_DEBUG_LOGS
    Serial.println("-------- SYSTEM HEALTH --------");

    Serial.print("Uptime: ");
    Serial.print(millis() / 1000);
    Serial.println(" s");

    Serial.print("Free Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");

    Serial.print("WiFi RSSI: ");
    Serial.println(WiFi.status() == WL_CONNECTED ? WiFi.RSSI() : 0);

    Serial.print("MQTT Connected: ");
    Serial.println(mqtt.isConnected() ? "YES" : "NO");

    if (ESP.getFreeHeap() < LOW_HEAP_WARNING_BYTES)
    {
        Serial.println("[WARN] Low heap memory detected");
    }

    Serial.println("-------------------------------");
#endif
}
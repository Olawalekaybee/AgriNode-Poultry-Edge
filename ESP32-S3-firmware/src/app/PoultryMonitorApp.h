#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "SensorData.h"

#include "sensors/DHT22Sensor.h"
#include "sensors/SHT31Sensor.h"
#include "sensors/LDRSensor.h"
#include "sensors/GPSSensor.h"

#include "display/DisplayBridge.h"

#include "cloud/FirebaseService.h"
#include "cloud/MQTTService.h"

#include "ota/OTAService.h"
#include "core/TaskManager.h"

class PoultryMonitorApp {
public:
    void begin();
    void update();

private:
    SensorData data;

    DHT22Sensor dht22;
    SHT31Sensor sht31;
    LDRSensor ldr;
    GPSSensor gps;

    DisplayBridge display;

    FirebaseService firebase;
    MQTTService mqtt;
    OTAService ota;

    unsigned long lastSensorRead = 0;
    unsigned long lastDisplayUpdate = 0;
    unsigned long lastFirebaseUpload = 0;
    unsigned long lastMqttPublish = 0;
    unsigned long lastHealthLog = 0;

    void readSensors();
    void updateDisplay();
    void uploadFirebase();
    void publishMqtt();
    void logSystemHealth();
};
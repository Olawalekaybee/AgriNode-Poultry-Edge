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

    unsigned long lastSensorRead = 0;
    unsigned long lastDisplayUpdate = 0;
    unsigned long lastFirebaseUpload = 0;

    void readSensors();
};
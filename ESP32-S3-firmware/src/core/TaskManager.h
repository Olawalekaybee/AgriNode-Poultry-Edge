#pragma once

#include <Arduino.h>

#include "cloud/MQTTService.h"
#include "ota/OTAService.h"
#include "sensors/GPSSensor.h"

class TaskManager {
public:
    static void begin(
        MQTTService* mqtt,
        OTAService* ota,
        GPSSensor* gps
    );

    static void update();

private:
    static TaskHandle_t networkTaskHandle;

    static bool started;

    static MQTTService* mqttService;
    static OTAService* otaService;
    static GPSSensor* gpsSensor;

    static void networkTask(void* parameter);
};
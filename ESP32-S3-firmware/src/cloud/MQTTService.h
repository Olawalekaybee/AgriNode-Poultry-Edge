#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#include "SensorData.h"

class MQTTService {
public:
    void begin();
    void update();

    bool publishTelemetry(const SensorData& data);
    bool isConnected();

    void handleCommand(char* topic, byte* payload, unsigned int length);

private:
    WiFiClientSecure wifiClient;
    PubSubClient client{wifiClient};

    static MQTTService* instance;

    unsigned long lastReconnectAttempt = 0;

    bool reconnect();
    String buildTelemetryPayload(const SensorData& data);

    static void mqttCallback(char* topic, byte* payload, unsigned int length);
};
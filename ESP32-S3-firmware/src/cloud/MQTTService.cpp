#include "cloud/MQTTService.h"
#include "Secrets.h"

MQTTService* MQTTService::instance = nullptr;

void MQTTService::begin() {
    wifiClient.setInsecure();

    client.setServer(MQTT_HOST, MQTT_PORT);
    client.setBufferSize(512);
    client.setKeepAlive(60);
    client.setSocketTimeout(15);

    instance = this;
    client.setCallback(mqttCallback);

    Serial.println("[MQTT] Service initialized");
}

void MQTTService::update() {
    if (!client.connected()) {
        unsigned long now = millis();

        if (now - lastReconnectAttempt >= 5000) {
            lastReconnectAttempt = now;
            reconnect();
        }

        return;
    }

    client.loop();
}

bool MQTTService::reconnect() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("[MQTT] WiFi not connected");
        return false;
    }

    Serial.print("[MQTT] Connecting to ");
    Serial.print(MQTT_HOST);
    Serial.print(":");
    Serial.print(MQTT_PORT);
    Serial.print(" ... ");

    bool connected = client.connect(
        MQTT_CLIENT_ID,
        MQTT_USERNAME,
        MQTT_PASSWORD,
        MQTT_STATUS_TOPIC,
        1,
        true,
        "offline"
    );

    if (connected) {
        Serial.println("connected");

        client.publish(MQTT_STATUS_TOPIC, "online", true);

        if (client.subscribe(MQTT_COMMAND_TOPIC, 1)) {
            Serial.print("[MQTT] Subscribed to command topic: ");
            Serial.println(MQTT_COMMAND_TOPIC);
        } else {
            Serial.println("[MQTT] Failed to subscribe to command topic");
        }

        return true;
    }

    Serial.print("failed, rc=");
    Serial.println(client.state());

    return false;
}

bool MQTTService::publishTelemetry(const SensorData& data) {
    if (!client.connected()) {
        Serial.println("[MQTT] Publish skipped: not connected");
        return false;
    }

    String payload = buildTelemetryPayload(data);

    bool success = client.publish(MQTT_TELEMETRY_TOPIC, payload.c_str());

    if (success) {
        Serial.println("[MQTT] Telemetry published");
    } else {
        Serial.print("[MQTT] Telemetry publish failed. Payload size: ");
        Serial.println(payload.length());
    }

    return success;
}

bool MQTTService::isConnected() {
    return client.connected();
}

void MQTTService::mqttCallback(char* topic, byte* payload, unsigned int length) {
    if (instance != nullptr) {
        instance->handleCommand(topic, payload, length);
    }
}

void MQTTService::handleCommand(char* topic, byte* payload, unsigned int length) {
    String message;

    for (unsigned int i = 0; i < length; i++) {
        message += static_cast<char>(payload[i]);
    }

    Serial.print("[MQTT] Command topic: ");
    Serial.println(topic);

    Serial.print("[MQTT] Command payload: ");
    Serial.println(message);

    if (message.indexOf("restart") >= 0) {
        Serial.println("[MQTT] Restart command received. Restarting device...");
        delay(1000);
        ESP.restart();
    }

    if (message.indexOf("ping") >= 0) {
        client.publish(MQTT_STATUS_TOPIC, "pong", false);
        Serial.println("[MQTT] Ping command received. Pong sent.");
    }
}

String MQTTService::buildTelemetryPayload(const SensorData& data) {
    String payload;

    payload.reserve(512);

    payload += "{";
    payload += "\"device\":\"" MQTT_CLIENT_ID "\",";
    payload += "\"indoor\":{";
    payload += "\"temperature\":" + String(data.indoorTemperature, 1) + ",";
    payload += "\"humidity\":" + String(data.indoorHumidity, 1);
    payload += "},";
    payload += "\"outdoor\":{";
    payload += "\"temperature\":" + String(data.outdoorTemperature, 1) + ",";
    payload += "\"humidity\":" + String(data.outdoorHumidity, 1);
    payload += "},";
    payload += "\"light\":{";
    payload += "\"raw\":" + String(data.lightIntensityRaw) + ",";
    payload += "\"voltage\":" + String(data.lightVoltage, 2);
    payload += "},";
    payload += "\"gps\":{";
    payload += "\"valid\":" + String(data.gpsValid ? "true" : "false") + ",";
    payload += "\"latitude\":" + String(data.latitude, 6) + ",";
    payload += "\"longitude\":" + String(data.longitude, 6) + ",";
    payload += "\"satellites\":" + String(data.gpsSatellites);
    payload += "},";
    payload += "\"datetime\":{";
    payload += "\"date\":\"" + data.date + "\",";
    payload += "\"time\":\"" + data.time + "\"";
    payload += "},";
    payload += "\"system\":{";
    payload += "\"uptime_ms\":" + String(data.timestamp) + ",";
    payload += "\"wifi\":true,";
    payload += "\"mqtt\":" + String(client.connected() ? "true" : "false");
    payload += "}";
    payload += "}";

    return payload;
}
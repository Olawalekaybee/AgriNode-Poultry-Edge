#include "ota/OTAService.h"

#include <WiFi.h>
#include <ArduinoOTA.h>

void OTAService::begin()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("[OTA] WiFi not connected. OTA disabled for now.");
        return;
    }

    ArduinoOTA.setHostname("agrinode-poultry-edge-001");

    ArduinoOTA.onStart([]() {
        Serial.println("[OTA] Update started");
    });

    ArduinoOTA.onEnd([]() {
        Serial.println("[OTA] Update finished");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("[OTA] Progress: %u%%\n", (progress * 100) / total);
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("[OTA] Error[%u]: ", error);

        if (error == OTA_AUTH_ERROR) Serial.println("Auth failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive failed");
        else if (error == OTA_END_ERROR) Serial.println("End failed");
    });

    ArduinoOTA.begin();

    initialized = true;

    Serial.println("[OTA] Ready");
    Serial.print("[OTA] IP Address: ");
    Serial.println(WiFi.localIP());
}

void OTAService::update()
{
    if (initialized)
    {
        ArduinoOTA.handle();
    }
}
#include "DisplayBridge.h"
#include "AppConfig.h"

void DisplayBridge::begin() {
    Serial.println("[DisplayBridge] CYD I2C bridge ready");
}

bool DisplayBridge::send(const SensorData& data) {
    String payload = buildPayload(data);

    Wire.beginTransmission(CYD_I2C_ADDRESS);
    Wire.write((const uint8_t*)payload.c_str(), payload.length());
    uint8_t result = Wire.endTransmission();

    if (result == 0) {
        Serial.println("[DisplayBridge] Data sent to CYD");
        return true;
    }

    Serial.print("[DisplayBridge] I2C send failed. Code: ");
    Serial.println(result);
    return false;
}

String DisplayBridge::buildPayload(const SensorData& data) {
    String payload;

    payload += "{";
    payload += "\"it\":" + String(data.indoorTemperature, 1) + ",";
    payload += "\"ih\":" + String(data.indoorHumidity, 1) + ",";
    payload += "\"ot\":" + String(data.outdoorTemperature, 1) + ",";
    payload += "\"oh\":" + String(data.outdoorHumidity, 1) + ",";
    payload += "\"lv\":" + String(data.lightVoltage, 2) + ",";
    payload += "\"lr\":" + String(data.lightIntensityRaw, 0) + ",";
    payload += "\"lat\":" + String(data.latitude, 6) + ",";
    payload += "\"lng\":" + String(data.longitude, 6) + ",";
    payload += "\"sat\":" + String(data.gpsSatellites) + ",";
    payload += "\"gps\":" + String(data.gpsValid ? 1 : 0) + ",";
    payload += "\"wifi\":" + String(data.wifiConnected ? 1 : 0) + ",";
    payload += "\"fb\":" + String(data.firebaseReady ? 1 : 0) + ",";
    payload += "\"date\":\"" + data.date + "\",";
    payload += "\"time\":\"" + data.time + "\"";
    payload += "}";

    return payload;
}
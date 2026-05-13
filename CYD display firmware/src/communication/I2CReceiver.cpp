#include "I2CReceiver.h"
#include "AppConfig_.h"
#include <ArduinoJson.h>

String I2CReceiver::incomingPayload = "";
bool I2CReceiver::newDataAvailable = false;

void I2CReceiver::begin()
{
    Wire.begin(I2C_SLAVE_ADDRESS, I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.onReceive(I2CReceiver::onReceiveHandler);

    Serial.print("[I2C] CYD slave started at address 0x");
    Serial.println(I2C_SLAVE_ADDRESS, HEX);
}

void I2CReceiver::onReceiveHandler(int byteCount)
{
    String payload;

    while (Wire.available())
    {
        char c = static_cast<char>(Wire.read());
        payload += c;
    }

    if (payload.length() > 0)
    {
        incomingPayload = payload;
        newDataAvailable = true;
    }
}

bool I2CReceiver::hasNewData() const
{
    return newDataAvailable;
}

bool I2CReceiver::readLatest(TelemetryData &data)
{
    if (!newDataAvailable)
    {
        return false;
    }

    String payload = incomingPayload;
    newDataAvailable = false;

    return parsePayload(payload, data);
}

bool I2CReceiver::parsePayload(const String &payload, TelemetryData &data)
{
    StaticJsonDocument<384> doc;

    DeserializationError error = deserializeJson(doc, payload);

    if (error)
    {
        Serial.print("[JSON] Parse failed: ");
        Serial.println(error.c_str());
        Serial.println(payload);
        return false;
    }

    data.indoorTemperature = doc["it"] | 0.0;
    data.indoorHumidity = doc["ih"] | 0.0;

    data.outdoorTemperature = doc["ot"] | 0.0;
    data.outdoorHumidity = doc["oh"] | 0.0;

    data.lightVoltage = doc["lv"] | 0.0;
    data.lightRaw = doc["lr"] | 0.0;

    data.latitude = doc["lat"] | 0.0;
    data.longitude = doc["lng"] | 0.0;

    data.satellites = doc["sat"] | 0;
    data.gpsValid = (doc["gps"] | 0) == 1;

    data.date = doc["date"] | "--";
    data.time = doc["time"] | "--";

    data.wifiConnected = (doc["wifi"] | 0) == 1;
    data.firebaseReady = (doc["fb"] | 0) == 1;

    data.dataReceived = true;
    data.lastUpdate = millis();

    return true;
}
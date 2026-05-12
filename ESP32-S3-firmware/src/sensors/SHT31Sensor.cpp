#include "sensors/SHT31Sensor.h"

void SHT31Sensor::begin() {
    available = sht31.begin(0x44);

    if (!available) {
        Serial.println("[SHT31] Sensor not found");
    } else {
        Serial.println("[SHT31] Sensor initialized");
    }
}

bool SHT31Sensor::read(SensorData& data) {
    if (!available) {
        return false;
    }

    float temperature = sht31.readTemperature();
    float humidity = sht31.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("[SHT31] Invalid reading");
        return false;
    }

    data.outdoorTemperature = temperature;
    data.outdoorHumidity = humidity;

    return true;
}
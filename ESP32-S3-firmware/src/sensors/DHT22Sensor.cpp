#include "sensors/DHT22Sensor.h"
#include "AppConfig.h"

DHT22Sensor::DHT22Sensor() : dht(DHT_PIN, DHT_TYPE) {}

void DHT22Sensor::begin() {
    dht.begin();
}

bool DHT22Sensor::read(SensorData& data) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("[DHT22] Failed to read sensor");
        return false;
    }

    data.indoorTemperature = temperature;
    data.indoorHumidity = humidity;

    return true;
}
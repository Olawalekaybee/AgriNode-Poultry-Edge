#include "sensors/LDRSensor.h"

void LDRSensor::begin() {
    available = ads.begin(0x48);

    if (!available) {
        Serial.println("[ADS1115] ADC not found");
        return;
    }

    ads.setGain(GAIN_ONE);

    Serial.println("[ADS1115] ADC initialized");
}

bool LDRSensor::read(SensorData& data) {
    if (!available) {
        return false;
    }

    int16_t adcValue = ads.readADC_SingleEnded(0);

    float voltage = adcValue * 0.125F / 1000.0F;

    data.lightIntensityRaw = adcValue;
    data.lightVoltage = voltage;

    return true;
}
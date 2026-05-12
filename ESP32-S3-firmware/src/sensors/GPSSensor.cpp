#include "sensors/GPSSensor.h"
#include "AppConfig.h"

void GPSSensor::begin() {
    gpsSerial.begin(
        GPS_BAUD_RATE,
        SERIAL_8N1,
        GPS_RX_PIN,
        GPS_TX_PIN
    );

    Serial.println("[GPS] UART initialized");
}

void GPSSensor::update() {
    while (gpsSerial.available() > 0) {
        gps.encode(gpsSerial.read());
    }
}

bool GPSSensor::read(SensorData& data) {
    data.gpsValid = gps.location.isValid();
    data.gpsSatellites = gps.satellites.value();

    if (gps.location.isValid()) {
        data.latitude = gps.location.lat();
        data.longitude = gps.location.lng();
    }

    if (gps.date.isValid()) {
        data.date = formatDate();
    }

    if (gps.time.isValid()) {
        data.time = formatTime();
    }

    return data.gpsValid;
}

String GPSSensor::formatDate() {
    char buffer[16];

    snprintf(
        buffer,
        sizeof(buffer),
        "%02d-%02d-%04d",
        gps.date.day(),
        gps.date.month(),
        gps.date.year()
    );

    return String(buffer);
}

String GPSSensor::formatTime() {
    char buffer[16];

    snprintf(
        buffer,
        sizeof(buffer),
        "%02d:%02d:%02d",
        gps.time.hour(),
        gps.time.minute(),
        gps.time.second()
    );

    return String(buffer);
}
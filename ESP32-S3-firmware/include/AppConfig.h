#pragma once

// =========================
// SENSOR PINS
// =========================
#define DHT_PIN 5
#define DHT_TYPE DHT22

// =========================
// GPS UART
// =========================
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD_RATE 9600

// =========================
// MAIN I2C BUS
// Used by SHT31, ADS1115, and CYD display bridge
// =========================
#define I2C_SDA_PIN 8
#define I2C_SCL_PIN 9
#define I2C_FREQUENCY 100000
#define STATUS_LED_PIN 2

// CYD display board I2C slave address
#define CYD_I2C_ADDRESS 0x12

// =========================
// TIMING
// =========================
#define FIREBASE_UPLOAD_INTERVAL_MS 30000
#define DISPLAY_REFRESH_INTERVAL_MS 4000
#define SENSOR_READ_INTERVAL_MS 2000

#define MQTT_PUBLISH_INTERVAL_MS 10000
#define FIREBASE_UPLOAD_INTERVAL_MS 30000

#define LOW_HEAP_WARNING_BYTES 40000
#define ENABLE_DEBUG_LOGS 1
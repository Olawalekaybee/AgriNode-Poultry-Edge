#include "DashboardDisplay.h"
#include "AppConfig_.h"

void DashboardDisplay::begin() {
    Serial.println("[Display] Initializing CYD dashboard...");

#ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
    delay(200);
#endif

    tft.init();
    tft.setRotation(DISPLAY_ROTATION);
    tft.fillScreen(TFT_BLACK);

    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    Serial.println("[Display] CYD dashboard initialized");
}

void DashboardDisplay::render(const TelemetryData& data) {
    tft.fillScreen(TFT_BLACK);

    if (!data.dataReceived) {
        tft.fillScreen(TFT_NAVY);
        tft.setTextColor(TFT_WHITE, TFT_NAVY);
        tft.setTextSize(2);
        tft.setCursor(35, 75);
        tft.print("AgriNode Poultry");

        tft.setTextSize(1);
        tft.setCursor(70, 115);
        tft.print("Waiting for ESP32-S3 data...");

        tft.setCursor(95, 140);
        tft.print("I2C Address: 0x12");

        return;
    }

    drawHeader(data);
    drawCards(data);
    drawFooter(data);
}

void DashboardDisplay::drawHeader(const TelemetryData& data) {
    tft.fillRoundRect(0, 0, 320, 36, 6, TFT_NAVY);

    tft.setTextColor(TFT_WHITE, TFT_NAVY);
    tft.setTextSize(2);
    tft.setCursor(8, 9);
    tft.print("AgriNode");

    tft.setTextSize(1);

    tft.setCursor(140, 6);
    tft.setTextColor(data.wifiConnected ? TFT_GREEN : TFT_RED, TFT_NAVY);
    tft.print(data.wifiConnected ? "WiFi OK" : "WiFi NO");

    tft.setCursor(140, 21);
    tft.setTextColor(data.firebaseReady ? TFT_GREEN : TFT_ORANGE, TFT_NAVY);
    tft.print(data.firebaseReady ? "Firebase OK" : "Firebase NO");

    tft.setCursor(240, 6);
    tft.setTextColor(data.gpsValid ? TFT_GREEN : TFT_RED, TFT_NAVY);
    tft.print(data.gpsValid ? "GPS OK" : "GPS NO");

    tft.setCursor(240, 21);
    tft.setTextColor(TFT_GREEN, TFT_NAVY);
    tft.print("I2C OK");
}

void DashboardDisplay::drawCards(const TelemetryData& data) {
    drawCard(6, 43, 100, 45, "Indoor T", String(data.indoorTemperature, 1), "C");
    drawCard(110, 43, 100, 45, "Indoor H", String(data.indoorHumidity, 1), "%");
    drawCard(214, 43, 100, 45, "Light", String(data.lightVoltage, 2), "V");

    drawCard(6, 94, 100, 45, "Outdoor T", String(data.outdoorTemperature, 1), "C");
    drawCard(110, 94, 100, 45, "Outdoor H", String(data.outdoorHumidity, 1), "%");
    drawCard(214, 94, 100, 45, "LDR Raw", String(data.lightRaw, 0), "");

    drawCard(6, 145, 100, 45, "GPS Sat", String(data.satellites), "");
    drawCard(110, 145, 100, 45, "Latitude", String(data.latitude, 2), "");
    drawCard(214, 145, 100, 45, "Longitude", String(data.longitude, 2), "");
}

void DashboardDisplay::drawFooter(const TelemetryData& data) {
    tft.fillRoundRect(0, 198, 320, 42, 6, TFT_DARKGREY);

    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.setTextSize(1);

    tft.setCursor(8, 207);
    tft.print("Date: ");
    tft.print(data.date);

    tft.setCursor(8, 224);
    tft.print("Time: ");
    tft.print(data.time);

    tft.setCursor(150, 207);
    tft.print("WiFi: ");
    tft.setTextColor(data.wifiConnected ? TFT_GREEN : TFT_RED, TFT_DARKGREY);
    tft.print(data.wifiConnected ? "CONNECTED" : "OFFLINE");

    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.setCursor(150, 224);
    tft.print("Cloud: ");
    tft.setTextColor(data.firebaseReady ? TFT_GREEN : TFT_ORANGE, TFT_DARKGREY);
    tft.print(data.firebaseReady ? "READY" : "NOT READY");
}

void DashboardDisplay::drawCard(
    int x,
    int y,
    int w,
    int h,
    const String& title,
    const String& value,
    const String& unit
) {
    tft.fillRoundRect(x, y, w, h, 7, TFT_DARKGREY);
    tft.drawRoundRect(x, y, w, h, 7, TFT_LIGHTGREY);

    tft.setTextColor(TFT_CYAN, TFT_DARKGREY);
    tft.setTextSize(1);
    tft.setCursor(x + 6, y + 5);
    tft.print(title);

    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.setTextSize(2);
    tft.setCursor(x + 6, y + 21);
    tft.print(value);

    if (unit.length() > 0) {
        tft.setTextSize(1);
        tft.setCursor(x + w - 18, y + 29);
        tft.print(unit);
    }
}
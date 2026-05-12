#include "cloud/FirebaseService.h"
#include "Secrets.h"

void FirebaseService::begin() {
    connectWiFi();

    config.api_key = FIREBASE_API_KEY;
    config.database_url = FIREBASE_DATABASE_URL;

    auth.user.email = FIREBASE_USER_EMAIL;
    auth.user.password = FIREBASE_USER_PASSWORD;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("[Firebase] Initializing...");
}

void FirebaseService::connectWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("[WiFi] Connecting");

    unsigned long startAttempt = millis();

    while (WiFi.status() != WL_CONNECTED && millis() - startAttempt < 20000) {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.print("[WiFi] Connected. IP: ");
        Serial.println(WiFi.localIP());
        ready = true;
    } else {
        Serial.println();
        Serial.println("[WiFi] Connection failed");
        ready = false;
    }
}

bool FirebaseService::upload(const SensorData& data) {
    if (!ready || !Firebase.ready()) {
        Serial.println("[Firebase] Not ready");
        return false;
    }

    FirebaseJson json;

    json.set("indoor/temperature", data.indoorTemperature);
    json.set("indoor/humidity", data.indoorHumidity);

    json.set("outdoor/temperature", data.outdoorTemperature);
    json.set("outdoor/humidity", data.outdoorHumidity);

    json.set("light/raw", data.lightIntensityRaw);
    json.set("light/voltage", data.lightVoltage);

    json.set("gps/valid", data.gpsValid);
    json.set("gps/latitude", data.latitude);
    json.set("gps/longitude", data.longitude);
    json.set("gps/satellites", data.gpsSatellites);

    json.set("datetime/date", data.date);
    json.set("datetime/time", data.time);

    json.set("system/uptime_ms", data.timestamp);

    String path = "/poultry_monitoring/latest";

    if (Firebase.RTDB.setJSON(&fbdo, path.c_str(), &json)) {
        Serial.println("[Firebase] Upload successful");
        return true;
    }

    Serial.print("[Firebase] Upload failed: ");
    Serial.println(fbdo.errorReason());

    return false;
}
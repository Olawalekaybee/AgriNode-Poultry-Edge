#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "TelemetryData.h"

class I2CReceiver {
public:
    void begin();
    bool hasNewData() const;
    bool readLatest(TelemetryData& data);

private:
    static void onReceiveHandler(int byteCount);
    static String incomingPayload;
    static bool newDataAvailable;

    bool parsePayload(const String& payload, TelemetryData& data);
};
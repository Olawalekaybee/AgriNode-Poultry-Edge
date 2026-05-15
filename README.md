<div align="center">

#   AgriNode Poultry Edge

### Intelligent Distributed Embedded IoT Platform for Poultry Environmental Monitoring

<p align="center">
  <img src="https://img.shields.io/badge/ESP32--S3-N16R8-blue?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/PlatformIO-Embedded-orange?style=for-the-badge&logo=platformio" />
  <img src="https://img.shields.io/badge/Firebase-Realtime-yellow?style=for-the-badge&logo=firebase" />
  <img src="https://img.shields.io/badge/Architecture-Distributed-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Display-CYD%20320x240-red?style=for-the-badge" />
</p>

---

### Edge Computing • Real-Time Telemetry • Smart Agriculture • Embedded Systems

</div>

---

# 📖 Project Overview

AgriNode Poultry Edge is a professional distributed embedded IoT system engineered for intelligent poultry farm environmental monitoring, cloud telemetry synchronization, and real-time local visualization.

The platform combines:

- 🌡 Environmental sensing
- 📍 GPS telemetry
- ☁ Cloud synchronization
- 📺 Edge dashboard visualization
- 🔄 Distributed embedded communication
- 📡 Real-time telemetry streaming

The architecture uses an **ESP32-S3 N16R8 Rev 1.1** as the primary edge controller and a dedicated **CYD 320×240 display node** communicating over I2C.

---

# 🏗 System Architecture

<div align="center">

```txt
                    ┌──────────────────────────┐
                    │ Firebase Realtime DB     │
                    │ Cloud Telemetry Platform │
                    └────────────┬─────────────┘
                                 │
                                 │ WiFi
                                 │
                   ┌─────────────▼─────────────┐
                   │ ESP32-S3 Edge Controller  │
                   │ Sensor Aggregation Engine │
                   └─────────────┬─────────────┘
                                 │
                           I2C Telemetry Bus
                                 │
                   ┌─────────────▼─────────────┐
                   │ CYD Dashboard Display     │
                   │ ILI9341_2_DRIVER          │
                   └───────────────────────────┘
```

</div>

---

# 🔧 Core Features

## Environmental Monitoring

- Indoor temperature monitoring
- Indoor humidity monitoring
- Outdoor temperature monitoring
- Outdoor humidity monitoring
- Ambient light intensity sensing

## Telemetry & Positioning

- GPS location tracking
- Satellite acquisition monitoring
- UTC date synchronization
- UTC time synchronization

## Cloud Infrastructure

- Firebase Realtime Database integration
- WiFi telemetry upload
- Real-time cloud synchronization

## Embedded Display System

- Distributed CYD display node
- Real-time telemetry dashboard
- I2C telemetry bridge
- Live environmental visualization

---

# 🧠 Hardware Components

| Component | Function |
|---|---|
| ESP32-S3 N16R8 Rev 1.1 | Main edge controller |
| CYD 320×240 Display | Visualization node |
| DHT22 | Indoor temperature & humidity |
| SHT31 | Outdoor temperature & humidity |
| ADS1115 | Precision ADC |
| LDR | Light intensity sensing |
| GPS Module | Location, date & time |

---

# ⚡ Embedded Interfaces

| Interface | Connected Devices |
|---|---|
| GPIO | DHT22 |
| I2C | SHT31, ADS1115, CYD Display |
| UART | GPS Module |
| WiFi | Firebase Cloud |

---

# 📂 Repository Structure

```txt
AgriNode-Poultry-Edge/
│
├── ESP32-S3-firmware/
│   ├── include/
│   ├── lib/
│   ├── src/
│   ├── platformio.ini
│   └── .gitignore
│
├── CYD display firmware/
│   ├── include/
│   ├── lib/
│   ├── src/
│   ├── platformio.ini
│   └── .gitignore
│
├── README.md
└── .gitignore
```

---

# 🧩 Firmware Architecture

## ESP32-S3 Edge Firmware

Responsible for:

- Sensor acquisition
- GPS telemetry parsing
- Firebase communication
- I2C telemetry transmission
- Environmental data processing
- System scheduling

### Major Modules

```txt
PoultryMonitorApp
├── SensorManager
├── DisplayBridge
├── FirebaseService
├── GPSManager
└── TelemetryScheduler
```

---

## CYD Display Firmware

Dedicated telemetry visualization node.

### Responsibilities

- Receives I2C telemetry packets
- Parses JSON telemetry
- Renders dashboard UI
- Displays environmental conditions
- Displays network/system status

### Display Driver

```txt
ILI9341_2_DRIVER
```

---

# 🔄 Data Flow

```txt
Sensors
   ↓
ESP32-S3 Sensor Manager
   ↓
Telemetry Processing
   ↓
├── Firebase Cloud Upload
│
└── I2C Telemetry Bridge
         ↓
    CYD Dashboard Display
```

---

# ☁ Firebase Integration

Telemetry is uploaded to Firebase Realtime Database in real time.

## Example Telemetry Payload

```json
{
  "indoor": {
    "temperature": 29.6,
    "humidity": 46.3
  },
  "outdoor": {
    "temperature": 30.3,
    "humidity": 64.5
  },
  "light": {
    "raw": 9,
    "voltage": 0.00
  },
  "gps": {
    "valid": false,
    "latitude": 0.0,
    "longitude": 0.0,
    "satellites": 0
  }
}
```

---

# 🛠 Development Environment

| Tool | Purpose |
|---|---|
| VS Code | Development IDE |
| PlatformIO | Embedded build system |
| Arduino Framework | ESP32 firmware framework |
| Firebase | Cloud telemetry backend |

---

# 🚀 Build & Upload

## ESP32-S3 Firmware

```bash
cd ESP32-S3-firmware
pio run -t upload
pio device monitor
```

## CYD Display Firmware

```bash
cd "CYD display firmware"
pio run -t upload
pio device monitor
```

---

# 🔒 Security

Sensitive credentials are excluded from source control.

## Ignored Files

```gitignore
Secrets.h
.pio/
.vscode/
```

Never commit:

- WiFi credentials
- Firebase secrets
- API tokens
- Certificates

---

# 📊 Current System Status

| Module | Status |
|---|---|
| ESP32-S3 Firmware | ✅ Stable |
| Sensor Acquisition | ✅ Operational |
| GPS Telemetry | ✅ Operational |
| Firebase Upload | ✅ Operational |
| CYD Dashboard | ✅ Operational |
| I2C Telemetry Bridge | ✅ Operational |
| Distributed Architecture | ✅ Operational |

---

# 🛣 Future Roadmap

- OTA firmware updates
- LVGL graphical dashboard
- Edge AI anomaly detection
- Multi-node deployment
- Offline telemetry buffering
- Mobile monitoring dashboard
- Remote firmware management
- SD card local logging
- CI/CD firmware pipelines
- MQTT telemetry support

---

# 📜 License

MIT License

---

<div align="center">

## Built with ESP32-S3, PlatformIO, Firebase & Embedded Systems Engineering

### AgriNode Poultry Edge • Smart Agriculture IoT Platform

</div>
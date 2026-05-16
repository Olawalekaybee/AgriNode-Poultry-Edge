# AgriNode Poultry Edge

### Industrial Edge IoT Platform for Smart Poultry Monitoring

<p align="center">
  <img src="https://img.shields.io/badge/ESP32--S3-N16R8-blue?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/PlatformIO-Embedded-orange?style=for-the-badge&logo=platformio" />
  <img src="https://img.shields.io/badge/FreeRTOS-Dual%20Core-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Firebase-Realtime-yellow?style=for-the-badge&logo=firebase" />
  <img src="https://img.shields.io/badge/MQTT-Telemetry-purple?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Display-CYD%20320x240-red?style=for-the-badge" />
</p>

---

### Edge Computing • Embedded Systems • Smart Agriculture • Real-Time Telemetry

---

# 📖 Project Overview

AgriNode Poultry Edge is a distributed embedded IoT platform engineered for intelligent poultry environmental monitoring, resilient edge telemetry, and real-time cloud synchronization.

The platform combines:

* 🌡 Environmental sensing
* ☁ Cloud telemetry synchronization
* 📡 MQTT real-time streaming
* 📺 Distributed dashboard visualization
* 🔄 OTA firmware management
* 🛰 GPS telemetry integration
* ⚙️ FreeRTOS dual-core scheduling
* 🌐 Offline-resilient edge operation

The system is powered by an **ESP32-S3 N16R8 Rev 1.1** acting as the primary edge controller, alongside a dedicated **CYD 320×240 dashboard node** communicating over I2C.

---

# ✨ Platform Highlights

* Dual-core ESP32-S3 FreeRTOS architecture
* OTA firmware update pipeline
* Real-time MQTT telemetry streaming
* Firebase cloud synchronization
* Offline-resilient edge operation
* Distributed CYD dashboard node
* GPS telemetry support
* Watchdog-safe scheduler architecture
* Industrial smart agriculture platform

---

# 🏗 System Architecture

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

---

# ⚙️ Runtime Architecture

```txt
Core 0
├── OTA Service Task
├── MQTT Communication Task
└── GPS Background Processing

Core 1
├── Sensor Scheduler
├── Display Scheduler
├── Firebase Scheduler
└── System Health Monitoring
```

---

# 🔧 Core Features

## Environmental Monitoring

* Indoor temperature monitoring
* Indoor humidity monitoring
* Outdoor temperature monitoring
* Outdoor humidity monitoring
* Ambient light intensity sensing

## Telemetry & Positioning

* GPS location tracking
* Satellite acquisition monitoring
* UTC date synchronization
* UTC time synchronization

## Cloud Infrastructure

* Firebase Realtime Database integration
* MQTT telemetry publishing
* WiFi cloud synchronization
* OTA firmware update support
* Remote telemetry monitoring

## Embedded Display System

* Distributed CYD dashboard node
* Real-time telemetry visualization
* I2C telemetry bridge
* Environmental dashboard rendering

---

# 🌐 Offline-Resilient Edge Operation

AgriNode Poultry Edge is designed to continue operating even during:

* WiFi outages
* Internet outages
* DNS failures
* MQTT broker downtime
* Firebase SSL failures

Core environmental monitoring and local dashboard visualization continue functioning independently from cloud infrastructure.

---

# 📡 MQTT Telemetry

The platform supports secure MQTT telemetry streaming for real-time monitoring and distributed integrations.

## Supported Features

* TLS-secured MQTT communication
* Real-time telemetry publishing
* Remote command subscription
* Automatic reconnect handling
* Offline-safe retry architecture

## Example Topics

```txt
agrinode/poultry/edge/001/telemetry
agrinode/poultry/edge/001/status
agrinode/poultry/edge/001/commands
```

---

# 🧠 Hardware Components

| Component              | Function                       |
| ---------------------- | ------------------------------ |
| ESP32-S3 N16R8 Rev 1.1 | Main edge controller           |
| CYD 320×240 Display    | Visualization node             |
| DHT22                  | Indoor temperature & humidity  |
| SHT31                  | Outdoor temperature & humidity |
| ADS1115                | Precision ADC                  |
| LDR                    | Light intensity sensing        |
| GPS Module             | Location, date & time          |

---

# ⚡ Embedded Interfaces

| Interface | Connected Devices           |
| --------- | --------------------------- |
| GPIO      | DHT22                       |
| I2C       | SHT31, ADS1115, CYD Display |
| UART      | GPS Module                  |
| WiFi      | Firebase Cloud, MQTT Broker |

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
├── CYD-display-firmware/
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

* Sensor acquisition
* GPS telemetry parsing
* MQTT communication
* Firebase synchronization
* OTA updates
* I2C telemetry transmission
* Environmental data processing
* Scheduler management

### Major Modules

```txt
PoultryMonitorApp
├── SensorManager
├── DisplayBridge
├── FirebaseService
├── MQTTService
├── OTAService
├── GPSManager
└── TaskManager
```

---

## CYD Dashboard Firmware

Dedicated telemetry visualization node.

### Responsibilities

* Receives I2C telemetry packets
* Parses telemetry payloads
* Renders dashboard UI
* Displays environmental conditions
* Displays network/system status

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
├── MQTT Telemetry Publish
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

| Tool              | Purpose                   |
| ----------------- | ------------------------- |
| VS Code           | Development IDE           |
| PlatformIO        | Embedded build system     |
| Arduino Framework | ESP32 firmware framework  |
| FreeRTOS          | Real-time task scheduling |
| Firebase          | Cloud telemetry backend   |
| HiveMQ Cloud      | MQTT telemetry broker     |

---

# 🚀 Build & Upload

## ESP32-S3 Firmware

```bash
cd ESP32-S3-firmware

pio run -t upload

pio device monitor
```

## OTA Upload

```bash
pio run -e esp32-s3-ota -t upload
```

## CYD Dashboard Firmware

```bash
cd CYD-display-firmware

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

---

# 📊 Current System Status

| Module                    | Status              |
| ------------------------- | ------------------- |
| ESP32-S3 Edge Firmware    | ✅ Production Stable |
| MQTT Telemetry            | ✅ Stable            |
| OTA Firmware Updates      | ✅ Stable            |
| Firebase Synchronization  | ✅ Stable            |
| CYD Distributed Dashboard | ✅ Stable            |
| FreeRTOS Task Scheduler   | ✅ Stable            |
| Offline Recovery System   | ✅ Stable            |
| GPS Telemetry             | ✅ Stable            |
| Sensor Monitoring         | ✅ Stable            |

---

# ✅ Completed Features

* OTA firmware updates
* MQTT telemetry support
* Distributed CYD dashboard bridge
* Firebase cloud synchronization
* Offline-safe cloud recovery
* FreeRTOS network task architecture
* GPS telemetry integration
* Real-time environmental monitoring
* Dual-core task scheduling

---

# 🚧 In Development

* LVGL graphical dashboard
* Sensor fault auto-recovery
* Remote device management
* Buffered telemetry queue
* Mobile monitoring dashboard

---

# 🔮 Planned Features

* Edge AI anomaly detection
* Multi-node deployment
* SD card persistent logging
* Fleet management dashboard
* CI/CD firmware pipelines
* Secure TLS certificate provisioning

---

# 📸 System Screenshots

> Dashboard previews and deployment screenshots will be added soon.

---

# 🤝 Contributions

Contributions, feature suggestions, and architecture improvements are welcome.

Please open:

* Issues
* Pull Requests
* Enhancement proposals

to contribute to the AgriNode ecosystem.

---

# 📜 License

MIT License

---

<div align="center">

# AgriNode Poultry Edge

### Industrial Smart Agriculture Edge Platform

Built with:

ESP32-S3 • FreeRTOS • PlatformIO • MQTT • Firebase • Embedded Systems Engineering

</div>

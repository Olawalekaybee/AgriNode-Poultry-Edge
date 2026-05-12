<div align="center">

# 🐓 AgriNode Poultry Edge

### Distributed Embedded IoT Architecture for Smart Poultry Environmental Monitoring

[![PlatformIO](https://img.shields.io/badge/PlatformIO-Embedded-orange?style=for-the-badge\&logo=platformio)](https://platformio.org/)
[![ESP32-S3](https://img.shields.io/badge/ESP32--S3-N16R8-blue?style=for-the-badge\&logo=espressif)](https://www.espressif.com/)
[![Firebase](https://img.shields.io/badge/Firebase-Realtime-yellow?style=for-the-badge\&logo=firebase)](https://firebase.google.com/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)]()

</div>

---

# 📖 Overview

AgriNode Poultry Edge is a professional distributed embedded IoT system designed for intelligent poultry farm environmental monitoring, cloud telemetry, and real-time dashboard visualization.

The project uses an **ESP32-S3 N16R8 Rev 1.1** as the primary edge controller and a dedicated **CYD 320×240 display node** communicating over I2C.

The system performs:

* 🌡 Indoor temperature & humidity monitoring
* 🌤 Outdoor temperature & humidity monitoring
* 💡 Light intensity sensing
* 📍 GPS location tracking
* 🕒 GPS date & time synchronization
* ☁ Firebase cloud telemetry upload
* 📺 Real-time dashboard visualization

---

# 🏗 System Architecture

<div align="center">

```txt
                    ┌─────────────────────┐
                    │ Firebase RealtimeDB │
                    └──────────┬──────────┘
                               │ WiFi
                               │
                     ┌─────────▼─────────┐
                     │ ESP32-S3 N16R8    │
                     │ Edge Controller   │
                     └─────────┬─────────┘
                               │
                        I2C Communication
                               │
                     ┌─────────▼─────────┐
                     │ CYD Display Node  │
                     │ ILI9341_2_DRIVER  │
                     └───────────────────┘
```

</div>

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

# ⚙ Main Hardware

| Component              | Purpose                        |
| ---------------------- | ------------------------------ |
| ESP32-S3 N16R8 Rev 1.1 | Main edge controller           |
| CYD 320×240 TFT        | Display dashboard node         |
| DHT22                  | Indoor temperature & humidity  |
| SHT31                  | Outdoor temperature & humidity |
| ADS1115                | Precision ADC                  |
| LDR                    | Light intensity sensing        |
| GPS Module             | Location, date & time          |

---

# 🧠 ESP32-S3 Edge Firmware

The ESP32-S3 firmware is responsible for:

* Sensor aggregation
* GPS telemetry
* Firebase communication
* I2C display communication
* Cloud upload scheduling
* Environmental data processing

## Interfaces

| Interface | Devices                     |
| --------- | --------------------------- |
| GPIO      | DHT22                       |
| I2C       | SHT31, ADS1115, CYD Display |
| UART      | GPS                         |
| WiFi      | Firebase                    |

---

# 📺 CYD Display Firmware

The CYD board functions as a dedicated visualization node.

## Responsibilities

* Receives telemetry packets over I2C
* Parses environmental sensor data
* Renders dashboard UI
* Displays real-time poultry conditions

## Display Driver

```txt
ILI9341_2_DRIVER
```

---

# 🔄 Communication Flow

```txt
Sensors
   ↓
ESP32-S3 Edge Node
   ↓ I2C JSON Packet
CYD Display Node
   ↓
Dashboard Rendering
```

---

# ☁ Firebase Telemetry

The ESP32-S3 uploads telemetry to Firebase Realtime Database.

## Example Payload

```json
{
  "indoor": {
    "temperature": 31.4,
    "humidity": 72.1
  },
  "outdoor": {
    "temperature": 29.8,
    "humidity": 68.3
  },
  "light": {
    "raw": 14320,
    "voltage": 1.79
  },
  "gps": {
    "valid": true,
    "latitude": 9.0765,
    "longitude": 7.3986,
    "satellites": 8
  }
}
```

---

# 🛠 Development Environment

| Tool              | Usage                    |
| ----------------- | ------------------------ |
| VS Code           | Development IDE          |
| PlatformIO        | Embedded build system    |
| Arduino Framework | ESP32 firmware framework |
| Firebase          | Cloud backend            |

---

# 🚀 Current Status

## ✅ ESP32-S3 Firmware

* Sensor acquisition implemented
* GPS telemetry implemented
* Firebase upload implemented
* I2C display bridge implemented
* Professional modular architecture implemented

## 🚧 CYD Display Firmware

* Project structure initialized
* I2C communication architecture prepared
* Dashboard renderer in progress

---

# 🧩 Planned Features

* 🔄 OTA firmware updates
* 📊 Advanced poultry analytics
* 🚨 Environmental threshold alerts
* 🧠 Edge AI monitoring
* 📡 Multi-node deployment
* 💾 Offline buffering
* 📱 Remote dashboard
* 🎨 LVGL graphical UI
* ⚙ GitHub CI/CD pipelines

---

# 🔒 Security

Sensitive credentials are excluded from Git tracking.

```gitignore
Secrets.h
.pio/
.vscode/
```

Never commit:

* WiFi credentials
* Firebase secrets
* API tokens
* Certificates

---

# 📜 License

MIT License

---

<div align="center">

### Built with ❤️ using ESP32-S3, PlatformIO, and Firebase

</div>

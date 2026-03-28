
---

# ESP32 Web-Based Relay Control System

Control home appliances from any browser on your local network using an ESP32 microcontroller. No cloud, no external server — just Wi-Fi.

---

## Overview

The ESP32 hosts a lightweight asynchronous web server that serves a toggle-switch interface. Any device on the same Wi-Fi network can visit the ESP32's IP address and flip relays on or off in real time — no app install required.

---

## Features

- Wi-Fi control with no external server dependency
- Mobile and desktop friendly web interface
- Real-time relay switching via async HTTP
- Configurable for 1, 2, or 4-channel relay modules
- Efficient asynchronous web server (ESPAsyncWebServer)

---

## Hardware Required

| Component | Notes |
|-----------|-------|
| ESP32 Development Board | Any standard dev board |
| Relay Module | 1, 2, or 4-channel |
| Jumper Wires | — |
| Power Supply | 5V recommended |

---

## Wiring

| ESP32 GPIO | Relay Module Pin |
|------------|------------------|
| GPIO 2 | IN1 |
| GPIO 4 | IN2 |
| GND | GND |
| 5V / VIN | VCC |

> **Safety:** Use relay modules with optocouplers for electrical isolation. Always test with low-voltage loads before connecting AC appliances. Never touch live wiring.

---

## Getting Started

### 1. Install Libraries

In Arduino IDE, install the following via Library Manager or manually:

- [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer)
- [`AsyncTCP`](https://github.com/me-no-dev/AsyncTCP)

### 2. Configure Wi-Fi Credentials

Open the sketch and update:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

### 3. Upload the Sketch

- Board: **ESP32 Dev Module**
- Baud rate: **115200**

Open the Serial Monitor after uploading. The ESP32 will print its assigned IP address once connected:

```
Connected. IP address: 192.168.1.100
```

### 4. Open the Web Interface

Visit the IP in any browser:

```
http://192.168.1.100
```

You'll see a page with toggle switches — one per relay.

---

## Configuration

### Number of Relays

```cpp
#define NUM_RELAYS 2
int relayGPIOs[NUM_RELAYS] = {2, 4};
```

### Relay Type

```cpp
#define RELAY_NO true   // true = Normally Open, false = Normally Closed
```

Set to `false` if your relay module is active-low (Normally Closed).

---

## Use Cases

- Smart home lighting and fan control
- Automated irrigation systems
- Remote power switching for equipment
- DIY home automation prototypes

---

## Possible Improvements

- MQTT integration for IoT platform support (Home Assistant, Node-RED)
- Internet access via cloud relay (Cloudflare Tunnel, ngrok)
- Voice control via Alexa or Google Home
- Scheduled on/off timers with NTP sync

---

## Safety Notes

- Do not touch live AC wiring while the circuit is powered
- Use relay modules that include optocoupler isolation
- Verify your relay module's coil voltage matches your power supply (typically 5V)
- Always prototype with low-voltage loads first

---

## License

MIT License — free to use, modify, and distribute.

---

## Contributing

Pull requests are welcome. For major changes, open an issue first to discuss what you'd like to change.

---

*Built with the ESP32 community and Arduino ecosystem.*

---

# 🌐 ESP32 Web-Based Relay Control System

Control your home appliances from a web browser using an ESP32 and relay modules. This project creates a simple web interface to switch devices ON/OFF over Wi-Fi.

---

## 🚀 Project Overview

This project uses an ESP32 microcontroller to host a web server that allows you to control relays remotely. Each relay can control an electrical appliance like lights, fans, or other devices.

The interface is accessible from any device connected to the same Wi-Fi network.

---

## ✨ Features

* 📡 Wi-Fi-based control (no external server needed)
* 🌍 Web interface (mobile & desktop friendly)
* ⚡ Real-time relay switching
* 🔁 Supports multiple relays
* 🧠 Asynchronous web server (fast & efficient)

---

## 🛠️ Components Required

* ESP32 Development Board
* Relay Module (1/2/4 channel)
* Jumper Wires
* Breadboard (optional)
* Power Supply

---

## 🔌 Circuit Connections

| ESP32 GPIO | Relay Module |
| ---------- | ------------ |
| GPIO 2     | IN1          |
| GPIO 4     | IN2          |
| GND        | GND          |
| 5V / VIN   | VCC          |

> ⚠️ **Important:**
>
> * Ensure your relay module voltage matches ESP32 (usually 5V relay with proper driver)
> * Be careful when working with high voltage appliances

---

## 📲 How It Works

1. ESP32 connects to your Wi-Fi network
2. It starts a web server on port 80
3. You open the ESP32 IP address in a browser
4. A web page with toggle switches appears
5. Toggling a switch sends a request to ESP32
6. ESP32 turns the relay ON/OFF

---

## 💻 Installation & Setup

### 1. Install Libraries

In Arduino IDE, install:

* `ESPAsyncWebServer`
* `AsyncTCP`

---

### 2. Configure Wi-Fi

Update your credentials in the code:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

### 3. Upload Code

* Select board: **ESP32 Dev Module**
* Upload the code
* Open Serial Monitor (115200 baud)

---

### 4. Access Web Interface

* After connecting, ESP32 prints an IP like:

```
192.168.1.100
```

* Open it in your browser:

```
http://192.168.1.100
```

---

## 📸 Web Interface Preview

* Clean UI with toggle switches
* Each switch controls one relay
* Works on mobile devices

---

## ⚙️ Configuration

### Change Number of Relays

```cpp
#define NUM_RELAYS 2
int relayGPIOs[NUM_RELAYS] = {2, 4};
```

---

### Relay Type

```cpp
#define RELAY_NO true
```

* `true` → Normally Open (NO)
* `false` → Normally Closed (NC)

---

## 🧪 Example Use Cases

* 💡 Home automation (lights, fans)
* 🌱 Smart irrigation systems
* 🔌 Remote power control
* 🏠 DIY smart home projects

---

## ⚠️ Safety Notes

* Do NOT touch live AC wires
* Use proper insulation
* Prefer relay modules with optocouplers
* Test with low voltage first

---

## 🔮 Future Improvements

* 📱 Mobile app integration (Blynk / MQTT)
* 🌐 Internet control (via cloud)
* 🗣️ Voice assistant integration (Alexa / Google)
* ⏱️ Scheduling & timers

---

## 🤝 Contributing

Feel free to fork this repo and submit pull requests!

---

## 📜 License

This project is open-source and available under the MIT License.

---

## 🙌 Acknowledgements

* ESP32 community
* Arduino ecosystem

---

## 👨‍💻 Author

**Your Name Here**

---

⭐ If you like this project, don’t forget to star the repo!

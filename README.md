
# IoT-Based Gas & Temperature Monitoring System

![Project Banner](https://your-image-link.com/banner.png)

## 🚀 Project Overview
This project is an IoT-based **Gas & Temperature Monitoring System** using **ESP8266, MQ-5 Gas Sensor, DHT11 Temperature Sensor, and Firebase Realtime Database**. The system continuously monitors gas levels, temperature, and humidity, displaying real-time data on a web dashboard.

## 📌 Features
- 🔥 **Real-time Monitoring:** Captures gas levels, temperature, and humidity using sensors.
- 📡 **Cloud Storage:** Sends sensor data to **Firebase Realtime Database**.
- 🚨 **Alerts & Notifications:** Alerts when gas levels exceed safe limits.
- 🛠 **Easy Deployment:** Simple setup using ESP8266 with Arduino IDE.

---

## 🛠️ Hardware Requirements
- **ESP8266 NodeMCU** – WiFi-enabled microcontroller.
- **MQ-5 Gas Sensor** – Detects gas levels.
- **DHT11 Sensor** – Measures temperature and humidity.
- **Buzzer** – Alerts when gas levels exceed safe limits.
- **Jumper Wires & Breadboard** – For circuit connections.

---

## 🔧 Software & Libraries
- **Arduino IDE** – Programming ESP8266.
- **Firebase ESP8266 Client** – For Firebase communication.
- **DHT Sensor Library** – For reading temperature and humidity.
- **ESP8266WiFi Library** – For WiFi connectivity.

---

## 📷 Project Screenshots
### 1️⃣ **Circuit Diagram**
![Circuit Diagram](https://your-image-link.com/circuit.png)

#### **Circuit Connections**
- **DHT11 Sensor**
  - VCC → **3.3V**
  - GND → **GND**
  - Data Pin → **D4**
- **MQ-5 Gas Sensor**
  - VCC → **3.3V**
  - GND → **GND**
  - Analog Output → **A0**
- **Buzzer**
  - Positive → **D2**
  - Negative → **GND**

### 2️⃣ **Live Dashboard UI**
![Web Dashboard](https://your-image-link.com/dashboard.png)

---

## 🚀 Installation & Setup
Follow these steps to set up the **IoT-Based Gas & Temperature Monitoring System**:

### 1️⃣ **Clone the Repository**
```bash
 git clone https://github.com/cygnodweb/real-time-gas-temp-sensor
 cd real-time-gas-temp-sensor
```

### 2️⃣ **Set Up Firebase**
1. Go to [Firebase Console](https://console.firebase.google.com/).
2. Create a new project and enable **Realtime Database**.
3. Get the **Database URL** and **Authentication Key**.

### 3️⃣ **Upload Code to ESP8266**
1. Open `iot_project.ino` in **Arduino IDE**.
2. Install required libraries:
   - Firebase ESP8266 Client
   - DHT Sensor Library
3. Update WiFi and Firebase credentials in the code:
   ```cpp
   #define WIFI_SSID "YOUR_WIFI_SSID"
   #define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
   #define FIREBASE_HOST "YOUR_FIREBASE_HOST"
   #define FIREBASE_AUTH "YOUR_FIREBASE_AUTH_KEY"
   ```
4. Select **NodeMCU 1.0 (ESP-12E Module)** and Upload.

## 📎 Project Links
- 🔗 **GitHub Repo:** [real-time-gas-temp-sensor](https://github.com/cygnodweb/real-time-gas-temp-sensor)
- 🛠 **Firebase Console:** [Firebase](https://console.firebase.google.com/)

---

## 📜 License
This project is open-source and licensed under the **MIT License**.

---

## 🛠 Future Improvements
- 📱 **Mobile App** – Extend functionality to a mobile app.
- 📈 **Historical Data** – Store sensor logs for analysis.
- 📢 **SMS/Email Alerts** – Send notifications for critical gas levels.

🚀 *Feel free to contribute and improve this project!*


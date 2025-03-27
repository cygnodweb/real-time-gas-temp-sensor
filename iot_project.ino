#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define WIFI_SSID "Your wifi ssid"               // WiFi SSID
#define WIFI_PASSWORD "Your passwrd"       // WiFi Password
#define FIREBASE_HOST "Your firebase host url"  // Firebase Host
#define FIREBASE_AUTH "Your auth key"  // Firebase Auth Key

#define DHTPIN D4                       // DHT11 sensor connected to NodeMCU D4 (GPIO2)
#define DHTTYPE DHT11
#define MQ5_PIN A0                      // MQ-5 gas sensor connected to NodeMCU Analog Pin (A0)
#define BUZZER_PIN D3                   // Buzzer connected to NodeMCU D3 (GPIO0)

DHT dht(DHTPIN, DHTTYPE);
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD I2C address 0x27, 16x2 LCD

void setup() {
    Serial.begin(115200);
    pinMode(BUZZER_PIN, OUTPUT);
    dht.begin();
    lcd.begin();
    lcd.backlight();  // Turn on LCD backlight

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected to WiFi");

    // Configure Firebase
    config.host = FIREBASE_HOST;
    config.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
}

void loop() {
    // Read temperature, humidity, and gas sensor values
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int gasValue = analogRead(MQ5_PIN);

    // Check if any sensor reading failed
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Print sensor data to Serial Monitor
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Gas Level: ");
    Serial.println(gasValue);

    // Send data to Firebase
    if (Firebase.setFloat(firebaseData, "/sensor/temperature", temperature) &&
        Firebase.setFloat(firebaseData, "/sensor/humidity", humidity) &&
        Firebase.setInt(firebaseData, "/sensor/gas", gasValue)) {
        Serial.println("Data sent to Firebase");
    } else {
        Serial.println("Failed to send data: " + firebaseData.errorReason());
    }

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: " + String(temperature) + "C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: " + String(humidity) + "%");

    // Gas leak detection and buzzer alert
    if (gasValue > 400) {  // Adjust threshold based on environment
        digitalWrite(BUZZER_PIN, HIGH);  // Activate buzzer
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Gas Leak!");
        lcd.setCursor(0, 1);
        lcd.print("Danger!");
        Serial.println("Gas Leak Detected!");
    } else {
        digitalWrite(BUZZER_PIN, LOW);  // Deactivate buzzer
    }

    delay(2000);  // Wait for 2 seconds before the next reading
}

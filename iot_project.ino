#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT.h>

#define WIFI_SSID "Your_wifi_ssid"  // Updated WiFi SSID
#define WIFI_PASSWORD "Your_wifi_password"  // Updated WiFi Password

#define FIREBASE_HOST "Your firebase host url"  // Updated Firebase Host
#define FIREBASE_AUTH "firebase auth key"  // Updated Firebase Auth Key

#define DHTPIN D4  // DHT11 sensor connected to NodeMCU D4 (GPIO2)
#define DHTTYPE DHT11
#define MQ5_PIN A0  // MQ-5 gas sensor connected to NodeMCU Analog Pin (A0)
#define BUZZER_PIN D3  // Buzzer connected to NodeMCU D3 (GPIO0)

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    pinMode(BUZZER_PIN, OUTPUT);
    dht.begin();
    
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
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int gasValue = analogRead(MQ5_PIN);

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.print("%, Gas Level: ");
    Serial.println(gasValue);

    // Send data to Firebase
    if (Firebase.setFloat(firebaseData, "/sensor/temperature", temperature) &&
        Firebase.setFloat(firebaseData, "/sensor/humidity", humidity) &&
        Firebase.setInt(firebaseData, "/sensor/gas", gasValue)) {
        Serial.println("Data sent successfully");
    } else {
        Serial.println("Failed to send data: " + firebaseData.errorReason());
    }

    // Buzzer alert if gas level exceeds threshold
    if (gasValue > 400) {  // Adjust threshold based on environment
        digitalWrite(BUZZER_PIN, HIGH);
        Serial.println("Gas leak detected! Buzzer activated.");
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }

    delay(2000);  // Wait 5 seconds before next reading
}
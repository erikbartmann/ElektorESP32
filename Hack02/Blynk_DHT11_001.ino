#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define DHTPIN 19     // DHT-Pin
#define DHTTYPE DHT11 // DHT-Type

char auth[] = "<Token>";        // Auth-Token
char ssid[] = "<SSID>";         // WiFi-SSiD
char pass[] = "<Password>";     // WiFi-Passwort

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void setup() {
  Serial.begin(115200); // Serial-Monitor
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendSensor() {
  float h = dht.readHumidity();    // Feuchtigkeit lesen
  float t = dht.readTemperature(); // Temperatur lesen
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h); // Versenden des Feuchtigkeitswertes
  Blynk.virtualWrite(V6, t); // Versenden des Temperaturwertes
}

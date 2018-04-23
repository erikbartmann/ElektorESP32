#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>           
#include <DallasTemperature.h>

const char* ssid        = "<SSID>";
const char* password    = "<Password>";
const char* mqtt_server = "192.168.178.24";
const char* topic1       = "/arbeitszimmer/temperatur1";
const char* topic2       = "/arbeitszimmer/temperatur2";
const int   RATE        = 5000;
#define ONE_WIRE_BUS 9  // DS18B20-Pin - IO 9

WiFiClient espClient;           // WiFi-Client Objekt
PubSubClient client(espClient); // PubSubClient Objekt
OneWire oneWire(ONE_WIRE_BUS);  // One-Wire initialisieren
DallasTemperature sensors(&oneWire); // One-Wire Referenz an Dallas übergeben

long lastMsg = 0;     // Wird für Timer verwendet

void setup() {
  Serial.begin(9600); // Init Serial-Monitor
  WiFiInit();         // Init WiFi
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  sensors.begin();    // Dallas-Bibliothek starten
}

void WiFiInit() {
  delay(10); // Kurze Pause
  Serial.print("\n\nVerbindungsaufnahem zu: ");
  Serial.println(ssid);       // Ausgabe SSID
  WiFi.begin(ssid, password); // WiFi starten
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nMit WiFi verbunden");
  Serial.print("IP Adresse: ");
  Serial.println(WiFi.localIP()); // Ausgabe IP-Adresse
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Nachricht eingegangen [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Starte MQTT-Verbindung...");
    if (client.connect("ESP32Client")) {
      Serial.println("verbunden");
      client.publish(topic1, "Ich lebe!"); // Kurzes Lebenszeichen
      client.subscribe(topic1); // Subcription des Topics
      client.publish(topic2, "Ich lebe!"); // Kurzes Lebenszeichen
      client.subscribe(topic2); // Subcription des Topics
    } else {
      Serial.print("Fehler, rc=");
      Serial.print(client.state());
      Serial.println(" versuche es in 5 Sekunden erneut");
      delay(5000); // 5 Sekunden Pause bevor neuer Versuch
    }
  }
}

void loop() {
  char msg1[100];          // Wird für Publishing-Nachricht 1 verwendet
  char msg2[100];          // Wird für Publishing-Nachricht 2 verwendet
  char temperaturIndex[2]; // Wird für Temperatur-Index verwendet
  float temperatur1;        // Speichert Temperaturwert 1
  float temperatur2;        // Speichert Temperaturwert 2
  if (!client.connected()) { reconnect(); }
  client.loop();
  long now = millis();
  // Nachricht im 5 Sekundentakt übermitteln
  if (now - lastMsg > RATE) {
    lastMsg = now;
    // Temperaturmessung anfordern
    sensors.requestTemperatures();
    temperatur1 = sensors.getTempCByIndex(0);
    temperatur2 = sensors.getTempCByIndex(1);
    // Umwandlung float -> char[], 2 Vor- und 2 Nachkommastellen
    dtostrf(temperatur1, 2, 2, msg1); 
    dtostrf(temperatur2, 2, 2, msg2);
    client.publish(topic1, msg1);
    client.publish(topic2, msg2);
  }
}

#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>           
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 9  // DS18B20-Pin - IO9
const char* ssid        = "<SSID>";
const char* password    = "<Password>";
const char* mqtt_server = "192.168.178.24";
const char* topic       = "/arbeitszimmer/temperatur";
const int   RATE        = 5000;

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
    if (client.connect("ESP8266Client")) {
      Serial.println("verbunden");
      client.publish(topic, "Ich lebe!"); // Kurzes Lebenszeichen
      client.subscribe(topic); // Subcription des Topics
    } else {
      Serial.print("Fehler, rc=");
      Serial.print(client.state());
      Serial.println(" versuche es in 5 Sekunden erneut");
      delay(5000); // 5 Sekunden Pause bevor neuer Versuch
    }
  }
}

void loop() {
  char msg[100];           // Wird für Publishing-Nachricht verwendet
  float temperatur;        // Speichert Temperaturwert
  if (!client.connected()) { reconnect(); }
  client.loop();
  long now = millis();
  // Nachricht im 5 Sekundentakt übermitteln
  if (now - lastMsg > RATE) {
    lastMsg = now;
    // Temperaturmessung anfordern
    sensors.requestTemperatures();
    temperatur = sensors.getTempCByIndex(0);
    // Umwandlung float -> char[], 2 Vor- und 2 Nachkommastellen
    dtostrf(temperatur, 2, 2, msg);
    client.publish(topic, msg);
  }
}

#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid        = "<SSID>";
const char* password    = "<Password>";
const char* mqtt_server = "<IP-Adresse MQTT-Server>";
const char* topic       = "/arbeitszimmer/temperatur";
const int   RATE        = 5000;

WiFiClient espClient;           // WiFi-Client Objekt
PubSubClient client(espClient); // PubSubClient Objekt

long lastMsg = 0;     // Wird für Timer verwendet
int counter = 0;      // Zähler

void setup() {
  Serial.begin(9600); // Init Serial-Monitor
  WiFiInit();         // Init WiFi
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
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
  if (!client.connected()) { reconnect(); }
  client.loop();
  long now = millis();
  char msg[100];        // Wird für Nachricht verwendet
  // Nachricht im 5 Sekundentakt übermitteln
  if (now - lastMsg > RATE) {
    lastMsg = now;
    ++counter;
    snprintf(msg, 75, "Hello world #%ld", counter);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(topic, msg);
  }
}

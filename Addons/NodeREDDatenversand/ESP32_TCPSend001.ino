#include <WiFi.h>
const char* ssid     = "<SSID>";
const char* password = "<Passwort>";

const char* server = "192.168.178.27"; // IP-Adresse des Node-RED-Servers
const int port = 8088; // Port
unsigned long previousMillis = 0; // Letzter Update-Zeitstempel
const long interval = 1000;       // Sende-Intervall in ms

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected to IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("Connecting to ");
    Serial.println(server);
    WiFiClient client; // Für TCP-Connection
    
    if (!client.connect(server, port)) {
        Serial.println("Connection failed");
        return;
    }
    int analogValue = analogRead(32);
    Serial.println(analogValue);
    client.print(analogValue); // Sende Daten zum Server
    client.stop();
  }
}

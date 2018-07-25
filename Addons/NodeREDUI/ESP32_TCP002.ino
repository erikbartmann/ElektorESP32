#include <WiFi.h>
#define MSG 50 // Maximale Länge der Nachricht
const char* ssid     = "<SSID>";
const char* password = "<Passwort>";
int pinArray[] = {19, 23, 18, 5}; // IO-Pins

WiFiServer server(8088); // Server hört auf Port 8088

void setup() {
  for(int i=0; i<4; i++) pinMode(pinArray[i], OUTPUT);
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
  server.begin(); // Server starten
}

void loop() {
  String msg = ""; // Nachricht
  // Auf einen neuen Client warten
  WiFiClient client = server.available();
  uint8_t data[MSG];
  if (client) {
    Serial.println("New client");
    // Prüfen, ob Client verbunden
    while (client.connected()) {
      if (client.available()) {
        int len = client.read(data, MSG);
        if (len < MSG) data[len] = '\0';
        else data[MSG] = '\0';
        Serial.print("Clients message: ");
        msg = (char *)data;
        Serial.println(msg);
        evalMessage(msg);
      }
    }
  }
}

void evalMessage(String msg) {
  int pos = msg.indexOf(':');
  int pin = msg.substring(0, pos).toInt();
  int status = msg.substring(pos + 1).toInt();
  Serial.println(pin);
  Serial.println(status);
  digitalWrite(pin, status);
}

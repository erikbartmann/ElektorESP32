#include <WiFi.h>
#define MSG 50 // Maximale Länge der Nachricht
const char* ssid     = "<SSID>";
const char* password = "<Passwort>";

WiFiServer server(8088); // Server hört auf Port 8088

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
      }
    }
  }
}

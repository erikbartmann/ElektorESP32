#include <WiFi.h>
const char* ssid     = "<SSID>";
const char* password = "<Password>";

WiFiServer server(80); // Webserver-Objekt (Port 80)

void setup() {
  Serial.begin(9600); // Init Serial-Monitor
  Serial.print("Verbindungsaufnahme zu SSID:  ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); delay(500);
  }
  Serial.println();
  Serial.println("WiFi-Verbindung ok.");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());
  server.begin(); // Starte Server
}

void loop() {
  WiFiClient client = server.available(); // Lauscht auf neue Clientanfragen
  if (client) {                           // falls ein Client anfragt
    Serial.println("Neuer Client.");      // erfolgt eine Nachricht im Serial-Monitor
    String currentLine = "";              // Variable für die Client-Daten
    while (client.connected()) {          // Schleife, solange Client verbunden
      if (client.available()) {           // Sind Daten zum Lesen vorhanden
        char c = client.read();           // dann wird ein Byte gelesen
        Serial.write(c);                  // Ausgabe im Serial-Monitor
        if (c == '\n') {                  // Wenn Byte ist ein Zeilenumbruch...
          if (currentLine.length() == 0) {
            // HTTP-Header starten immer mit dem Response Code (HTTP/1.1 200 OK)
            // und dem Content-Type gefolgt von einer Leerzeile
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Hier kommt die Nachricht an den Webbrowser
            client.print("Hallo ESP32-Freunde!<br>");
            client.print("Das ist eine einfache Webseite.<br>");
            // Der HTTP-Response endet mit einer Leerzeile
            client.println();
            break; // Die Loop wird verlassen
          } else { // falls eine neue Zeile kommt, wird die alte gelöscht
            currentLine = "";
          }
        } else if (c != '\r') { // Alles, was nicht Carriage Return ist,
          currentLine += c;     // wird am Ende der currentLine hinzugefügt
        }
      }
    }
    client.stop(); // Schließe Verbindung
    Serial.println("Client-Verbindung geschlossen.");
  }
}

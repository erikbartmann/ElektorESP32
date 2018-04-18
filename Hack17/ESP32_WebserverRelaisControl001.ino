#include <WiFi.h>
const char* ssid     = "SSID";
const char* password = "Password";
String request       = ""; // HTTP-Request
byte relayArray[] = {21, 22, 19, 23}; // Pin-Array

WiFiServer server(80); // Webserver-Objekt (Port 80)

void setup() {
  Serial.begin(9600); // Init Serial-Monitor
  for (int i = 0; i < 4; i++) {
    pinMode(relayArray[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(relayArray[i], HIGH);
  }

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
        request += c;                     // HTTP-Request
        if (c == '\n') {                  // Wenn Byte ist ein Zeilenumbruch...
          if (currentLine.length() == 0) {
            // HTTP-Header starten immer mit dem Response Code (HTTP/1.1 200 OK)
            // und dem Content-Type gefolgt von einer Leerzeile
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // GPIO-Ansteuerung
            ledControl(request);
            // Bootstrap-Resource einbinden
            client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>");
            client.println("<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script>");
            client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>");
            // Hier kommen die LED-Botton
            client.println("<h1>Relais-Control</h1>");
            client.println("  Relais 1: ");
            client.println("<div class='btn-group'>");
            client.println("<a href='/21/ON' class='btn btn-success'>On</a>");
            client.println("<a href='/21/OFF' class='btn btn-danger'>Off</a>");
            client.println("</div><br />");
            client.println("  Relais 2: ");
            client.println("<div class='btn-group'>");
            client.println("<a href='/22/ON' class='btn btn-success'>On</a>");
            client.println("<a href='/22/OFF' class='btn btn-danger'>Off</a>");
            client.println("</div><br />");
            client.println("  Relais 3: ");
            client.println("<div class='btn-group'>");
            client.println("<a href='/19/ON' class='btn btn-success'>On</a>");
            client.println("<a href='/19/OFF' class='btn btn-danger'>Off</a>");
            client.println("</div><br />");
            client.println("  Relais 4: ");
            client.println("<div class='btn-group'>");
            client.println("<a href='/23/ON' class='btn btn-success'>On</a>");
            client.println("<a href='/23/OFF' class='btn btn-danger'>Off</a>");
            client.println("</div><br />");
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
    request = "";  // HTTP-Request leeren
    client.stop(); // Schließe Verbindung
    Serial.println("Client-Verbindung geschlossen.");
  }
}

void ledControl(String setLED) {
  int pos1 = setLED.indexOf('/') + 1;
  int pos2 = setLED.indexOf('/', pos1 + 1);
  int pin = setLED.substring(pos1, pos2).toInt();
  String status = setLED.substring(pos2 + 1, setLED.indexOf(' ', 5));
  digitalWrite(pin, !(status == "ON" ? HIGH : LOW));
}

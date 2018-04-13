#include <WiFi.h>
#include <ArduinoJson.h>
#define ROT 21
#define GRUEN 22
#define BLAU 19

const char* ssid     = "Highli";
const char* password = "TreCronLap0_78";

//open weather map api key
String apiKey = "3c78cde49e9a31791ac7b82dc0f4c254";
char server[] = "api.openweathermap.org";
String location = "Cologne,DE";

WiFiClient client; // WiFi-Client
StaticJsonBuffer<5000> jsonBuffer; // JSON-Buffer erstellen

void setup() {
  pinMode(ROT, OUTPUT);
  pinMode(GRUEN, OUTPUT);
  pinMode(BLAU, OUTPUT);
  RGBLED(HIGH, HIGH, HIGH); // Alle aus
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  getWeather(); // Wetterdaten abrufen
}

void loop() { /* ... */ }

void getWeather() {
  client.stop();
  Serial.println("\nConnection to server...");
  // Wenn Verbindung -> Serverdaten abrufen
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // HTTP Request starten
    client.print("GET /data/2.5/weather?");
    client.print("q=" + location);
    client.print("&appid=" + apiKey);
    client.println("&units=metric");
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ESP32WiFi/1.1");
    client.println("Connection: close");
    client.println();
  } else Serial.println("Unable to connect");
  delay(1000);
  String line = ""; // Variable zur Antwortspeicherung
  while (client.connected()) {
    line = client.readStringUntil('\n');
    JsonObject& root = jsonBuffer.parseObject(line);
    if (!root.success()) {
      Serial.println("parseObject() failed");
      return;
    }
    // Daten vom JSON-Tree abrufen
    JsonArray& list = root["list"];
    String city = root["name"];
    float tempNow = root["main"]["temp"];
    float tempMin = root["main"]["temp_min"];
    float tempMax = root["main"]["temp_max"];
    float humidityNow = root["main"]["humidity"];
    String weatherNow = root["weather"][0]["description"];
    calculate(tempNow); // RGB-Ansteuern
    Serial.print("Rohdaten:"); 
    Serial.println(line);
    Serial.print("Stadt: "); Serial.println(city);
    Serial.print("Temp: "); Serial.println(tempNow);
    Serial.print("Temp (Min): "); Serial.println(tempMin);
    Serial.print("Temp (Max): "); Serial.println(tempMax);
    Serial.print("Feuchtigkeit: "); Serial.println(humidityNow);
    Serial.print("Wetter: "); Serial.println(weatherNow);
  }
}

void RGBLED(boolean r, boolean g, boolean b) {
  digitalWrite(ROT, r);
  digitalWrite(GRUEN, g);
  digitalWrite(BLAU, b);
}

void calculate(float t) {
  if(t < 5.0) RGBLED(LOW, HIGH, HIGH); // Rot
  if((t >= 5.0) && (t <= 20.0)) RGBLED(HIGH, HIGH, LOW); // Blau
  if(t > 20.0) RGBLED(HIGH, LOW, HIGH); // Grün
}


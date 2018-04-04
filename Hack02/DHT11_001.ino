#include "DHT.h"  // DHT Bibliothek einbinden
#include "Wire.h" // Wire Bibliothek einbinden
#include "LiquidCrystal_I2C.h" // LiquidCrystal_I2C Bibliothek einbinden
#define DHTPIN 19 // DHT11-Pin

// Welcher DHT-Typ wird verwendet
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin(); // DHT initialisieren
  lcd.begin(); // LCD initialisieren
}

void loop() {
  delay(2000); // Kurze Pause
  float h = dht.readHumidity();    // Feuchtigkeit ermitteln
  float t = dht.readTemperature(); // Temperatur ermitteln
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Temp:");

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print("\337"); // Grad-Zeichen
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(h);
  lcd.print("%");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("*C ");
}

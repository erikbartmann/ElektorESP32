#include <OneWire.h>           // One-Wire-Bibliothek einbinden
#include <DallasTemperature.h> // Dallas-Bibliothek einbinden
#define ONE_WIRE_BUS 9         // DS18B20-Pin IO 9

// One-Wire initialisieren 
OneWire oneWire(ONE_WIRE_BUS);
// One-Wire Referenz an Dallas übergeben
DallasTemperature sensors(&oneWire); 
 
void setup() {
  Serial.begin(9600); // Init Serial-Monitor
  sensors.begin();    // Dallas-Bibliothek starten
}
  
void loop() {
  // Temperaturmessung anfordern
  sensors.requestTemperatures();
  // Ausgabe-Text für Sensor #1
  Serial.print("Temperatur Sensor #1: ");
  // Temperatur von Sensor #1 ausgeben
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" Grad Celsius");
}

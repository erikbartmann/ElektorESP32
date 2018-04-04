#include <Wire.h>              // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // I2C Bibliothek einbinden
#define Taster 19              // Taster-Pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C-Adresse und Format festlegen

void setup() {
  pinMode(Taster, INPUT); // Pin als INPUT
  lcd.begin(); // Die Initialisierung des LCD
}

void loop() {
   byte tasterStatus = digitalRead(Taster); // Taster-Status lesen
   lcd.setCursor(0, 0); // Cursor auf Spalte, Zeile positionieren
   lcd.print("*ESP32 Pico-V4*");
   lcd.setCursor(0, 1); // Cursor auf Spalte, Zeile positionieren
   if(tasterStatus == HIGH)
     lcd.print("Taster: HIGH"); // lcd.print zeigt Text an
   else
     lcd.print("Taster: LOW "); // lcd.print zeigt Text an
}

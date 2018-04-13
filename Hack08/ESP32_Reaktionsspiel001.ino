#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LEDRot   19 // LED-Pin Rot
#define LEDGelb  23 // LED-Pin Gelb
#define LEDGruen 18 // LED-Pin Grün
#define Taster    5 // Taster-Pin

LiquidCrystal_I2C lcd(0x27, 16, 2);
volatile bool ledGruenStatus = false;
volatile bool buttonPressed = false;
unsigned long actualTime;

void setup() {
  pinMode(LEDRot,   OUTPUT); // LED-Pin als Ausgang
  pinMode(LEDGelb,  OUTPUT); // LED-Pin als Ausgang
  pinMode(LEDGruen, OUTPUT); // LED-Pin als Ausgang
  pinMode(Taster,   INPUT);  // Taster-Pin als Eingang
  attachInterrupt(digitalPinToInterrupt(Taster), ISR, RISING);
  LED(false, false, false); // Alle LEDs aus
  lcd.begin(); lcd.setCursor(0,0);
  lcd.print("*Reaktionsspiel*");
}

void ISR() {
  if (!buttonPressed) {
    if (ledGruenStatus) {
      unsigned long interruptTime = millis();
      double reactionTime = (interruptTime - actualTime) / 1000.0;
      buttonPressed = true;
      lcd.setCursor(0,1);
      lcd.print("Zeit: " + (String)reactionTime + "s");
    } else {
      lcd.setCursor(0,1);
      lcd.print("Zu frueh!!!");
      buttonPressed = true;
    }
  }
}

void loop() {
  if (!ledGruenStatus) {
    // Phase rot
    LED(true, false, false); delay(2000);
    // Phase rot / gelb
    LED(true, true, false);  delay(2000);
    ledGruenStatus = true;
    actualTime = millis();
    // Phase grün
    LED(false, false, true);
  }
}

void LED(bool rot, bool gelb, bool gruen) {
  digitalWrite(LEDRot, rot);
  digitalWrite(LEDGelb, gelb);
  digitalWrite(LEDGruen, gruen);
}

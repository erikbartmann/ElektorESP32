#include "Motor.h"  // Motor-Klasse einbinden
#include "Keypad.h" // Keypad-Klasse einbinden
#define ROWS 4      // Anzahl der Keypad-Reihen
#define COLS 4      // Anzahl der Keypad-Spalten
#define SoundPin 10 // Piezo-Buzzer
#define STEPS 10    // Anzahl der möglichen Aktionen
#define FAHRAUER 700 // Fahrdauer der Aktion 
#define FAHRGESCHWINDIGKEIT 180 // Fahrgeschwindigkeit
#define DREHDAUER 8 // Drehdauer der Aktion
#define DREHGESCHWINDIGKEIT 180 // Drehgeschwindigkeit

Motor meinMotor; // Objekt-Erstellung

char keys[ROWS][COLS] =
{
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'G', 'P'},
  {'U', 'D', 'L', 'R'}
};

byte rowPins[] = {25, 26, 32, 33}; // Row1, Row2, Row3, Row4
byte colPins[] = {27, 14, 12, 13}; // Col1, Col2, Col3, Col4
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte ToneCMD = 0, ToneDigit = 3;
byte mode, digCount;       // Neede for storing mode and Key-Press count
String actionValue;        // Stores the action-value
String actionStep[STEPS];  // Array for storing actions
int stepCounter;           // Couns action-steps
byte keyValue;             // Stored the keyValue

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(SoundPin, OUTPUT);
  clearActionSteps(STEPS);
}

void loop() {
  char keyPressed = myKeypad.getKey();
  if (keyPressed != NO_KEY) {
    if (keyPressed == 'G') {
      if ((mode == 1) && (actionValue.length() > 2) && (stepCounter < STEPS)) {
        Serial.println("Step added to Array");
        actionStep[stepCounter] = actionValue; // Füge Schritt zu actionStep-Array hinzu
        digCount = 0;
        actionValue = "A";
        actionValue += keyPressed;
        makeSound(tones[ToneCMD], 200);
        Serial.println(actionValue);
        delay(500);
        playMelody();
        action();
      }
    }
    if ((keyPressed == 'L') || (keyPressed == 'R') || 
        (keyPressed == 'U') || (keyPressed == 'D') || 
        (keyPressed == 'P')) {
      Serial.println("CMD");
      if (mode == 0) {
        actionValue += keyPressed;
        mode = 1;
        makeSound(tones[ToneCMD], 200);
        Serial.println("ActionValue1: " + actionValue);
      }

      if ((mode == 1) && (actionValue.length() > 2) && (stepCounter < STEPS)) {
        Serial.println("Schritt zum Array hinzugefuegt");
        actionStep[stepCounter++] = actionValue; // Füge Schritt zu actionStep-Array hinzu
        digCount = 0;
        actionValue = "A";
        actionValue += keyPressed;
        makeSound(tones[ToneCMD], 200);
        Serial.println(actionValue);
      }
    } else if ((mode == 1) && (digCount < 3)) {
      if ((keyPressed == '0') || (keyPressed == '1') || 
          (keyPressed == '2') || (keyPressed == '3') || 
          (keyPressed == '4') || (keyPressed == '5') || 
          (keyPressed == '6') || (keyPressed == '7') || 
          (keyPressed == '8') || (keyPressed == '9')) {
        Serial.println("Nummer");
        actionValue += keyPressed;
        digCount++; // Increase Digit-Count
        makeSound(tones[ToneDigit], 200);
      }
      Serial.println("ActionValue3: " + actionValue);
    }
    printSteps();
  }
}

void BotMove(String botDirection, int botDuration) {
  Serial.println(botDuration);
  if(botDirection == "U") { // Vorwärts fahren
    meinMotor.move(FORWARD, botDuration * FAHRAUER, FAHRGESCHWINDIGKEIT);
  }
  if(botDirection == "D") { // Rückwärts fahren
    meinMotor.move(BACKWARD, botDuration * FAHRAUER, FAHRGESCHWINDIGKEIT);
  }
  if(botDirection == "R") { // Rechts drehen
    meinMotor.move(RIGHT, botDuration * DREHDAUER, DREHGESCHWINDIGKEIT);
  }
  if(botDirection == "L") { // Links drehen
    meinMotor.move(LEFT, botDuration * DREHDAUER, DREHGESCHWINDIGKEIT);
  }
  if(botDirection == "P") { // Pause
    delay(1000 * botDuration);
  }
  delay(300); // Kurze Pause
}

void makeSound(int t, int d) {
  for (long i = 0; i < d * 1000L; i += t * 2) {
    digitalWrite(SoundPin, HIGH);
    delayMicroseconds(t);
    digitalWrite(SoundPin, LOW);
    delayMicroseconds(t);
  }
}

void playMelody(void) {
  makeSound(tones[0], 200);
  makeSound(tones[1], 200);
  makeSound(tones[2], 200);
  makeSound(tones[3], 200);
  makeSound(tones[1], 400);
  makeSound(tones[1], 400);
}

void clearActionSteps(int steps) {
  mode = 0;
  digCount = 0;
  stepCounter = 0;
  actionValue = "A";
  for (int i = 0; i < steps; i++)
    actionStep[i] = "."; // Leerer Schritt
}

void printSteps(void) {
  Serial.println("=============");
  for (int i = 0; i < STEPS; i++) {
    Serial.println(actionStep[i]);
  }
}

void action(void) {
  Serial.println("Action");
  printSteps();
  String action;
  int actionValue;
  for (int i = 0; i < STEPS; i++) {
    if (actionStep[i] != ".") {
      action = actionStep[i].substring(1, 2);
      actionValue = actionStep[i].substring(2).toInt();
      BotMove(action, actionValue);
    }
  }
  playMelody();             // Spiele Melodie
  clearActionSteps(STEPS);  // Lösche alle Schritte
}


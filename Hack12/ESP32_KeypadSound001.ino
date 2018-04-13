#include "Keypad.h"
#define ROWS 4
#define COLS 4
#define SoundPin 25  // Piezo-Pin
#define Duration 250 // Tonlänge

char keys[ROWS][COLS] =
{
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'a', 'b'},
  {'c', 'd', 'e', 'f'}
};

byte rowPins[] = {18,  5, 10,  9}; // Row1, Row2, Row3, Row4
byte colPins[] = {23, 19, 22, 21}; // Col1, Col2, Col3, Col4
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(SoundPin, OUTPUT);
}

void loop() {
  char keyPressed = myKeypad.getKey();
  if(keyPressed != NO_KEY) {
    int keyValue = (int)keyPressed -49; // ASCI -> Wert minus 49
    if((keyValue >=0) && (keyValue < 8)) makeSound(tones[keyValue], Duration);
  }
}

void makeSound(int t, int d) {
  for (long i = 0; i < d * 1000L; i += t * 2) {
    digitalWrite(SoundPin, HIGH);
    delayMicroseconds(t);
    digitalWrite(SoundPin, LOW);
    delayMicroseconds(t);
  }
}

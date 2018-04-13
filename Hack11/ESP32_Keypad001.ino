#include "Keypad.h"
#define ROWS 4
#define COLS 4

char keys[ROWS][COLS] =
{
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', '0', 'a', 'b'},
  {'c', 'd', 'e', 'f'}
};

byte rowPins[] = {18,  5, 10,  9}; // Row1, Row2, Row3, Row4
byte colPins[] = {23, 19, 22, 21}; // Col1, Col2, Col3, Col4

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char keyPressed = myKeypad.getKey();
  if(keyPressed != NO_KEY)
    Serial.println(keyPressed);
}

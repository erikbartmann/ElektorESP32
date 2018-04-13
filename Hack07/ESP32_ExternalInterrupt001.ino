#define LED    21 // LED-Pin
#define Taster 22 // Taster-Pin

volatile bool LEDStatus = false; // LED-Status

void setup() {
  pinMode(LED, OUTPUT); // LED-Pin als Ausgang
  pinMode(Taster, INPUT); // Taster-Pin als Eingang
  attachInterrupt(digitalPinToInterrupt(Taster), toggle, CHANGE);
}

void loop() { /* leer */ }

void toggle() {
   LEDStatus = !LEDStatus;
   digitalWrite(LED, LEDStatus);
}

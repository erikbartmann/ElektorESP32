#define LED    21 // LED-Pin
#define Taster 22 // Taster-Pin

volatile bool LEDStatus = false;
unsigned long lastInterruptTime; // Zählvariable

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Taster, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Taster), toggle, RISING);
}

void loop() { /* leer */ }

void toggle() {
  unsigned long interruptTime = millis();
 /* Wenn die Interrupts in Folge schneller wie 200ms auftreten,
    werden diese als Prellen erkannt und letztendlich ignoriert */
 if (interruptTime - lastInterruptTime > 200) {
   LEDStatus = !LEDStatus;
   digitalWrite(LED, LEDStatus);
 }
 // Speichert den aktuellen Zeitstempel
 lastInterruptTime = interruptTime;
}

#define Frequency  5000 // Frequenz
#define Resolution 8    // Auflösung
#define Step       1    // PWM-Schritte
#define Speed      6    // Geschwindigkeit

// GPIO-Array
byte pinArray[] = {25, 26, 32, 33, 27, 14, 12, 13, 15, 2};

void setup() {
  for (int ch = 0; ch < 10; ch++) {
    ledcSetup(ch, Frequency, Resolution);
    ledcAttachPin(pinArray[ch], ch);
  }
}

void loop() {
  for (int ch = 0; ch < 10; ch++) 
    for (int level = 0; level < 256; level+= Step) {
      ledcWrite(ch, level); delay(Speed);
    }
  for (int ch = 0; ch < 10; ch++)
    for (int level = 255; level >= 0; level-= Step) {
      ledcWrite(ch, level); delay(Speed);
    }
}

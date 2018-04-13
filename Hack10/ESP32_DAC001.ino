#define DAC1  25
#define DAC2  26
#define PAUSE 5

void setup() {
  pinMode(DAC1, ANALOG);
}

void loop() {
  for(int i = 0; i < 256; i++) {
    dacWrite(DAC1, i);
    delayMicroseconds(PAUSE); // Pause
  }
  for(int i = 255; i >= 0; i--) {
    dacWrite(DAC1, i);
    delayMicroseconds(PAUSE); // Pause
  }
}

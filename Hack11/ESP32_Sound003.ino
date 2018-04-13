#define SoundPin 10

void setup() {
  pinMode(SoundPin, OUTPUT);
}

void loop() {
  for(int i = 500; i > 200; i--) {
    digitalWrite(SoundPin, HIGH);
    delayMicroseconds(i);
    digitalWrite(SoundPin, LOW);
    delayMicroseconds(i);
  }
}

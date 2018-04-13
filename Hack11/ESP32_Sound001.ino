#define SoundPin 21
#define PAUSE 5

void setup() {
  pinMode(SoundPin, OUTPUT);
}

void loop() {
  digitalWrite(SoundPin, HIGH);
  delay(PAUSE);
  digitalWrite(SoundPin, LOW);
  delay(PAUSE);
}

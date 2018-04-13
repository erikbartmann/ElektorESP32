#define SoundPin 25
#define Pause 1000
void setup() {
  pinMode(SoundPin, OUTPUT);
}

void loop() {
  digitalWrite(SoundPin, HIGH);
  delayMicroseconds(Pause);
  digitalWrite(SoundPin, LOW);
  delayMicroseconds(Pause);
}

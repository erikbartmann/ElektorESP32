#define IN1 21 // Motor 1 - Antrieb
#define IN2 22 // Motor 1 - Antrieb
#define T1 19 // Taster Motor links
#define T2 23 // Taster Motor rechts

void setup() {
  pinMode(IN1, OUTPUT); // Motor 1
  pinMode(IN2, OUTPUT); // Motor 1
  pinMode(T1, INPUT); // Taster links
  pinMode(T2, INPUT); // Taster rechts
}

void loop() {
  digitalWrite(IN1, digitalRead(T1));
  digitalWrite(IN2, digitalRead(T2));
}

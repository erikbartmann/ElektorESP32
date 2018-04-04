#define LED 21

void setup() {
  pinMode(LED, OUTPUT); // Pin als Output
}

void loop() {
  digitalWrite(LED, HIGH); // LED-An
  delay(1000);             // 1 Sekunde Pause
  digitalWrite(LED, LOW);  // LED aus
  delay(1000);             // 1 Sekunde Pause
}

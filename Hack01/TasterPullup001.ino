#define Taster 22

void setup() {
  pinMode(Taster, INPUT_PULLUP); // Pin als Input mit Pullup
  Serial.begin(9600);            // Serial-Monitor
}

void loop() {
  byte tasterStatus = digitalRead(Taster);
  if(tasterStatus == LOW)
    Serial.println("Taster gedrückt");
  else
    Serial.println("Taster nicht gedrückt");
  delay(500); // Kurze Pause
}

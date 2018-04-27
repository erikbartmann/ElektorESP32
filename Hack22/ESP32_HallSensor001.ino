void setup() {
  Serial.begin(9600);
}

void loop() {
  int hallValue = hallRead();
  Serial.println(hallValue);
  delay(500);
}

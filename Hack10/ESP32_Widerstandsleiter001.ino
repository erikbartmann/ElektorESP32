int pinArray[] = {21, 22, 19, 23, 18, 5, 10, 9};
int value; // DAC-Wert

void setup() {
  for(int i = 0; i < 8; i++)
    pinMode(pinArray[i], OUTPUT);
  value = B00000011; // Ansteuerung des R2R-Netzwerkes
}

void loop() {
  for(int i = 0; i < 8; i++)
    digitalWrite(pinArray[i], bitRead(value, i) ==1?HIGH:LOW);
}

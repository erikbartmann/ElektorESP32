#define Frequency  50
#define Channel    0 // Kanal 0
#define Resolution 8 // Auflösung
#define Poti      25 // Poti-Pin
#define LED       22 // LED-Pin

void setup() {
  ledcSetup(Channel, Frequency, Resolution);
  ledcAttachPin(LED, Channel);
  Serial.begin(9600);
}

void loop() { 
  int potValue = map(analogRead(Poti), 0, 4095, 0, pow(2, Resolution) - 1);
  ledcWrite(Channel, potValue);  // PWM GPIO-Ansteuerung
  Serial.println(potValue);
  delay(100);
}

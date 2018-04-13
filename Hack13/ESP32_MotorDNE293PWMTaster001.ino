#define IN1  21 // Motor 1 - Antrieb
#define IN2  22 // Motor 1 - Antrieb
#define EN12 18 // Motor 1 - Enable
#define T1   19 // Taster Motor links
#define T2   23 // Taster Motor rechts
#define Frequency  5000 // PWM-Frequenz
#define Channel    0    // Genutzter PWM-Kanal
#define Resolution 8    // 8-Bit Auflösung
#define PotiPin    35   // Potentiometer-Pin

void setup() {
  pinMode(IN1, OUTPUT); // Motor 1
  pinMode(IN2, OUTPUT); // Motor 1
  pinMode(T1, INPUT);   // Taster links
  pinMode(T2, INPUT);   // Taster rechts
  ledcSetup(Channel, Frequency, Resolution);
  ledcAttachPin(EN12, Channel);
  Serial.begin(9600); // Init Serial-Monitor
}

void loop() {
  // Poti-Wert auf Werte 0 bis 255 konvertieren
  int potiValue = map(analogRead(PotiPin), 0, 4095, 0, 255);
  // PWM-Wert an EN12 versenden
  ledcWrite(Channel, potiValue);
  // Motor ansteuern
  digitalWrite(IN1, digitalRead(T1));
  digitalWrite(IN2, digitalRead(T2));
  // Kontrolle des PWM-Wertes
  Serial.println(potiValue);
}

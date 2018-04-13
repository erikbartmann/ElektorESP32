#define Frequency  5000
#define Channel0   0 // Kanal 0
#define Channel1   1 // Kanal 1
#define Channel2   2 // Kanal 2
#define Channel3   3 // Kanal 3
#define Resolution 8 // Auflösung

void setup() {
  ledcSetup(Channel0, Frequency, Resolution);
  ledcSetup(Channel1, Frequency, Resolution);
  ledcSetup(Channel2, Frequency, Resolution);
  ledcSetup(Channel3, Frequency, Resolution);
  
  ledcAttachPin(25, Channel0);
  ledcAttachPin(26, Channel1);
  ledcAttachPin(32, Channel2);
  ledcAttachPin(33, Channel3);
  
  ledcWrite(Channel0, 32);  // 12,5% Tastverhältnis
  ledcWrite(Channel1, 64);  // 25% Tastverhältnis
  ledcWrite(Channel2, 128); // 50% Tastverhältnis
  ledcWrite(Channel3, 160); // 62% Tastverhältnis
}

void loop() { /* leer */ }

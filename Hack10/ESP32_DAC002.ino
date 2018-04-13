#define DAC1      25
#define Steps     1
#define Offset    128
#define Amplitude 100

void setup() {
  pinMode(DAC1, ANALOG);
}

void loop() {
  for(int i = 0; i < 360; i = i + Steps) 
    dacWrite(DAC1, int(Offset + Amplitude * sin(i * PI/180)));
}

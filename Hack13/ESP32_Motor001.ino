#define MotorPin 25  // Motor-Pin
#define TouchOn  T2  // Touch T2 -> IO2
#define TouchOff T3  // Touch T3 -> IO15
#define Threshold 15 // Ansprechschwelle

bool motorDrive = false; // Flag für Motor

void setup() {
  pinMode(MotorPin, OUTPUT);
}

void loop() {
  byte touchValueOn  = touchRead(TouchOn);
  byte touchValueOff = touchRead(TouchOff);
  if(touchValueOn  < Threshold) motorDrive = true;
  if(touchValueOff < Threshold) motorDrive = false;
  if(motorDrive) 
    digitalWrite(MotorPin, HIGH);
  else
    digitalWrite(MotorPin, LOW);
  delay(100); // Kurze Pause
}

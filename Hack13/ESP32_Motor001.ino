#define MotorPin 25 // Motor-Pin
#define TouchOn  T2 // Touch T2 -> IO2
#define TouchOff T3 // Touch T3 -> IO15
#define Theshold 15 // Ansprechschwelle

bool motorDrive = false; // Flag für Motor

void setup() {
  pinMode(MotorPin, OUTPUT);
}

void loop() {
  byte touchValueOn  = touchRead(TouchOn);
  byte touchValueOff = touchRead(TouchOff);
  if(touchValueOn  < Theshold) motorDrive = true;
  if(touchValueOff < Theshold) motorDrive = false;
  if(motorDrive) 
    digitalWrite(MotorPin, HIGH);
  else
    digitalWrite(MotorPin, LOW);
  delay(100); // Kurze Pause
}

#define STEPPER_DIRECTION 21 // Stepper Direction-Pin
#define STEPPER           22 // Stepper Pin
#define STEPPER_DELAY      5 // Stepper Delay
#define STEPS_TO_MOVE     60 // Anzahl der Schritte

enum stepperDirection {
  RIGHT, // LOW
  LEFT   // HIGH
};

void setup() {
  pinMode(STEPPER_DIRECTION, OUTPUT); 
  pinMode(STEPPER, OUTPUT);           
  digitalWrite(STEPPER_DIRECTION, LEFT);
  for (int i = 0; i <= STEPS_TO_MOVE; i++) {
    digitalWrite(STEPPER, HIGH); delay(STEPPER_DELAY);
    digitalWrite(STEPPER, LOW ); delay(STEPPER_DELAY);
  }
}

void loop() { /* leer */ }

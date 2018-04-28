#define STEPPER_DIRECTION1 21 // Stepper1 Direction-Pin
#define STEPPER1           22 // Stepper1 Pin
#define STEPPER_DELAY1     4 // Stepper1 Delay
#define STEPPER_DIRECTION2 19 // Stepper2 Direction-Pin
#define STEPPER2           23 // Stepper2 Pin
#define STEPPER_DELAY2      5 // Stepper2 Delay

unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
bool stepperState1, stepperState2 = false;

void setup() {
  pinMode(STEPPER_DIRECTION1, OUTPUT); 
  pinMode(STEPPER1, OUTPUT);  
  pinMode(STEPPER_DIRECTION2, OUTPUT); 
  pinMode(STEPPER2, OUTPUT);
  digitalWrite(STEPPER_DIRECTION1, HIGH);
  digitalWrite(STEPPER_DIRECTION2, LOW); 
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= STEPPER_DELAY1) {
    previousMillis1 = currentMillis;
    stepperState1 = !stepperState1;
  }
  if (currentMillis - previousMillis2 >= STEPPER_DELAY2) {
    previousMillis2 = currentMillis;
    stepperState2 = !stepperState2;
  }
  digitalWrite(STEPPER1, stepperState1);
  digitalWrite(STEPPER2, stepperState2);
}

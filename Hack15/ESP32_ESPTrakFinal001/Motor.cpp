#include "Motor.h"

// Konstruktor
Motor::Motor() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(EN12, OUTPUT); pinMode(EN34, OUTPUT);
  digitalWrite(EN12, HIGH); digitalWrite(EN34, HIGH);
  ledcSetup(PWMChannelM1, PWMFrequency, PWMResolution);
  ledcAttachPin(EN12, PWMChannelM1);
  ledcSetup(PWMChannelM1, PWMFrequency, PWMResolution);
  ledcAttachPin(EN34, PWMChannelM2);
}

void Motor::move(byte dir, int duration, int speed) {
  ledcWrite(PWMChannelM1, speed); 
  ledcWrite(PWMChannelM2, speed);
  switch (dir) {
    case 1: control(HIGH, LOW, HIGH, LOW); break; // Vorwärts
    case 2: control(LOW, HIGH, LOW, HIGH); break; // Rückwärts
    case 3: control(HIGH, LOW, LOW, HIGH); break; // Rechts
    case 4: control(LOW, HIGH, HIGH, LOW); break; // Links
  }
  delay(duration); // Dauer der Aktion
  control(LOW, LOW, LOW, LOW); // Alles Stop
}

void Motor::control(bool in1, bool in2, bool in3, bool in4) {
  digitalWrite(IN1, in1); digitalWrite(IN2, in2); // Motor 1
  digitalWrite(IN3, in3); digitalWrite(IN4, in4); // Motor 2
}



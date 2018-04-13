#ifndef Moror_h
#define Motor_h
#include <Arduino.h>

#define FORWARD  1 // Parameter für Vorwärtsfahrt
#define BACKWARD 2 // Parameter für Rückwärtsfahrt
#define LEFT     3 // Parameter für Linksdrehung
#define RIGHT    4 // Parameter für Rechtsdrehung
#define IN1  21 // Motor 1 - Antrieb
#define IN2  22 // Motor 1 - Antrieb
#define EN12 18 // Motor 1 - Enable
#define IN3  19 // Motor 2 - Antrieb
#define IN4  23 // Motor 2 - Antrieb
#define EN34  5 // Motor 2 - Enable
#define PWMFrequency 5000 // PWM-Frequenz
#define PWMChannelM1    1 // Genutzter PWM-Kanal Motor 1
#define PWMChannelM2    2 // Genutzter PWM-Kanal Motor 2
#define PWMResolution   8 // 8-Bit PWM-Auflösung

class Motor {
  public:
    Motor(); // Standard-Konstruktor
    void move(byte, int, int); // Bewegen-Methode
  private:
    void control(bool, bool, bool, bool); // Steuer-Methode
};
#endif

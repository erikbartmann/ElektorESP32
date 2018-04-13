#include "Motor.h"
/* Verwendung der move-Methode
   move(Richtung, Dauer, Speed) 
*/

Motor meinMotor;

void setup() {
  meinMotor.move(FORWARD,  3000, 255); // Vorwärts
  meinMotor.move(BACKWARD, 2000, 200); // Rückwärts
  meinMotor.move(LEFT,     2500, 220); // Links
  meinMotor.move(RIGHT,    2500, 220); // rechts
}

void loop() { /* leer */}

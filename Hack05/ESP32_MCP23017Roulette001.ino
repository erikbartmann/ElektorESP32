#include <Wire.h>
#define address  0x20 // I2C Address MCP23017
#define GPIOA    0x12 // Register Address Port A
#define GPIOB    0x13 // Register Address Port B
#define IODIRA   0x00 // I/O-Register Address Port A
#define IODIRB   0x01 // I/O-Register Address Port B

void setup() {
  Wire.begin(); // Init I2C bus
  sendData(0x00, IODIRA); // Alle Pins -> OUTPUT
  randomSeed(analogRead(25));
  byte randomNr = random(0, 8);
  roll(randomNr);
}

void loop() { /* leer */ }

void sendData(char data, byte reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);  // Register
    Wire.write(data); // Set data
    Wire.endTransmission();
}

void roll(byte n) {
  for(int i = 0; i < 4; i++)
    for(int j = 0; j < 8; j++) {
      sendData(1 << j, GPIOA);
      delay(100);
    }
  sendData(1 << n, GPIOA);  
}

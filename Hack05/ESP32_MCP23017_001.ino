#include <Wire.h>
#define address  0x20 // I2C Address MCP23017
#define GPIOA    0x12 // Register Address Port A
#define GPIOB    0x13 // Register Address Port B
#define IODIRA   0x00 // I/O-Register Address Port A
#define IODIRB   0x01 // I/O-Register Address Port B

char bitArray[] = {0B10101010, 0B01010101,
                   0B00001111, 0B11110000,
                   0B11001100, 0B00110011};

void setBits(char bits) {
    Wire.beginTransmission(address);
    Wire.write(GPIOA); // GPIOA
    Wire.write(bits);  // Set bits
    Wire.endTransmission();
}

void setup() {
  Wire.begin(); // Init I2C bus
  Wire.beginTransmission(address);
  Wire.write(IODIRA); // IODIRA register
  Wire.write(0x00);   // All pins to output
  Wire.endTransmission();
}

void loop() {
  for(int i = 0; i < 6; i++) {
    setBits(bitArray[i]);
    delay(500);
  }
}

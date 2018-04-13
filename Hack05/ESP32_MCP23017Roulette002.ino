#include <Wire.h>
#define address  0x20 // I2C Address MCP23017
#define GPIOA    0x12 // Register Address Port A
#define GPIOB    0x13 // Register Address Port B
#define IODIRA   0x00 // I/O-Register Address Port A
#define IODIRB   0x01 // I/O-Register Address Port B

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Init I2C bus
  sendData(0x00, IODIRA); // Alle Pins Port A -> OUTPUT
  sendData(0x01, IODIRB); // Port B GPB0  -> INPUT
}

void loop() {
  byte tasterStatus = readTaster(GPIOB);
  evalTaster(tasterStatus);
}

byte readTaster(byte reg) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, 1);
  return Wire.read();
}

void evalTaster(byte t) {
  Serial.println(t);
  if((t & 0x01) == 0x01) {
    Serial.println("Taster 1 gedrückt");
    randomSeed(analogRead(25));
    byte randomNr = random(0, 8);
    roll(randomNr);
  }
}

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

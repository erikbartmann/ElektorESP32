#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b" // Service UUID
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8" // Characteristic UUID
BLECharacteristic *pCharacteristic; // Metadaten für BLE
bool deviceConnected = false;       // BLE Connection Status
float analogValue = 0;              // Analog Value
const int readPin = 32;             // Analog-Pin

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void setup() {
  Serial.begin(115200); // Serial-Monitor
  BLEDevice::init("ESP32 AnalogRead"); // Erzeuge BLE-Device mit Name
  // Create BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);
  // Create BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE
                    );                    
  // Start service
  pService->start();
  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  if (deviceConnected) {
    analogValue = analogRead(readPin); // Analoger Wert

    // Convert value to char-Array
    char analogString[8]; // Buffer
    dtostrf(analogValue, 1, 2, analogString); // value, min width, digits, char buffer
    pCharacteristic->setValue(analogString);  
    pCharacteristic->notify(); // Sends value to app
    Serial.print("Analog Value: ");
    Serial.println(analogValue);
  }
  delay(1000);
}

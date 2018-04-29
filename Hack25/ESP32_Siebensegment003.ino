byte segmente[10]= {B01111110,  // 0
                    B00110000,  // 1
                    B01101101,  // 2
                    B01111001,  // 3
                    B00110011,  // 4
                    B01011011,  // 5
                    B01011111,  // 6
                    B01110000,  // 7
                    B01111111,  // 8
                    B01111011}; // 9 
                    
int pinArray[] = {21, 22, 19, 23, 18, 5, 10};                      

void setup() {
  for(int i = 0; i < 7; i++)
    pinMode(pinArray[i], OUTPUT);  
}

void loop() {
  for(int i = 0; i < 10; i++) {   // Ansteuern der Ziffer
    for(int j = 6; j >= 0; j--){  // Abfragen der Bits für die Segmente
      digitalWrite(pinArray[6 - j], bitRead(segmente[i], j) == 1?LOW:HIGH);
    }    
    delay(500); // Eine halbe Sekunde warten
  }
}

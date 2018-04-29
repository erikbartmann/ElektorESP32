int segmente[10][7] = 
 {{1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
}; 

int pinArray[] = {21, 22, 19, 23, 18, 5, 10};

void setup() {
  for (int i = 0; i < 7; i++)
    pinMode(pinArray[i], OUTPUT);
}

void loop() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++)
      digitalWrite(pinArray[j], (segmente[i][j] == 1) ? LOW : HIGH);
    delay(1000);
  }
}

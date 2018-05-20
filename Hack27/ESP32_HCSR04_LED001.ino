#define trigPin 21 // Trigger-Pin
#define echoPin 22 // Echo-Pin
long zeit, cm;
int ledArray[] = {19, 23, 18, 5, 10, 9, 25, 26, 32, 33};
 
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  for(int i = 0; i < 10; i++) {
    pinMode(ledArray[i], OUTPUT);
  }
}
 
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  zeit = pulseIn(echoPin, HIGH);
  cm = (zeit/2) / 29.4;
  Serial.println(cm);
  showLED(cm);
  delay(50);
}

void showLED(int v) {
  digitalWrite(ledArray[0], v < 10);
  digitalWrite(ledArray[1], (v >= 10) && (v < 15));
  digitalWrite(ledArray[2], (v >= 15) && (v < 20));
  digitalWrite(ledArray[3], (v >= 20) && (v < 25));
  digitalWrite(ledArray[4], (v >= 25) && (v < 30));
  digitalWrite(ledArray[5], (v >= 30) && (v < 35));
  digitalWrite(ledArray[6], (v >= 35) && (v < 40));
  digitalWrite(ledArray[7], (v >= 40) && (v < 45));
  digitalWrite(ledArray[8], (v >= 45) && (v < 50));
  digitalWrite(ledArray[9], (v >= 50) && (v < 55));
}

#define trigPin 21 // Trigger-Pin
#define echoPin 22 // Echo-Pin
long zeit, cm;
 
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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
  Serial.print("Entfernung: ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}

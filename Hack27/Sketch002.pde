import processing.serial.*;

Serial myPort;  // Serielles Objekt erstellen
String value;   // Für empfangenen Wert (String)
float v;        // Für empfangenen Wert (float)

void setup() {
  size(200,100); // Fenstergröße  
  String portName = Serial.list()[0]; // Index ggf. anpassen
  myPort = new Serial(this, portName, 9600);
}

void serialEvent(Serial myPort) {
// Eintreffende Daten in eine Zeichenkette speichern 
// solange, bis '\n' empfangen wurde
value = myPort.readStringUntil('\n');
// Sicherstellen, dass val initialisiert wurde
  if (value != null) {
    value = trim(value); // Leerzeichen bzw. Formatierungzeichen wie CR entfernen
    v = float(value);
    v = map(v, 0, 100, 0, width);
  }
}

void draw() {
  background(0);     // Hintergrundfarbe
  strokeWeight(3);   // Liniendicke
  println(v);        // Wert anzeigen
  // Linienfarbe 
  if(v < 30) stroke(255, 0, 0); else stroke(0, 255, 0); 
  line(v, 50, v, 100); // Linie zeichnen
}

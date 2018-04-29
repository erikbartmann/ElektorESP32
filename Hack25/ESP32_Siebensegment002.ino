void setup(){
  Serial.begin(9600);
  byte a = B10001011;     // Variable deklarieren + initialisieren
  Serial.println(a, BIN); // Als Binärwert ausgeben
  Serial.println(a, HEX); // Als Hexwert ausgeben
  Serial.println(a, DEC); // Als Dezimalwert ausgeben
}

void loop(){ /* leer */ }

void setup() {
  Serial.begin(9600);
  // Anzeige, dass normaler Status existiert.
  Serial.println("Normal mode.");
  delay(5000); // 5 Sekunden Pause
  // Anzeige, dass Deep Sleep Mode eingeleitet wird.
  Serial.println("Deep sleep mode.");
  // Starten des Deep-Sleep-Modes
  esp_deep_sleep_start();
}

void loop() { /* leer */ }

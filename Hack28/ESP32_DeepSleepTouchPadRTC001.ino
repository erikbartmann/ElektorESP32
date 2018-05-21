#define Threshold 50           // Ansprechschwelle
RTC_DATA_ATTR int counter = 0; // RTC-Variable

void showWakeupReason() {
  esp_sleep_wakeup_cause_t wakeupReason;
  wakeupReason = esp_sleep_get_wakeup_cause();
  switch(wakeupReason) {
    case 1:
      Serial.println("Wakeup durch externes Signal RTC_IO"); 
      break;
    case 2: 
      Serial.println("Wakeup durch externes Signal RTC_CNTL"); 
      break;
    case 3: 
      Serial.println("Wakeup durch Timer"); 
      break;
    case 4: 
      Serial.println("Wakeup durch Touchpad"); 
      break;
    case 5: 
      Serial.println("Wakeup durch ULP Programm"); 
      break;
    default: 
      Serial.println("Wakeup nicht durch Deep-Sleep"); 
      break;
  }
}

void showWakeupTouchpad() {
  touch_pad_t touchPin;
  touchPin = esp_sleep_get_touchpad_wakeup_status();
  switch (touchPin) {
    case 0: Serial.println("Touch an IO 4"); break;
    case 1: Serial.println("Touch an IO 0"); break;
    case 2: Serial.println("Touch an IO 2"); break;
    case 3: Serial.println("Touch an IO 15"); break;
    case 4: Serial.println("Touch an IO 13"); break;
    case 5: Serial.println("Touch an IO 12"); break;
    case 6: Serial.println("Touch an IO 14"); break;
    case 7: Serial.println("Touch an IO 27"); break;
    case 8: Serial.println("Touch an IO 33"); break;
    case 9: Serial.println("Touch an IO 32"); break;
    default: Serial.println("Wakeup nicht durch Touchpad"); break;
  }
}

void callback() { /* leer */ }

void setup() {
  Serial.begin(9600);
  Serial.println("\nsetup() ausgeführt!");
  counter++; // RTC-Variable hochzählen
  // Zeige Wakeup-Informationen
  showWakeupReason();
  showWakeupTouchpad();
  // Zeige Inhalt der RTC-Variablen
  Serial.print("Count: ");
  Serial.println(counter);
  // Konfiguration des Touchpad-Interrupts T2->IO2
  touchAttachInterrupt(T2, callback, Threshold);
  // Konfiguration des Touchpad als Wakeup Source
  esp_sleep_enable_touchpad_wakeup();
  Serial.println("Deep sleep mode.");
  esp_deep_sleep_start();
}

void loop() { /* leer */ }

#define GPIO_MASK 0x4C00000000

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

void showWakeupIO() {
  uint64_t IOReason = esp_sleep_get_ext1_wakeup_status();
  String res = "";
  for(int i = 0; i < 64; i++) {
    int a = (IOReason >> i) & 0x1;
    if(a == 0) res = "0" + res;
    else if(a == 1) res = "1" + res;
  }
  Serial.println(res);
}

void callback() { /* leer */ }

void setup() {
  Serial.begin(9600);
  Serial.println("\nsetup() ausgeführt!");
  // Zeige Wakeup-Informationen
  showWakeupReason();
  showWakeupIO();
  // Konfiguration von ext1 als Wakeup Source
  esp_sleep_enable_ext1_wakeup(GPIO_MASK, ESP_EXT1_WAKEUP_ANY_HIGH);
  Serial.println("Deep sleep mode.");
  esp_deep_sleep_start();
}

void loop() { /* leer */ }

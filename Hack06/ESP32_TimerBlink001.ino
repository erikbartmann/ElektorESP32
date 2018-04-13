#define LEDPIN 9           // LED-Pin
hw_timer_t * timer = NULL; // Hardware-Timer erstellen
volatile byte led = LOW;   // LED-Status

void IRAM_ATTR onTimer() {
  led=!led; // Toggle LED-Status
  digitalWrite(LEDPIN, led); // Ansteuerung LED
}

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT); // LED-Pin als Ausgang
  Serial.println("Timer-Start");
  timer = timerBegin(0, 80, true);  // timer 0, MWDT clock period = 12.5 ns * TIMGn_Tx_WDT_CLK_PRESCALE -> 12.5 ns * 80 -> 1000 ns = 1 us, countUp
  timerAttachInterrupt(timer, &onTimer, true); // edge (not level) triggered 
  //timerAlarmWrite(timer, 1000000, true); // 1000000 * 1 us = 1 s, autoreload true
  timerAlarmWrite(timer, 10000, true); // 1000000 * 1 us = 1 s, autoreload true
  timerAlarmEnable(timer); // Enable Timer
}

void loop() { /* leer */ }

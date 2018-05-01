from machine import Pin
import time
ledPin21 = Pin(21, Pin.OUT)
while True:
  ledPin21.value(0)
  time.sleep(0.5)
  ledPin21.value(1)
  time.sleep(0.5)

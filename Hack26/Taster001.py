from machine import Pin
ledPin21 = Pin(21, Pin.OUT)
tasterPin22 = Pin(22, Pin.IN)
while True:
  if tasterPin22.value() == 1:
    ledPin21.value(1)
  else:
    ledPin21.value(0)

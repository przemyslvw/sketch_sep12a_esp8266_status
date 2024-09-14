#include <Arduino.h>  // Potrzebne, aby używać funkcji Arduino
#include "led.h"

void blinkLED() {
  digitalWrite(LED_BUILTIN, LOW);  // Włącz diodę
  digitalWrite(LED_GPIO4, HIGH);  // Włącz diodę
  delay(100);                      // Opóźnienie 100 ms
  digitalWrite(LED_BUILTIN, HIGH); // Wyłącz diodę
  digitalWrite(LED_GPIO4, LOW); // Wyłącz diodę
  delay(100);  
}

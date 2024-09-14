#include <Arduino.h>  // Potrzebne, aby używać funkcji Arduino
#include "led.h"

// Funkcja do migania diodą wbudowaną
void blinkBuiltinLED() {
  digitalWrite(LED_BUILTIN, LOW);  // Włącz diodę
  delay(100);                      // Opóźnienie 100 ms
  digitalWrite(LED_BUILTIN, HIGH); // Wyłącz diodę
}

// Funkcja do migania zewnętrzną diodą Włączamy diodę GPIO4
void blinkLEDGPIO4() {
  digitalWrite(LED_GPIO4, LOW);       // Dioda na GPIO4 (D2) gaśnie
  delay(100);           // Czekamy 1 sekundę
  digitalWrite(LED_GPIO4, HIGH);      // Dioda na GPIO4 (D2) zapala się na HIGH (aktywny stan wysoki)
}  
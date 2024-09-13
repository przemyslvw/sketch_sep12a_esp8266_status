#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "wifi_setup.h"  // Import konfiguracji WiFi
#include "mqtt_client.h" // Import konfiguracji MQTT

unsigned long lastUpdateTime;
unsigned long totalActiveMinutes = 0;  // Domyślna wartość
const unsigned long updateInterval = 60000; // 1 minuta
bool initialValueLoaded = false; // Flaga do sprawdzenia, czy początkowa wartość została załadowana

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);  // Ustawienie diody w tryb OUTPUT
  digitalWrite(LED_BUILTIN, HIGH); // Upewnij się, że dioda jest wyłączona na start

  setup_wifi();  // Funkcja z pliku wifi_setup.h
  setup_mqtt();  // Funkcja z pliku mqtt_client.h

  lastUpdateTime = millis();
}

void loop() {
  if (!client.connected()) {
    reconnect();  // Funkcja z mqtt_client.h
  }
  client.loop();

  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= updateInterval) {
    if (initialValueLoaded) {
      totalActiveMinutes += 1;
      lastUpdateTime = currentTime;
      saveTotalActiveMinutes();  // Funkcja z mqtt_client.h
    } else {
      Serial.println("Oczekiwanie na początkową wartość...");
      totalActiveMinutes = 0;
      initialValueLoaded = true;
    }
  }
}

#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include "credentials.h"  // Importuj dane uwierzytelniające

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Laczenie z ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Polaczono z siecia WiFi");
  Serial.println(WiFi.localIP());
}

#endif

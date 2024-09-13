#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <PubSubClient.h>
#include "credentials.h"  // Importuj dane uwierzytelniające

WiFiClient espClient;
PubSubClient client(espClient);

extern unsigned long totalActiveMinutes;
extern bool initialValueLoaded;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Odebrano wiadomość na temat: ");
  Serial.println(topic);

  payload[length] = '\0';  // Dodaj znak końca łańcucha
  if (strcmp(topic, "totalActiveMinutes") == 0) {
    totalActiveMinutes = atol((char*)payload);
    Serial.print("Wczytano totalActiveMinutes: ");
    Serial.println(totalActiveMinutes);
    initialValueLoaded = true;
  }
}

void saveTotalActiveMinutes() {
  if (client.connected()) {
    char msg[50];
    int len = sprintf(msg, "%lu", totalActiveMinutes);
    if (len > 0) {
      bool result = client.publish("totalActiveMinutes", msg, true);  // Zmieniono na true (retained message)
      if (result) {
        Serial.print("Zapisano totalActiveMinutes: ");
        Serial.println(totalActiveMinutes);
      } else {
        Serial.println("Błąd publikacji na temat totalActiveMinutes.");
      }
    } else {
      Serial.println("Błąd formatowania wiadomości.");
    }
  } else {
    Serial.println("Klient nie jest połączony.");
  }
}

void loadTotalActiveMinutes() {
  if (client.connected()) {
    Serial.println("Subskrybowanie tematu totalActiveMinutes...");
    bool result = client.subscribe("totalActiveMinutes");
    if (result) {
      Serial.println("Subskrypcja pomyślna.");
    } else {
      Serial.println("Błąd subskrypcji.");
    }
  } else {
    Serial.println("Nie ma połączenia z MQTT.");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Laczenie z MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Polaczono");
      client.publish("test", "Witaj z ESP8266");
      loadTotalActiveMinutes();  // Subskrybuj temat
      client.setCallback(callback);  // Ustaw funkcję zwrotną
    } else {
      Serial.print("Nie udalo sie, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup_mqtt() {
  client.setServer(mqtt_server, 1883);
  reconnect();
}

#endif

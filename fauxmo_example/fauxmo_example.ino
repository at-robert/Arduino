#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include "credential.h"

#define SERIAL_BAUDRATE                 115200
#define GPIO5_ID 1

fauxmoESP fauxmo;

// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

    // Set WIFI module to STA mode
    WiFi.mode(WIFI_STA);

    // Connect
    Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // Wait
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
    }
    Serial.println();

    // Connected!
    Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void gpio_setup() {
  pinMode(GPIO5_ID, OUTPUT);
}

void callback(uint8_t device_id, const char * device_name, bool state) {
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");
  if (state) {
    Serial.println("ON xx");
    digitalWrite(GPIO5_ID, HIGH);
  } else {
    Serial.println("OFF x");
    digitalWrite(GPIO5_ID, LOW);
  }
}

void setup() {
    // Init serial port and clean garbage
    Serial.begin(SERIAL_BAUDRATE);
    Serial.println("FauxMo demo sketch");
    Serial.println("After connection, ask Alexa/Echo to 'turn <devicename> on' or 'off'");

    // Wifi
    wifiSetup();

    //GPIO
    gpio_setup();

    // Fauxmo
    fauxmo.addDevice("relay");
    fauxmo.addDevice("pixels");
    fauxmo.onMessage(callback);
}

void loop() {
  fauxmo.handle();
}

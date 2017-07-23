#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "globals.h"
#include "weather_helpers.h"

void setup() {
  Serial.begin(115200);

  if (DEBUG_MODE == 1) {
    Serial.println(ESP.getChipId(), HEX);
    Serial.println(ESP.getFlashChipId(), HEX);

    Serial.println(ESP.getFlashChipSize());
    Serial.println(ESP.getFlashChipSpeed());

    Serial.print("Connecting to: ");
    Serial.println(WIFI_SSID);
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  if (DEBUG_MODE == 1) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("Device IP: ");
    Serial.print(WiFi.localIP());
  }

  temperaturePixels.begin();
  temperaturePixels.setBrightness(64);

  DS18B20.begin();
}

void loop() {  
//  getRemoteWeather();
  getInternalTemperature();
}

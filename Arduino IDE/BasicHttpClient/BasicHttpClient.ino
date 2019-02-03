#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {
  pinMode(D5, OUTPUT);     // Initialize the pin as an output
  digitalWrite(D5, LOW);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("DIGI_71f618", "3ff08e09");
  Serial.begin(115200);
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;

    Serial.println();
    Serial.print("Starting ...");
    Serial.flush();

    HTTPClient http;
    //  int sensorValue = analogRead(A0);
    // Serial.println();
    // Serial.print(String(sensorValue));
    // Serial.flush();
    if (http.begin(client, "http://basilicum-api.azurewebsites.net/api/mesurement/create/1/1")) {
      int httpCode = http.POST("Content-Length: 0");

      // httpCode will be negative on error
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println();
          Serial.print("Http call success " + String(httpCode));
          Serial.flush();
          delay(1000);

          Serial.println();
          Serial.print("Going to sleep");
          Serial.flush();
          ESP.deepSleep(60e6);
        }
        else {
          Serial.println();
          Serial.print(" http failed " + String(httpCode));
          Serial.flush();
          delay(1000);
        }
        http.end();
        Serial.println();
        Serial.print("Http end");
        Serial.flush();
        delay(1000);
      }
      else {
        Serial.println();
        Serial.print("Http code  < 0");
        Serial.flush();
      }
    }
  }
  else {
    Serial.println();
    Serial.print("Not connected to wifi");
    Serial.flush();
  }
  
}

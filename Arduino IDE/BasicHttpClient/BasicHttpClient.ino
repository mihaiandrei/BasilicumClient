/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  pinMode(D7, OUTPUT);     // Initialize the pin as an output
  pinMode(D5, OUTPUT);     // Initialize the pin as an output
  digitalWrite(D5, LOW); 
  digitalWrite(D7, LOW);   

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("DIGI_71f618", "3ff08e09");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://basilicum-api.azurewebsites.net/api/parameter/list?SearchString=node")) {  // HTTP
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          //digitalWrite(D5, HIGH);
          delay(1000);
        }
        digitalWrite(D5, HIGH); 
        delay(1000);  
      }
      http.end();
    } else {
     digitalWrite(D7, HIGH);
     delay(1000);
    }
  }
  digitalWrite(D5, LOW); 
  digitalWrite(D7, LOW);   
}

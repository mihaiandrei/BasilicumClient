#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
int retryAttempt;

void setup() {
  pinMode(D5, OUTPUT);     // Initialize the pin as an output
  digitalWrite(D5, HIGH);
  retryAttempt = 10;
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("DIGI_71f618", "3ff08e09");
  Serial.begin(115200);
}

void loop() {
  // wait for WiFi connection
  if (WiFiMulti.run() == WL_CONNECTED) {
    WiFiClient client;

    writeToSerial("Connected to wifi");

    HTTPClient http;
    int sensorValue = analogRead(A0);
    writeToSerial(("Value read: " + String(sensorValue)).c_str());
    if (http.begin(client, "http://basilicum-api.azurewebsites.net/api/mesurement/create/1/1")) {
      int httpCode = http.POST("Content-Length: 0");

      // httpCode will be negative on error
      if (httpCode > 0) {
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          writeToSerial(("Http call success " + String(httpCode)).c_str());
          shutDown();
        }
        else {
          writeToSerial(("http failed " + String(httpCode)).c_str());
        }
        http.end();
      }
      else {
        writeToSerial(("http failed " + String(httpCode)).c_str());
      }
    }
  }
  else {
    writeToSerial("Connection to wifi failed");
    delay(1000);
  }
  if (retryAttempt <= 0) {
    writeToSerial("Finish retring");
    shutDown();
  }
  retryAttempt-- ;
}

void writeToSerial(const char* input) {
  Serial.println();
  Serial.print(input);
  Serial.flush();
  return;
}

void shutDown() {
  digitalWrite(D5, LOW);
  writeToSerial("Going to sleep");
  ESP.deepSleep(60e6);
}
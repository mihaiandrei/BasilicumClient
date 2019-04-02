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

    int sensorValue = analogRead(A0);
    writeToSerial(("Value read: " + String(sensorValue)).c_str());
    double celsius = milivoltsToCelsius(sensorValue);
    writeToSerial(("Value read Celsius: " + String(celsius)).c_str());
    
    if (sendMeasurement(client, 2, sensorValue) && sendMeasurement(client, 3, celsius)) {
      shutDown();
    }
  }
  else {
    writeToSerial("Connection to wifi failed");
    delay(1000);
  }
  if (retryAttempt <= 0) {
    writeToSerial("Finish retrying");
    shutDown();
  }
  retryAttempt-- ;
}

bool sendMeasurement(WiFiClient client, int parameterId, double parameterValue) {
  HTTPClient http;
  if (http.begin(client, "http://basilicum-api.azurewebsites.net/api/measurement/create/" + String(parameterId) + "/" + String(parameterValue))) {
    int httpCode = http.POST("Content-Length: 0");

    // httpCode will be negative on error
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_CREATED) {
        writeToSerial(("Http call success " + String(httpCode)).c_str());
        return true;
      }
      else {
        writeToSerial(("http failed " + String(httpCode)).c_str());
        return false;
      }
      http.end();
    }
    else {
      writeToSerial(("http failed " + String(httpCode)).c_str());
      return false;
    }
  }
}

double milivoltsToCelsius(int milivolts) {
  return (milivolts - 159) / 5.12077;
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

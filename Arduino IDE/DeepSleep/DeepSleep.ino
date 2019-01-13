#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void setup() {
  pinMode(D7, OUTPUT);     // Initialize the pin as an output
  pinMode(D5, OUTPUT);     // Initialize the pin as an output
  
  digitalWrite(D7, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(2000);                      // Wait for a second
  digitalWrite(D7, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(4000);                      // Wait for two seconds (to demonstrate the active low LED)
  
  digitalWrite(D5, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(2000);                      // Wait for a second
  digitalWrite(D5, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(4000);                      // Wait for two seconds (to demonstrate the active low LED)

  delay(40000);
  digitalWrite(D7, LOW);
  digitalWrite(D5, LOW);
  ESP.deepSleep(20e6); // 20e6 is 20 microseconds
}

// the loop function runs over and over again forever
void loop() {
}

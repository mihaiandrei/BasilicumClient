# Configure Lolin Node Mcu V3

Follow this tutorial
https://www.instructables.com/id/Getting-Started-With-ESP8266LiLon-NodeMCU-V3Flashi/

## Flush
Make sure that Drivers are installed USB-Serial CH340. A new device should appear in Device manager under Ports. 
To enable Flush Mode connect D3 to GND and D8 to GND with jumper cables.

## Upload code to the device
* Connect D3 to GND and D8 to GND with jumper cables.
* Press and hold Flush button
* Press Reset button
* Let go Flush Button
* Upload code from Arduino IDE

## Run uploaded code on the device
* connect D3 to 3V and D8 to GND with jumper cables
* Press Reset button

## Deep sleep and Wakeup
https://www.losant.com/blog/making-the-esp8266-low-powered-with-deep-sleep
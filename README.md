ESP8266
=============
## bmp280_thingspeak.

Sends Temperature, humidity, altitude, Pressure, dew point, and wifi signal strength to Thingspeak.  
Also usefull boilerplate for sending a message through the GET method to a private webserver (like a raspberry pi).

## Hardware:

* Bosch [BME280 or BMP280](https://www.amazon.com/dp/B0118XCKTG/ref=cm_sw_r_tw_dp_x_5feozbVBZTRCQ) with i2c connection 
* esp8266 module [for example](https://www.amazon.com/dp/B01IK9GEQG/ref=cm_sw_r_tw_dp_x_DieozbD29KNYZ)

## Requirments and Install:

* Arduino IDE or similar that can load and send .ino files to the esp8266
* The library [ESP8266WiFi](https://github.com/esp8266/Arduino) to use arduino IDE to program esp8266. Follow install there first
* The library [BME280I2C](https://github.com/finitespace/BME280) found in the arduino package manager

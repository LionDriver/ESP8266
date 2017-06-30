ESP8266
=============
## bme280_Post_To_server
Sends Temperature, humidity, altitude, Pressure, dew point, and wifi signal strength through a POST to a server. See sensor.php for a receiving script example.

## How to setup the server (raspberry pi or other linux system):

* sudo apt-get update && sudo apt-get -y dist-upgrade
* sudo apt-get -y install lighttpd php5-common php5-cgi php5
* sudo lighttpd-enable-mod fastcgi-php
* Copy both sensor.php and debug.html to the /var/www/html directory
* sudo chown -R www-data:www-data /var/www/html
* sudo /etc/init.d/lighttpd force-reload

Make sure your www-data user has rights to write to debug.html (chmod a+rx debug.html)

## How to use:

Open up a browser and navigate to your server's ip/debug.html to view the latest sensor readings.

## Hardware:

* Bosch [BME280 or BMP280](https://www.amazon.com/dp/B0118XCKTG/ref=cm_sw_r_tw_dp_x_5feozbVBZTRCQ) with i2c connection 
* esp8266 module [for example](https://www.amazon.com/dp/B01IK9GEQG/ref=cm_sw_r_tw_dp_x_DieozbD29KNYZ)

## Requirments and Install for esp8266:

* Arduino IDE or similar that can load and send .ino files to the esp8266
* The library [ESP8266WiFi](https://github.com/esp8266/Arduino) to use arduino IDE to program esp8266. Follow install there first
* The library [BME280I2C](https://github.com/finitespace/BME280) found in the arduino package manager

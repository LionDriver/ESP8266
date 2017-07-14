ESP8266 Bosch bmp/bme280 environment sensor projects
=============

## bmp280_thingspeak

![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img5.JPG)
![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img1.JPG)
![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img7.png)

Sends temperature, humidity, altitude, pressure, dew point, and wifi signal strength to [Thingspeak](https://thingspeak.com/).  Thingspeak is a website that will read the post data sent to them and provide graphs, it makes an easy way to test out esp communication and if you don't want to spend your own time coding up something you can just use their stuff.

## bme280_Post_To_Server

Sends temperature, humidity, altitude, pressure, dew point, and wifi signal strength through a POST to a server. The hostname of the esp8266 is sent also so you can read from multiple sensors.  Also uses the esp deepsleep function which requires wiring the reset pin to gpio 16.  See sensor.php for a receiving script example.

## bme280_Post_To_Server_Mysql

Sends temperature, humidity, altitude, pressure, dew point, and wifi signal strength through a POST to a server. The hostname of the esp8266 is sent so you can read from multiple sensors.  Also uses the esp deepsleep function which requires wiring the reset pin to gpio 16.  sensor.php file reads the post and inserts the data into an Mysql database. Environment.php displays the sensor graphs (under construction).


![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img4.png)

## Hardware:

![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img2.JPG)
![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img3.JPG)
![alt text](https://github.com/slumbermachine/ESP8266/blob/master/images/img6.JPG)

* Bosch [BME280 or BMP280](https://www.amazon.com/dp/B0118XCKTG/ref=cm_sw_r_tw_dp_x_5feozbVBZTRCQ) with i2c connection
* esp8266 module [for example](https://www.amazon.com/dp/B01IK9GEQG/ref=cm_sw_r_tw_dp_x_DieozbD29KNYZ)

## Requirments and Install:

* Arduino IDE or similar that can load and send .ino files to the esp8266
* The library [ESP8266WiFi](https://github.com/esp8266/Arduino) to use arduino IDE to program esp8266. Follow install there first
* The library [BME280I2C](https://github.com/finitespace/BME280) found in the arduino package manager

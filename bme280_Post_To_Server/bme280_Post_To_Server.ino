/**
* bme280Post_To_Server.ino
* esp8266 with bmp280 sensor (atmosphere) with data post upload to webserver.
* Copyright 2017 SlumberMachine
* BME280 library is Copyright (C) 2016  Tyler Glenn
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* 
* Connecting the BME280 Sensor:
* Sensor              ->  Board
* -----------------------------
* Vin (Voltage In)    ->  3.3V
* Gnd (Ground)        ->  Gnd
* SDA (Serial Data)   ->  D2 (gpio 4) on ESP8266
* SCL (Serial Clock)  ->  D1 (gpio 5) on ESP8266
*/

#include <BME280I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

BME280I2C bme;
bool metric = false;
ESP8266WiFiMulti WiFiMulti;

// Wi-Fi Settings
const char* ssid = "XXXXXXXX"; // your wireless network name (SSID)
const char* password = "XXXXXXXX"; // your Wi-Fi network password
const char* host = "http://192.168.1.144/sensor.php";  //your server IP and receiving script


void setup() {
    Serial.begin(115200);
    while(!Serial) {} // Wait
    
    while(!bme.begin()){
      Serial.println("Could not find BME280 sensor!");
      delay(1000);
    }
    Serial.println();

    for(uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFiMulti.addAP(ssid, password);
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        long rssi = WiFi.RSSI();
        String strgth = String(rssi);
        Serial.print("Signal Strength: ");
        Serial.println(strgth);
        float temp(NAN), hum(NAN), pres(NAN);
        uint8_t pressureUnit(3);
        bme.read(pres, temp, hum, metric, pressureUnit);
        float altitude = bme.alt(metric);
        float dewPoint = bme.dew(metric);
        String body = "temp=";
            body += String(temp);
            body += "&hum=";
            body += String(hum);
            body += "&pres=";
            body += String(pres);
            body += "&strength=";
            body += strgth;
            body += "&alt=";
            body += String(altitude);
            body += "&dew=";
            body += String(dewPoint);
        HTTPClient http;
        Serial.print("Temp: " + String(temp));
        Serial.print("°"+ String(metric ? 'C' :'F'));
        Serial.print("\tHumidity: " + String(hum) + "% RH");
        Serial.print("\tPressure: " + String(pres) + " atm");
        Serial.print("\tAltitude: " + String(altitude));
        Serial.print((metric ? " m" : " ft"));
        Serial.print("\tDew point: " + String(dewPoint));
        Serial.println("°"+ String(metric ? 'C' :'F'));
        Serial.print("[HTTP] begin...\n");
        http.begin(host);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded", false, true);
       
        Serial.print("[HTTP] Sending POST\n");
        // start connection and send HTTP header
        int httpCode = http.POST(body);

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] POST result code: %d\n", httpCode);
        } else {
            Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
    delay(30000);
}

/*
bmp280_thingspeak.ino
Read from a bmp/bme-280 sensor with an ESP8266
Copyright 2017 SlumberMachine
BME280 library is Copyright (C) 2016  Tyler Glenn
Includes Thingspeak demo code Copyright Thingspeak

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Connecting the BME280 Sensor to ESP8266
Sensor              ->  Board
-----------------------------
Vin (Voltage In)    ->  3.3V
Gnd (Ground)        ->  Gnd
SDA (Serial Data)   ->  D2 on ESP8266
SCL (Serial Clock)  ->  D1 on ESP8266
*/

/* ==== Includes ==== */
#include <BME280I2C.h>
#include <ESP8266WiFi.h>

BME280I2C bme;                   // Default : forced mode, standby time = 1000 ms
                              // Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off,
bool metric = false;
const int postingInterval = 30 * 1000; // post data every 20 seconds

// Wi-Fi Settings
const char* ssid = "xxxxxxx"; // your wireless network name (SSID)
const char* password = "xxxxxx"; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
const int channelID = XXXXXXX; //write your channelID
String writeAPIKey = "XXXXXXXXXXXXXXXX"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";

void setup() {
  Serial.println("Connecting Wifi...");
  Serial.begin(115200);
  while(!Serial) {} // Wait
  while(!bme.begin()){
    Serial.println("Could not find BME280 sensor!");
    delay(1000);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if (client.connect(server, 80)) {
    float temp(NAN), hum(NAN), pres(NAN);
    uint8_t pressureUnit(3);                                    // unit: B000 = Pa, B001 = hPa, B010 = Hg, B011 = atm, B100 = bar, B101 = torr, B110 = N/m^2, B111 = psi
    bme.read(pres, temp, hum, metric, pressureUnit);            // Parameters: (float& pressure, float& temp, float& humidity, bool celsius = false, uint8_t pressureUnit = 0x0)
    float altitude = bme.alt(metric);
    float dewPoint = bme.dew(metric);

    Serial.print("Temp: " + String(temp));
    Serial.print("°"+ String(metric ? 'C' :'F'));
    Serial.print("\tHumidity: " + String(hum) + "% RH");
    Serial.print("\tPressure: " + String(pres) + " atm");
    Serial.print("\tAltitude: " + String(altitude));
    Serial.print((metric ? "m" : "ft"));
    Serial.print("\tDew point: " + String(dewPoint));
    Serial.println("°"+ String(metric ? 'C' :'F'));
    
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();
    String strgth = String(rssi);
    Serial.println("Connecting Wifi...");

    // Construct API request body
    String body = "field1=";
           body += String(temp);
           body += "&field2=";
           body += String(hum);
           body += "&field3=";
           body += String(pres);
           body += "&field4=";
           body += String(altitude);
           body += "&field5=";
           body += String(dewPoint);
           body += "&field6=";
           body += strgth;
           
    Serial.println("signal strength: " + strgth);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body.length());
    client.print("\n\n");
    client.print(body);
    client.print("\n\n");
    Serial.println("data sent");
  }
  client.stop();
  // wait and then post again
  delay(postingInterval);
}

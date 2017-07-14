#!/bin/bash
# esp8266 Environment Server Setup Script
# For use on Raspbian on Raspberry pi.
# Sets up lighttpd webserver and mysql database for recording in 
# sensor readings from esp8266 sensors. 
# MIT License
# Copyright (c) 2017 SlumberMachine
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


clear
echo "This is the Environment sensor server setup"
echo  "------------------------------------------"
if [ "$EUID" -ne 0 ]; then 
  echo "Please run using sudo"
  exit
fi

apt-get update && sudo apt-get -y dist-upgrade;
apt-get -y install lighttpd php5-common php5-cgi php5 php5-mysql
debconf-set-selections <<< 'mysql-server mysql-server/root_password password 23rdqw'
debconf-set-selections <<< 'mysql-server mysql-server/root_password_again password 23rdqw'
apt-get -y install mysql-server
lighttpd-enable-mod fastcgi-php;
echo '<?php $servername = "localhost"; $username = "monitor"; $password = "23rdqw"; $dbname = "sensors"; ?>' > db.php
mv db.php /var/www/html/
/etc/init.d/lighttpd force-reload
mysql -u root -p23rdqw -e "CREATE DATABASE sensors";
mysql -u root -p23rdqw -e "CREATE TABLE sensdat( sensId INT PRIMARY KEY AUTO_INCREMENT, hname VARCHAR(20), timepoint DATETIME, temp VARCHAR(10), hum VARCHAR(10), pres VARCHAR(10), alt VARCHAR(10), strgth VARCHAR(10), dew VARCHAR(10) );";
mysql -u root -p23rdqw -e "CREATE USER 'monitor'@'localhost' IDENTIFIED BY '23rdqw'";
mysql -u root -p23rdqw -e "GRANT ALL PRIVILEGES ON sensors.* TO 'monitor'@'localhost'";
mysql -u root -p23rdqw -e "FLUSH PRIVILEGES";
echo "Please copy the webserver files from the repository this script was found in to /var/www/html/"
echo "Then be sure to sudo chown -R www-data:www-data /var/www/html"
echo "Have a nice Flat Earth day!"

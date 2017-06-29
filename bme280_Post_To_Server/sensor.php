<?php
define('LBASE_DIR',dirname(__FILE__));
define('CONFIGFILE', 'sensor1.html');

error_reporting(E_ALL);

$temp = $_POST['temp'];
$hum  = $_POST['hum'];
$pres = $_POST['pres'];
$strgth = $_POST['strength'];
$alt = $_POST['alt'];
$dew = $_POST['dew'];

$fp = fopen(LBASE_DIR . '/' . CONFIGFILE, 'w');

fwrite($fp, "<html><title>Sensor Readings</title><body><ul><li>Temperature: ".$temp."&#176;F</li>\n");
fwrite($fp, "<li>Humidity: ".$hum."% rh</li>\n");
fwrite($fp, "<li>Pressure: ".$pres." atm</li>\n");
fwrite($fp, "<li>Altitude: ".$alt." ft</li>\n");
fwrite($fp, "<li>Dew Point: ".$dew."&#176;F</li>\n");
fwrite($fp, "<li>Signal Strength: ".$strgth." db</li>\n");
fwrite($fp, '</ul></body><script>setTimeout(function(){window.location.reload(1);}, 5000);</script></html>');

fclose($fp);
exit();

?>
<?php
define('LBASE_DIR',dirname(__FILE__));
define('CONFIGFILE', 'debug.html');

error_reporting(E_ALL);

$temp = $_POST['temp'];
$hum  = $_POST['hum'];
$pres = $_POST['pres'];
$strgth = $_POST['strength'];
$alt = $_POST['alt'];
$dew = $_POST['dew'];
$hostname = $_POST['hname'];

include "db.php";
$dbname = "sensors";
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO sensdat (hname, timepoint, temp, hum, pres, alt, strgth, dew) VALUES ('$hostname', now(),'$temp','$hum','$pres','$alt','$strgth','$dew')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();

$fp = fopen(LBASE_DIR . '/' . CONFIGFILE, 'w');

fwrite($fp, "<html><title>Sensor Readings</title><body><h1>Sensor Name: ".$hostname."</h1><ul><li>Temperature: ".$temp."&#176;F</li>\n");
fwrite($fp, "<li>Humidity: ".$hum."% rh</li>\n");
fwrite($fp, "<li>Pressure: ".$pres." atm</li>\n");
fwrite($fp, "<li>Altitude: ".$alt." ft</li>\n");
fwrite($fp, "<li>Dew Point: ".$dew."&#176;F</li>\n");
fwrite($fp, "<li>Signal Strength: ".$strgth." db</li></ul>\n");
fwrite($fp, "<p>".$sql."</p>");
fwrite($fp, '</body><script>setTimeout(function(){window.location.reload(1);}, 10000);</script></html>');
fclose($fp);

?>
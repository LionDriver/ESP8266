<?php
error_reporting(E_ALL);

include "db.php";
$dbname = "sensors";
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT * FROM sensdat ORDER BY sensId DESC LIMIT 1";
$result = $conn->query($sql);

if ($result === false){
    return "0";
}

$value = mysqli_fetch_array($result);
$temp = $value['temp'];
$hum = $value['hum'];
$strgth = $value['strgth'];
$dew = $value['dew'];
$alt = $value['alt'];
$timepoint = $value['timepoint'];
$hostname = $value['hname'];

$result = $conn->query("(SELECT * FROM sensdat ORDER BY sensId DESC LIMIT 144) ORDER BY sensId ASC");
    
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
        $clean = substr($row['timepoint'], 11, -3);
        $timearray[] = $clean;
        $temparray[] = $row['temp'];
    }
} else {
    echo "Problem in sql query";
}
$conn->close();
?>
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Environment Status</title>
  <link rel="stylesheet" href="./css/style.css">
  <link href="images/favicon.ico" rel="shortcut icon" type="image/x-icon" />
    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet">
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
</head>
<body>
  <div class="container">
    <h1 class="title page-header">Environment Status</h1>
    <a href=index.html ><span class="glyphicon glyphicon-home"></span><a/>
    <br>
    <br>
    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    <script type="text/javascript">
      google.charts.load('current', {'packages':['corechart']});
      google.charts.setOnLoadCallback(drawChart);
      var times = <?php echo json_encode($timearray);?>;
      var temps = <?php echo json_encode($temparray);?>;

      function drawChart() {
        var data = new google.visualization.DataTable();
        data.addColumn('string', 'Time');
        data.addColumn('number', 'Temperature');
        for (var i = 0; i < temps.length; i++) {
            data.addRow([times[i], parseInt(temps[i])]);
        }

        var options = {
          title: "<?php echo $hostname;?>" + ' Temperature',
          curveType: 'function',
          width: '1100',
          height: '400',
          legend: 'none',
          grid: 'true'
        };
        var chart = new google.visualization.LineChart(document.getElementById('curve_chart'));
        chart.draw(data, options);
      }
    </script>
  <div id="curve_chart" style="width: 1200px; height: 600px"></div>
  <br>
  <div class="container">
  <footer class="footer-bottom">
    <div class="container">
    <div class="col-xs-5 col-md-5">
    </div>
    <div class="col-xs-3 col-md-3">
    </div>
    <div class="col-xs-4 col-md-4">
      <p class="text-right text-muted">
      <span class="glyphicon glyphicon-wrench"></span>  
      Osteen Industries 2017&#8482</p>
    </div>
    </div>
  </footer>
  </div>
  <script src="js/jquery-3.2.1.slim.min.js"></script>
  <script src="js/bootstrap.min.js"></script>
  </body>
</html>

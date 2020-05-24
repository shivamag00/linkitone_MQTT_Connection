<!DOCTYPE html>
<html>
<head>
	<title>LinkIt Database</title>
	<style>
			#database {
				font-family: 'Trebuchet MS', Arial, Helvetica, sans-serif;
				border-collapse: collapse;
				width: 100%;
			}

			#database td, #database th {
				border: 1px solid #ddd;
				padding: 8px;
			}

			#database tr:nth-child(even){background-color: #f2f2f2;}

			#database tr:hover {background-color: #ddd;}

			#database th {
				padding-top: 12px;
				padding-bottom: 12px;
				text-align: left;
				background-color: #4CAF50;
				color: white;
			}
		}
		</style>
</head>
<body>
	<div style="float:right">
	<table id="database">
		<tr>
			<th>Time</th>
			<th>Temperature</th>
		</tr>
		<?php

			$servername = "localhost";
			$username = "username";
			$password = "password";
			$dbname = "mediatek";

			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) 
			{
				die("Connection failed: " . $conn->connect_error);
			} 
			$sql = "SELECT Time, Temperature FROM temperature";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "<tr><td>" . $row["Time"]. "</td><td>" . $row["Temperature"]. "</td><td>";
				}
			} 
			else 
			{
				echo "0 results";
			}
			$conn->close();
		?>
	</table>
	</div>

	<div style="float:right">
	<table id="database">
		<tr>
			<th>Time</th>
			<th>Latitude</th>
			<th>Longitude</th>
		</tr>
		<?php
			$servername = "localhost";
			$username = "username";
			$password = "password";
			$dbname = "mediatek";

			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) 
			{
				die("Connection failed: " . $conn->connect_error);
			} 

			$sql = "SELECT Time, Latitude, Longitude FROM gps";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "<tr><td>" . $row["Time"]. "</td><td>" . $row["Latitude"].  "</td><td>" . $row["Longitude"]. "</td></tr>";
				}
			} 
			else 
			{
				echo "0 results";
			}
			$conn->close();
		?>
	</table>
	</div>
	
	<div style="float:right">
	<table id="database">
		<tr>
			<th>Time</th>
			<th>Tilt</th>
		</tr>
		<?php

			$servername = "localhost";
			$username = "username";
			$password = "password";
			$dbname = "mediatek";

			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) 
			{
				die("Connection failed: " . $conn->connect_error);
			} 
			$sql = "SELECT Time, Tilt FROM tilt";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "<tr><td>" . $row["Time"]. "</td><td>" . $row["Tilt"]. "</td><td>";
				}
			} 
			else 
			{
				echo "0 results";
			}
			$conn->close();
		?>
	</table>
	</div>
	
	<div style="float:right">
	<table id="database">
		<tr>
			<th>Time</th>
			<th>Light</th>
		</tr>
		<?php

			$servername = "localhost";
			$username = "username";
			$password = "password";
			$dbname = "mediatek";

			// Create connection
			$conn = new mysqli($servername, $username, $password, $dbname);
			// Check connection
			if ($conn->connect_error) 
			{
				die("Connection failed: " . $conn->connect_error);
			} 
			$sql = "SELECT Time, Light FROM light";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "<tr><td>" . $row["Time"]. "</td><td>" . $row["Light"]. "</td><td>";
				}
			} 
			else 
			{
				echo "0 results";
			}
			$conn->close();
		?>
	</table>
	</div>
	
	
	
</body>
</html>
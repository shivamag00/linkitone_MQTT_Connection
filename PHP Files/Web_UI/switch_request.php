<!DOCTYPE html>
<html>
<head>
	<title>Control Database</title>
</head>
<body>
	<div style="float:right">
	<table>
		<tr>
			<th>Time</th>
			<th>Temp Control</th>
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
			$sql = "SELECT Time, Control FROM ctrl_temp";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "<tr><td>" . $row["Time"]. "</td><td>" . $row["Control"]. "</td><td>";
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

	<div style="float-right">
	<table>
		<tr>
			<th>Time</th>
			<th>GPS Control</th>
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

			$sql = "SELECT Time, Control FROM ctrl_gps";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "<tr><td>" . $row["Time"]. "</td><td>" . $row["Control"].  "</td></tr>";
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
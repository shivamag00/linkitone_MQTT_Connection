<!DOCTYPE html>
<html>
	<head>
			<style>
					html, body {
					height:100%;
					margin: 0;
					padding: 0;
								}
					#map {
						height: 100%;
						}
			</style>
			<meta http-equiv="refresh" content="9">
			
	</head>
	<body>
	
	
	
			<div id="map"></div>
			
			<script>
			var map;
			function initMap() 
			{
				var mapoptions = {
									
									center: {lat: <?php
															$servername = "localhost";
															$username = "username";
															$password = "password";
															$dbname = "mediatek";

															// Create connection
															$conn = new mysqli($servername, $username, $password, $dbname);
															// Check connection
															if ($conn->connect_error) {
																die("Connection failed: " . $conn->connect_error);
															} 

															$sql = "SELECT Latitude, Longitude FROM gps ORDER BY Time DESC LIMIT 1";
															$result = $conn->query($sql);

															if ($result->num_rows > 0) {
																// output data of each row
																while ($row = $result->fetch_assoc()) {
																	echo $row["Latitude"];
																	//lng: $row["Longitude"];
																}
															} 
															else {
																echo "0 results";
															}
															$conn->close();
														?>, lng: <?php
															$servername = "localhost";
															$username = "username";
															$password = "password";
															$dbname = "mediatek";

															// Create connection
															$conn = new mysqli($servername, $username, $password, $dbname);
															// Check connection
															if ($conn->connect_error) {
																die("Connection failed: " . $conn->connect_error);
															} 

															$sql = "SELECT Latitude, Longitude FROM gps ORDER BY Time DESC LIMIT 1";
															$result = $conn->query($sql);

															if ($result->num_rows > 0) {
																// output data of each row
																while ($row = $result->fetch_assoc()) {
																//	lat: $row["Latitude"];
																	echo $row["Longitude"];
																}
															} 
															else {
																echo "0 results";
															}
															$conn->close();
														?>},
									zoom: 16.2
								}
				map = new google.maps.Map(document.getElementById('map'), mapoptions);
				 
				
				if (navigator.geolocation) 
				{
							navigator.geolocation.watchPosition(myposition,error);
								function myposition(position) 
									{
										var pos = {
													lat: <?php
															$servername = "localhost";
															$username = "username";
															$password = "password";
															$dbname = "mediatek";

															// Create connection
															$conn = new mysqli($servername, $username, $password, $dbname);
															// Check connection
															if ($conn->connect_error) {
																die("Connection failed: " . $conn->connect_error);
															} 

															$sql = "SELECT Latitude, Longitude FROM gps ORDER BY Time DESC LIMIT 1";
															$result = $conn->query($sql);

															if ($result->num_rows > 0) {
																// output data of each row
																while ($row = $result->fetch_assoc()) {
																	echo $row["Latitude"];
																	//lng: $row["Longitude"];
																}
															} 
															else {
																echo "0 results";
															}
															$conn->close();
														?>,
													lng: <?php
															$servername = "localhost";
															$username = "username";
															$password = "password";
															$dbname = "mediatek";

															// Create connection
															$conn = new mysqli($servername, $username, $password, $dbname);
															// Check connection
															if ($conn->connect_error) {
																die("Connection failed: " . $conn->connect_error);
															} 

															$sql = "SELECT Latitude, Longitude FROM gps ORDER BY Time DESC LIMIT 1";
															$result = $conn->query($sql);

															if ($result->num_rows > 0) {
																// output data of each row
																while($row = $result->fetch_assoc()) {
																//	lat: $row["Latitude"];
																	echo $row["Longitude"];
																}
															} 
															else {
																echo "0 results";
															}
															$conn->close();
														?>
												  };
										var marker = new google.maps.Marker
												  ({
													position: pos,
													map: map,
													title: "You are here",
												  });
            
									}
								function error() 
									{
										alert("Your browser does not support geolocation");
									}
				}
			}

      		
			</script>
			<script async defer 
			src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBpQgqMEYBufZmRmf09L_JviWPWIlc9jmc&v=3&callback=initMap">
			</script>
			
			
			
	</body>
</html>

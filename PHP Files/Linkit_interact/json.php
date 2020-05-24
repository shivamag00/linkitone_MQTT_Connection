<?php
		$data = json_decode($_POST['json'],true);

		echo '
		
		<!DOCTYPE html>
			<html lang="en">    
			<head>
				<meta charset="UTF-8">    
				<title>Add Record Form</title>
				<style>
						label
						{
							float:left;
							width:200px;
						}
				</style>
				<script>
					function tp()
					{
						document.getElementById("dem1").click();
						document.getElementById("dem2").click();
						document.getElementById("dem3").click();
						document.getElementById("dem4").click();
					}
				</script>
			</head>

			<body>
				<form action="./linkit_forms/temperature.php" method="post" target="_blank">
					<p>
        				<label>Temperature:</label>
        				<input type="text" name="temp" value="'.$data['Temperature'].'" id="TMP" >    
    				</p>
						<input type="submit" value="Submit" id="dem1">
				</form>
				<form action="./linkit_forms/gps.php" method="post" target"_blank">
    				<p>
        				<label>Latitude:</label>
        				<input type="text" name="lat" value="'.$data['Latitude'].'" id="LAT" >    
    				</p>
    				<p>    
        				<label>Longitude:</label>
       					<input type="text" name="long" value="'.$data['Longitude'].'" id="LONG" >    
    				</p>
	
						<input type="submit" value="Submit" id="dem2">
				</form>
				<form action="./linkit_forms/tilt.php" method="post" target="_blank">
					<p>
        				<label>Tilt:</label>
        				<input type="text" name="tilt" value="'.$data['Tilt'].'" id="TMP" >    
    				</p>
						<input type="submit" value="Submit" id="dem3">
				</form>
				<form action="./linkit_forms/light.php" method="post" target="_blank">
					<p>
        				<label>Light:</label>
        				<input type="text" name="light" value="'.$data['Light'].'" id="TMP" >    
    				</p>
						<input type="submit" value="Submit" id="dem4">
				</form>
				<script>
				tp();
				</script>
			</body>
			</html>'

?>
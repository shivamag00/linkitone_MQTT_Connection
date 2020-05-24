<?php

    /* Attempt MySQL server connection. Assuming you are running MySQL
    server with default setting (user 'root' with no password) */

    $link = mysqli_connect("localhost", "username", "password", "mediatek");

    // Check connection

    if($link === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }

    // Escape user inputs for security
    $tp = mysqli_real_escape_string($link, $_POST['tup']);
    
    // attempt insert query execution
    $sql = "INSERT INTO tup (Value) VALUES ('$tp')";

    if(mysqli_query($link, $sql)){
        echo "Records added successfully.";
    } else{
        echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
    }

    // close connection
    mysqli_close($link);
	
	echo '
	
		<script src="https://cdnjs.cloudflare.com/ajax/libs/paho-mqtt/1.0.1/mqttws31.js" type="text/javascript"></script>
		<script type = "text/javascript" language = "javascript">
			var mqtt;
			var reconnectTimeout = 2000;
			var host="192.168.1.127"; //change this
			//var host="iot.eclipse.org"
			//var port=80
			var port=1884;
			
			function onFailure(message) 
			{
				console.log("Connection Attempt to Host "+host+"Failed");
				setTimeout(MQTTconnect, reconnectTimeout);
			}
			
			function onConnect() 
			{
		  // Once a connection has been made, make a subscription and send a message.
				console.log("Connected ");
				message = new Paho.MQTT.Message("'.$_POST['tup'].'");
				message.destinationName = "3tup";
				mqtt.send(message);
			}
		</script>
		<script>
		console.log("connecting to "+ host +" "+ port);
				mqtt = new Paho.MQTT.Client(host,port,"clientjs");
				//document.write("connecting to "+ host);
				var options = {
					timeout: 3,
					onSuccess: onConnect,
					onFailure: onFailure,
							};
				mqtt.connect(options); //connect
		</script>
	';
	
	
	
	
	
?>
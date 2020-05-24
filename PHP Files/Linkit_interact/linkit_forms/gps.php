<?php

    /* Attempt MySQL server connection. Assuming you are running MySQL
    server with default setting (user 'root' with no password) */

    $link = mysqli_connect("localhost", "username", "password", "mediatek");

    // Check connection

    if($link === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }

    // Escape user inputs for security
    
    $lat = mysqli_real_escape_string($link, $_POST['lat']);
    $long = mysqli_real_escape_string($link, $_POST['long']);



    // attempt insert query execution
    $sql = "INSERT INTO gps (Latitude, Longitude) VALUES ('$lat', '$long')";

    if(mysqli_query($link, $sql)){
        echo "Records added successfully.";
    } else{
        echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
    }

    // close connection
    mysqli_close($link);
	echo "<script>window.close();</script>";
?>
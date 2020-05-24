<?php

    /* Attempt MySQL server connection. Assuming you are running MySQL
    server with default setting (user 'root' with no password) */
set_time_limit(60);
    $link = mysqli_connect("localhost", "username", "password", "mediatek");

    // Check connection

    if($link === false){
        die("ERROR: Could not connect. " . mysqli_connect_error());
    }



//---------------------------------------------------------------------------
$sql = "SELECT Value FROM tup ORDER BY Time DESC LIMIT 1";

			$result = $link->query($sql);
			$row = $result->fetch_assoc(); 
			$temp_up=$row["Value"];
			
$sql = "SELECT Value FROM ulow ORDER BY Time DESC LIMIT 1";

			$result = $link->query($sql);
			$row = $result->fetch_assoc(); 
			$temp_down=$row["Value"];



//--------------------------------------------------------------------------





    // Escape user inputs for security
    $tp = mysqli_real_escape_string($link, $_POST['tilt']);
	if (($tp>$temp_up || $tp <$temp_down) && $tp != 'f')
	{
		 require("PHPMailer-master/src/PHPMailer.php");
			require("PHPMailer-master/src/SMTP.php");

    $mail = new PHPMailer\PHPMailer\PHPMailer();
    $mail->IsSMTP(); // enable SMTP

    $mail->SMTPDebug = 1; // debugging: 1 = errors and messages, 2 = messages only
    $mail->SMTPAuth = true; // authentication enabled
    $mail->SMTPSecure = 'ssl'; // secure transfer enabled REQUIRED for Gmail
    $mail->Host = "smtp.gmail.com";
    $mail->Port = 465; // or 587
    $mail->IsHTML(true);
    $mail->Username = "______________________";
    $mail->Password = "______________________";
    $mail->SetFrom("______________________");
    $mail->Subject = "Tilt Threshold Breached";
    $mail->Body = "Tilt exceeded. Check it!!<br>Upper Threshold=".$temp_up."<br>Lower Threshold=".$temp_down."<br>Current Tilt=".$tp;
    $mail->AddAddress("______________________");

     if(!$mail->Send()) {
        echo "Mailer Error: " . $mail->ErrorInfo;
     } else {
        echo "Message has been sent";
     }
	}
    
    // attempt insert query execution
    $sql = "INSERT INTO tilt (Tilt) VALUES ('$tp')";

    if(mysqli_query($link, $sql)){
        echo "Records added successfully.";
    } else{
        echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
    }
	

    // close connection
    mysqli_close($link);
	echo "<script>window.close();</script>";
?>
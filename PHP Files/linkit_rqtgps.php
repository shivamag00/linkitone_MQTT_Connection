
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

			$sql = "SELECT Time, Control FROM ctrl_gps ORDER BY Time DESC LIMIT 1";
			$result = $conn->query($sql);

			if ($result->num_rows > 0) 
			{
				// output data of each row
				while($row = $result->fetch_assoc()) 
				{
					echo "Sidsat" . $row["Control"];
				}
			} 
			else 
			{
				echo "0 results";
			}
			$conn->close();
		?>
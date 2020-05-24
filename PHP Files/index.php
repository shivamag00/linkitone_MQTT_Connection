<!DOCTYPE html>
<html>
<head>
	<title>Linkit One IOT Device</title>
	<link href="fonts.css" rel="stylesheet">
	
	<style>
		body{
			background-color: #a29bfe;
		}
		.title{
			margin-left: 39.5%;
			color: red;
			font-family: 'Libre Baskerville', serif;
		}
		.header{
			margin-left: 40%;
			font-family: 'Tomorrow', sans-serif;
		}
		.mainBody{
			margin-top: 10%;
			margin-left: 20%;
		}
		.btn{
			background-color: #636e72;
			font-family: 'Ubuntu', sans-serif;
			font-size: 26px;
			height: 200px;
			width: 200px;
			border-radius: 50%;
		}
	</style>
</head>

<body>

<div class="container">
	<div class="title"><h1>SCM EXPERTS</h1></div>
	<div class="header"><h2>Linkit One IOT Project</h2></div>
	
	<div class="mainBody">
		<form method="POST">
			<button class="btn switch_page" formaction="./Web_UI/control_form.html">Switches</button>
			<button class="btn threshold_page" formaction="./Web_UI/threshold_form.html">Threshold</button>
			<button class="btn delay_page" formaction="./Web_UI/frequency_form.html">Delays</button>
			<button class="btn database_page" formaction="./Web_UI/request.php">Live Database</button>		
		</form>
	</div>
</div>

</body>

</html>
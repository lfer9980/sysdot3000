<?php
//página se actualice automáticamente cada 15 segundos
$page = $_SERVER['PHP_SELF'];
$sec = "15";

/*Incluimos el database_connect.php que tiene los datos para la conexión a la base de datos */
include("database_connect.php"); 

/* checar conexion */
if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
/* De nuevo, sacamos la tabla de la base de datos, cuyo nombre es ESPtable2 en este caso*/
$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select
?>


<html>
<head>
	<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
	<meta charset="UTF-8">
	<meta http-equiv="X-UA-Compatible" content="IE=edge">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="stylesheet" href="style.css">
	<title>Sistema domotico 3000</title>
	<link rel="shortcut icon" href="./favicon.png">
</head>

<body>
	<h1>Hola!</h1>
	<h2>Visualiza todo el panel de control desde aqui</h2>

	<section>
		<h3>Sistema General de controles REMOTO</h3>
		<table class='table'>
			<tbody>
				<tr class='active'>
					<td><b>id</b></td>
					<td><b>lamp 1 </b> </td>
					<td><b>lamp 2 </b> </td>
					<td><b>lamp 3 </b> </td>
					<td><b>lamp 4 </b> </td>
					<td><b>lamp 5 </b> </td>
				</tr>
	
				<?php				
				//recorrer la tabla e imprimir los datos en la tabla
				while($row = mysqli_fetch_array($result)) {
					echo "<tr class='success'>"; 	
					$unit_id = $row['id'];
					echo "<td>" . $row['id'] . "</td>";
	
					$column1 = "RECEIVED_BOOL1";
					$column2 = "RECEIVED_BOOL2";
					$column3 = "RECEIVED_BOOL3";
					$column4 = "RECEIVED_BOOL4";
					$column5 = "RECEIVED_BOOL5";
	
					$current_bool_1 = $row['RECEIVED_BOOL1'];
					$current_bool_2 = $row['RECEIVED_BOOL2'];
					$current_bool_3 = $row['RECEIVED_BOOL3'];
					$current_bool_4 = $row['RECEIVED_BOOL4'];
					$current_bool_5 = $row['RECEIVED_BOOL5'];
	
					if($current_bool_1 == 1) {
						$inv_current_bool_1 = 0;
						$text_current_bool_1 = "ON";
						$color_current_bool_1 = "#6ed829";
					}
					else {
						$inv_current_bool_1 = 1;
						$text_current_bool_1 = "OFF";
						$color_current_bool_1 = "#e04141";
					}
	
					if($current_bool_2 == 1) {
						$inv_current_bool_2 = 0;
						$text_current_bool_2 = "ON";
						$color_current_bool_2 = "#6ed829";
					}
					else{
						$inv_current_bool_2 = 1;
						$text_current_bool_2 = "OFF";
						$color_current_bool_2 = "#e04141";
					}
	
					if($current_bool_3 == 1) {
						$inv_current_bool_3 = 0;
						$text_current_bool_3 = "ON";
						$color_current_bool_3 = "#6ed829";
					}
					else {
						$inv_current_bool_3 = 1;
						$text_current_bool_3 = "OFF";
						$color_current_bool_3 = "#e04141";
					}
	
					if($current_bool_4 == 1) {
						$inv_current_bool_4 = 0;
						$text_current_bool_4 = "ON";
						$color_current_bool_4 = "#6ed829";
					}
					else {
						$inv_current_bool_4 = 1;
						$text_current_bool_4 = "OFF";
						$color_current_bool_4 = "#e04141";
					}
	
					if($current_bool_5 == 1) {
						$inv_current_bool_5 = 0;
						$text_current_bool_5 = "ON";
						$color_current_bool_5 = "#6ed829";
					}
					else {
						$inv_current_bool_5 = 1;
						$text_current_bool_5 = "OFF";
						$color_current_bool_5 = "#e04141";
					}
				}
				?>
				<!-- IMPRESION DE BOTONES TABLA 1 -->
				<?php
				echo "
				<td>
					<form action= update_values.php method= 'post'>
						<input type='hidden' name='value2' value=$current_bool_1   size='15' >	
						<input type='hidden' name='value' value=$inv_current_bool_1  size='15' >	
						<input type='hidden' name='unit' value=$unit_id >
						<input type='hidden' name='column' value=$column1 >
						<input type= 'submit' name= 'change_but' style='background-color: $color_current_bool_1' value=$text_current_bool_1>
					</form>
				</td>";
					
				echo "
				<td>
					<form action= update_values.php method= 'post'>
						<input type='hidden' name='value2' value=$current_bool_2   size='15' >	
						<input type='hidden' name='value' value=$inv_current_bool_2 size='15' >	
						<input type='hidden' name='unit' value=$unit_id >
						<input type='hidden' name='column' value=$column2 >
						<input type= 'submit' name= 'change_but' style='background-color: $color_current_bool_2' value=$text_current_bool_2>
					</form>
				</td>";
	
				echo "
				<td>
					<form action= update_values.php method= 'post'>
						<input type='hidden' name='value2' value=$current_bool_3   size='15' >	
						<input type='hidden' name='value' value=$inv_current_bool_3 size='15' >	
						<input type='hidden' name='unit' value=$unit_id >
						<input type='hidden' name='column' value=$column3 >
						<input type= 'submit' name= 'change_but' style='background-color: $color_current_bool_3' value=$text_current_bool_3>
					</form>
				</td>";
	
				echo "
				<td>
					<form action= update_values.php method= 'post'>
						<input type='hidden' name='value2' value=$current_bool_4   size='15' >	
						<input type='hidden' name='value' value=$inv_current_bool_4 size='15' >	
						<input type='hidden' name='unit' value=$unit_id >
						<input type='hidden' name='column' value=$column4 >
						<input type= 'submit' name= 'change_but' style='background-color: $color_current_bool_4' value=$text_current_bool_4>
					</form>
				</td>";
	
				echo "
				<td>
					<form action= update_values.php method= 'post'>
						<input type='hidden' name='value2' value=$current_bool_5   size='15' >	
						<input type='hidden' name='value' value=$inv_current_bool_5 size='15' >	
						<input type='hidden' name='unit' value=$unit_id >
						<input type='hidden' name='column' value=$column5 >
						<input type= 'submit' name= 'change_but' style='background-color: $color_current_bool_5' value=$text_current_bool_5>
					</form>
				</td>";
				?>
			</tr>
			</tbody>
		</table>
	</section>

	<section>
		<h3>temperatura actual</h3>
		<p>Vizualiza la temperatura actual del sistema</p>
		<div>
		<?php
			include("database_connect.php");

			if (mysqli_connect_errno()) {
				echo "Failed to connect to MySQL: " . mysqli_connect_error();
			}

			$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select

			while($row = mysqli_fetch_array($result)) {
				echo "<span>" . $row['SENT_TEMP'] . "</span> <span> °C </span>";
			}
		?>
		</div>
	</section>

	<section>
		<h3>Alarma temperatura</h3>
		<div>
		<?php
			include("database_connect.php");

			if (mysqli_connect_errno()) {
				echo "Failed to connect to MySQL: " . mysqli_connect_error();
			}
			
			$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select
			
			while($row = mysqli_fetch_array($result)) {		
				$cur_sent_bool_1 = $row['SENT_ALARM'];

				if($cur_sent_bool_1 == 1){
					$label_sent_bool_1 = "label-success";
					$text_sent_bool_1 = "Active";
				}
				else {
					$label_sent_bool_1 = "label-danger";
					$text_sent_bool_1 = "Inactive";
				}
				echo "
				<span class = 'label $label_sent_bool_1'>"
				. $text_sent_bool_1 . "</span>";
			}
		?>
		</div>
	</section>

	<section>
		<h3> Control de la alarma de temperatura</h3>
		<p>Elige la temperatura que será la base para activar la alarma</p>
		<?php
		include("database_connect.php");

		if (mysqli_connect_errno()) {
			echo "Failed to connect to MySQL: " . mysqli_connect_error();
		}

		$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select

		while($row = mysqli_fetch_array($result)) {		
			$column6 = "RECEIVED_CONT_TEMP";
			$current_num_1 = $row['RECEIVED_CONT_TEMP'];
		}
		?>
		<div>
		<?php
			echo "
			<form action= update_values.php method= 'post'>
				<input type='text' name='value' style='width: 120px;' value= $current_num_1  size='15' >
				<input type='hidden' name='unit' style='width: 120px;' value=$unit_id >
				<input type='hidden' name='column' style='width: 120px;' value=$column6 >
				<input type= 'submit' name= 'change_but' style='width: 120px; text-align:center;' value='cambiar valor'>
			</form>";
		?>
		</div>
	</section>
</body>
</html>
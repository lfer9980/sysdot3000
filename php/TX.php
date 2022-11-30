<?php
/*
	Este archivo debe recibir un enlace algo así: http://sysdot3000.000webhostapp.com/TX.php?unit=1&b1=1
	Si pegas ese enlace en tu navegador, debería actualizar el valor de b1 con este archivo TX.php. Lea más detalles a continuación.
	El ESP enviará un enlace como el de arriba pero con algo más que b1. Tendrá b1, b2, etc...
*/

//Hacemos un bucle y tomamos las variables de la URL recibida
//Guarda el valor recibido en la variable key. Guarda cada carácter después del "&"
foreach ($_REQUEST as $key => $value) {
	//Ahora detectamos si recibimos el id, la contraseña, la unidad, o un valor para actualizar
	if ($key == "id") {
		$unit = $value;
	}
	if ($key == "pw") {
		$pass = $value;
	}
	if ($key == "un") {
		$update_number = $value;
	}

	if ($update_number == 1) {
		if ($key == "n1") {
			$sent_temp = $value;
		}
	} else if ($update_number == 2) {
		if ($key == "b1") {
			$sent_alarm = $value;
		}
	}
}

include("database_connect.php"); 	

if (mysqli_connect_errno()) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

//Now we update the values in database
//If the received data is for SENT_NUMBER_1, we update that value
if ($update_number == 1) {
	mysqli_query($con, "UPDATE ESPtable2 SET SENT_TEMP = $sent_temp WHERE id=$unit AND PASSWORD=$pass");

} else if ($update_number == 2) {
	mysqli_query($con, "UPDATE ESPtable2 SET SENT_ALARM = $sent_alarm, WHERE id=$unit AND PASSWORD=$pass");;
}



//In case that you need the time from the internet, use this line
date_default_timezone_set('UTC');
$t1 = date("gi"); 	/* return 1:23 as 123 */

//Get all the values form the table on the database
$result = mysqli_query($con, "SELECT * FROM ESPtable2");

/* Recorrer la tabla y filtrar los datos para esta identificación de unidad igual a la que hemos recibido.  */
while ($row = mysqli_fetch_array($result)) {
	if ($row['id'] == $unit) {
		/* Actualizamos los valores del booleano y los números que recibimos del Arduino, y luego nos hacemos eco del booleano */
		//y números y el texto de la base de datos de vuelta al Arduino
		$b1 = $row['RECEIVED_BOOL1'];
		$b2 = $row['RECEIVED_BOOL2'];
		$b3 = $row['RECEIVED_BOOL3'];
		$b4 = $row['RECEIVED_BOOL4'];
		$b5 = $row['RECEIVED_BOOL5'];

		$n1 = $row['RECEIVED_CONT_TEMP'];

		/* La siguiente línea se hará eco de los datos de vuelta al Arduino */
		echo "_t1$t1##_b1$b1##_b2$b2##_b3$b3##_b4$b4##_b5$b5##_n1$n1##";
	}
}
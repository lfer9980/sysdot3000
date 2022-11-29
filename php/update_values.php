<?php
//Este archivo obtendrá los valores cuando haga clic en cualquiera de los botones ON/OFF o de cambio en el archivo index.php
//Obtenemos ese valor y lo enviamos a la tabla database y con ello actualizamos los valores
$value = $_POST['value'];    //Get the value
$unit = $_POST['unit'];      //Get the id if the unit where we want to update the value
$column = $_POST['column'];    //Which column of the database, could be the RECEIVED_BOOL1, etc...

//connect to the database
include("database_connect.php"); //We include the database_connect.php which has the data for the connection to the database

// Check the connection
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

//Now update the value sent from the post (ON/OFF, change or send button)
mysqli_query($con, "UPDATE ESPtable2 SET $column = '{$value}'
WHERE id=$unit");

//go back to the interface
header("location: index.php");

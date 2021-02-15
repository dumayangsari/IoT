<?php
	include ('connection.php');
	$sql_insert = "INSERT INTO pembukaan (idcard, nomor_parkiran) VALUES ('".$_GET["idcard"]."', '".$_GET["nomor_parkiran"]."')";

	$lama = 1;
	$query = "DELETE FROM pembukaan WHERE date_diff(CURDATE(), tanggal) > $lama";
	$hasil = mysqli_query($query);

	if(mysqli_query($con,$sql_insert))
	{
		echo "Done";
		mysqli_close($con);
	}
	else
	{
		echo "error is ".mysqli_error($con );
	}

?>
<?php
include ('connection.php');
	$Query = mysqli_query($con, "SELECT * FROM pembukaan INNER JOIN penguncian WHERE penguncian.idcard = pembukaan.idcard AND penguncian.nomor_parkiran = pembukaan.nomor_parkiran ORDER BY pembukaan.id DESC");

	$RecordSet = mysqli_fetch_array($Query);
	echo "idcard: $RecordSet[idcard]<br>";
	echo "nomor_parkiran: $RecordSet[nomor_parkiran]<br>";
?>
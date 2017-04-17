<!DOCTYPE html>
<html lang="en">
	<?php
	  include 'php/template.php';
	  head('Addison Snyder - Portfolio', 'This page stores your referrer.');
	  if ($_SERVER["REQUEST_METHOD"] == "POST") {
 		$refer = test_input($_POST["refer"]);
    	$dbRefer = new SQLite3('refer.db');
    	$stmt = $dbRefer->prepare("INSERT INTO Refer VALUES (?, ?)");
    	$stmt->bindParam(1, $refer);
    	$stmt->bindParam(2, date("Y-m-d H:m:s",time()));
    	$stmt->execute();
	}else{
		die();
	}
	?>
  <body>
  </body>
</html>
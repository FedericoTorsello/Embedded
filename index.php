<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8" />
		<title>Jimmy Challenge</title>
		<meta http-equiv="X-UA-Compatible" content="IE=edge" />
		<meta content="width:device-width, initial-scale=1.0" name="viewport">
		<link type="image/x-icon" hred="images/favicon.ico" rel="shortcut icon">
		<script src="https://code.jquery.com/jquery-1.12.3.min.js"></script>
		<script src="js/script.js" type="text/javascript"></script>
	</head>
	<body>
		<?php
			//session_set_cookie_params(0, '/', 'www.embedded16.duckdns.org', isset($_SERVER["HTTPS"]), true);
			//session_start();
			print_r($_SESSION);
			require_once("config/conf.inc.php");
			require_once("phplibs/JWS.php");
			$j = new JWTAuth(RSA_PASS);
			$j->isValid();
		?>
	</body>
</html>

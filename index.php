<!DOCTYPE html>
<html>
	<head>
		<meta charset='utf-8' />
		<title>Jimmy Challenge</title>
		<meta http-equiv='X-UA-Compatible' content='IE=edge' />
		<meta content='width:device-width, initial-scale=1.0' name='viewport'>
		<link type='image/x-icon' href='images/favicon.ico' rel='shortcut icon'>
		<meta name='viewport' content='width=device-width,initial-scale=1'>
		<link rel='stylesheet' href='css/normalize.css'>
		<link rel='stylesheet' href='css/font-awesome/css/font-awesome.min.css'>
		<link rel='stylesheet' href='css/layout.css'>
		<link rel='stylesheet' href='css/style.css'>
		<link rel='stylesheet' href='css/progressbar.css'>
	</head>
	<body>
	<?php
	require __DIR__ . '/phplibs/JWS.php';
	// check if the users is logged, authenticated or clean the session and return to login
	if (isset($_COOKIE['sessionID']))
		$jwt = new JWTAuth($_COOKIE['sessionID']);
	session_start();
	if (!isset($_COOKIE['sessionID'], $_SESSION['username']) || !$jwt->isValid() || !session_status()) {
		if (isset($_COOKIE['sessionID'])) {
			setcookie($_COOKIE['sessionID'], '' , 1);
			setCookie($_COOKIE['sessionID'], false);
			unset($_COOKIE);
			session_unset();
			session_destroy();
		}
		header('Location: login.html');
		exit;
	}
	?>
	<div class='content'>
		<div class='top'></div>
		<div class='row'>
			<div class='whole header'>
				<h1 class='icon'>JimmyChallenge</h1>
			</div>
		</div>
		<div class='row'>
			<div class='one-fifth columns sidebar'>
				<p class='menu'>Welcome <b class='icon'><?php echo htmlspecialchars($_SESSION['username']); ?></b>
					<button class='logout'><i class="fa fa-sign-out icon" aria-hidden="true"></i>Logout</button>
				</p>
				<div class='row'>
					<small>Select a user to start playing</small>
					<div id='listUsers' class='whole'></div>
					<div class='row'>
						<div class='whole chat'>
							<p>Room chat <i class="fa fa-comments-o icon" aria-hidden="true"></i></p>
							<ul class='message-list'></ul>
							<input type='text' autocomplete='off' placeholder='Message' id='send-message'/>
						</div>
					</div>
				</div>
			</div>
			<div class='four-fifths columns main'>
				<div class='whole'><h2>Remote</h2></div>
				<div class='row'>
					<h3>Distance</h3>
					<div class='whole'>
						<div class='remote distance'></div>
					</div>
				</div>
				<div class='row timer'>
					<div class='six columns'>
						<h3>Wait to open</h3>
						<div class='remote open'></div>
					</div>
					<div class='six columns'>
						<h3>Break alarm</h3>
						<div class='remote broken'></div>
					</div>
				</div>
				<div class='row'>
					<div class='three columns'>
						<p>Actual Level:</p><h1 class="remote level">1</h1>
					</div>
					<div class='nine columns'>
						<p>Status:</p><h4 class="remote status">Wait for someone to play!</h4>
					</div>

				</div>

			</div>
		</div>
		<div class='row footer'>
				<div class='whole'>
					<div class='one-third column'>
						<i class='fa fa-github icon' aria-hidden='true'></i>
						<a target='_blank' href='https://github.com/FedericoTorsello/Embedded.git'>GitHub</a>
					</div>
					<div class='one-third column'>
						<i class='fa fa-copyright icon' aria-hidden='true'></i>2016
						<a href='#'>JimmyChallenge</a>
					</div>
					<div class='one-third column contact'>
						<i class='fa fa-envelope icon' aria-hidden='true'></i>
					</div>
				</div>
		</div>
	</div>
	<script src='https://code.jquery.com/jquery-2.2.4.min.js'></script>
	<script src='https://code.jquery.com/ui/1.11.4/jquery-ui.min.js'></script>
	<script src='js/browser.js'></script>
	<script src='js/progressbar.min.js' type='text/javascript'></script>
	<script src='js/gameProgress.js' type='text/javascript'></script>
	<script src='js/script.js' type='text/javascript'></script>
	<script src='js/chat.js' type='text/javascript'></script>
	<img src="images/key.png" class='fixed-bottom'>
	</body>
</html>

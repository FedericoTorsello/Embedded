/* window.ready */
$(function() {
	// bind the logout button to logout function
	$('.logout').on('click', function() {
		req.sendPost({'request': 'logout'}, function() {
			// clean cookies (the server will try to clean them anyway)
			document.cookie = 'sessionID' + '=; expires=Thu, 01 Jan 1970 00:00:01 GMT;';
			document.cookie = 'game' + '=; expires=Thu, 01 Jan 1970 00:00:01 GMT;';
			document.cookie = 'PHPSESSID' + '=; expires=Thu, 01 Jan 1970 00:00:01 GMT;';
			window.location.reload();
		});
	});

	// sync the height
	$('.main, .sidebar').height($('.content').height());

	// Create content to 'Contact' link (should avoid problems with spam bot)
	$('.contact').append('<a href="mailto:edoardo.rosa@studio.unibo.it,federico.torsello@studio.unibo.it">Contact</a>');
});

// create a usefull wrapper to send post HTTP request to server API using JSON
class JSONRequest {
	constructor() {
		this._serviceURL = '/api/';
		this._timeout = 700;
		this._cookieName = 'sessionID';
	};

	// get the cookie to send with the payload
	_getCookie(_name) {
		var name = _name + '=';
		var ca = document.cookie.split(';');
		for (var i = 0; i < ca.length; i++) {
			var c = ca[i];
			while (c.charAt(0) == ' ') c = c.substring(1);
			if (c.indexOf(name) == 0)
				return c.substring(name.length, c.length);
		}
	}

	// use AJAX to send JSON POST request
	sendPost(_dataJSON, callback) {
		var data = _dataJSON;
		data.JWSAuth = this._getCookie(this._cookieName);
		$.ajax({
			url:			this._serviceURL,
			dataType:		'json',
			contentType:    'application/json',
			type:			'POST',
			isLocal:        true,
			processData:	true,
			error:			this._HandleError,
			complete:       callback,
			data:			JSON.stringify(data),
		});
	};

	// if an error occout print to console
	_HandleError(err) {
		console.log(err.status);
	}
};
let req = new JSONRequest();

// send login informations
function send_auth(user, pass) {
	var data = {
		request: "auth",
		username: user,
		password: pass
	};
	req.sendPost(data, function(data) {
		switch(data.status) {
			case 200:
				// if credentials are correct the server returns 200 'OK', redirect to index
				top.location.href = JSON.parse(data.responseText).response;
				break;
			case 403:
				// wrong credentials, show an error
				form = document.getElementById('login');
				form.classList.add('error_1');
				setTimeout(function () {
					form.classList.remove('error_1');
				}, 3000);
				break;
		}
	});
}

// send information for a new user
function register_user(user, pass, email) {
	var data = {
		request: 'register',
		username: user,
		password: pass,
		email: email
	};
	req.sendPost(data);
}

// send a configuration request to stat a new game
function start_game(local, remote) {
	// inform all users that a new game will starts
	var data = {
		request: 'send_message',
		message: local + ' invited ' + remote + ' to play!'
	}
	req.sendPost(data);
	// instructs the server to create channels and SSE for a new game
	var data = {
		request: 'start_game',
		remoteuser: remote
	}
	req.sendPost(data, function(data) { console.log(data); });
	subscribe_game();
}

var serviceURL = 'phplibs/api.php';
var data = '{"key": "valasd", "key1": "value1"}';

console.log("OK");

class JSONRequest {

	constructor(url, to) {
		this._serviceURL = url;
		this._timeout = to;
		this._cookieName = 'sessionID';
	};

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

	sendPost(_dataJSON) {
		var data = JSON.parse(_dataJSON);
		data.JWSAuth = this._getCookie(this._cookieName);
		console.log(data);
		$.ajax({
			url:			this._serviceURL,
			dataType:		'json',
			type:			'POST',
			processData:	true,
			timeout:		this._timeout,
			success:		this._GetPost,
			error:			this._HandleError,
			data:			JSON.stringify(data),
		});
	};

	_GetPost(data) {
		console.log(data);
	};

	_HandleError(err) {
		console.log(err.status);
	}

};

let req = new JSONRequest(serviceURL, data);
req.sendPost(data);

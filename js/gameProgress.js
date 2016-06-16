// during the window loading show a nice progress bar on top page
window.addEventListener("load", function () {
	new ProgressBar.Line('.top', {
		trokeWidth: 4,
		easing: 'easeInOut',
		duration: 700,
		color: '#FFEA82',
		trailColor: '#eee',
		trailWidth: 1,
		svgStyle: {width: '100%', height: '100%'},
		to: {color: '#FFEA82'},
		from: {color: '#ED6A5A'},
		step: (state, bar) => {
			bar.path.setAttribute('stroke', state.color);
		}
	}).animate(1.0);
	// hide the nice progress bar on top page after finish
	setTimeout(function() { $('.top').css('display', 'none'); } , 700);
});

// wrapper of semicircle progress bar
function SemiCircle_bar_factory(className, fromC, toC) {
	return new ProgressBar.SemiCircle(className, {
		strokeWidth: 5,
		trailColor: '#eee',
		trailWidth: 5,
		easing: 'linear',
		duration: 50,
		from: {color: fromC},
		to: {color: toC},
		svgStyle: { autoStyleContainer: false, height: '120px', width: '100%'},
		step: (state, bar) => {
			bar.path.setAttribute('stroke', state.color);
			var value = Math.round(bar.value() * 100);
			if (value === 0) {
				bar.setText('');
			} else {
				bar.setText(value);
			}

			bar.text.style.color = state.color;
		}
	});
}

// wrapper of horizontal progress bar
function Line_bar_factory(className, fromC, toC) {
	return new ProgressBar.Line(className, {
		trailColor: '#222',
		trailWidth: 1,
		easing: 'linear',
		duration: 300,
		from: {color: fromC},
		to: {color: toC},
		svgStyle: { autoStyleContainer: false, height: '10px', width: '100%'},
		step: (state, bar) => {
			bar.path.setAttribute('stroke', state.color);
			var value = Math.round(bar.value() * 100);
			if (value === 0) {
				bar.setText('');
			} else {
				bar.setText(value);
			}

			bar.text.style.color = state.color;
		}
	});
}

// create the 3 progress bar for distance and game status
var bar = SemiCircle_bar_factory('.remote.distance', '#005af5', '#2ECC71');
var barOpen = Line_bar_factory('.remote.open', '#F04949', '#2ECC71');
var barBroken = Line_bar_factory('.remote.broken', '#2ECC71', '#F04949');

// when a game starts subscribe the user to game SSE, this function permite to see progress of the opponent player
function subscribe_game() {
	var _domlevel = document.getElementsByClassName('remote level')[0];
	var _domstatus = document.getElementsByClassName('remote status')[0];
	_domstatus.innerHTML = 'Waiting for connecitions...';
	game = new EventSource('/phplibs/gameSSE.php');
	// add an event listener for the distance changes and animate the bar
	game.addEventListener('info', function(e) {
		if (e.data != 'null') {
			var _data = JSON.parse(e.data);
			var _dist = Math.abs(parseInt(_data.distance));
			bar.animate(1 - (_dist / 100));
			var _status = parseInt(_data.status);
			var _level = parseInt(_data.level);
			_domlevel.innerHTML = _level;
			switch (_status) {
				case 0:
					_domstatus.innerHTML = "NOOB!";
					barOpen.animate(0);
					barBroken.animate(0);
					break;
				case 101:
					_domstatus.innerHTML = "Padlock found...";
					barOpen.animate((_status - 100) * 0.2);
					break;
				case 102:
					_domstatus.innerHTML = "lock-picking";
					barOpen.animate((_status - 100) * 0.2);
					break;
				case 103:
					_domstatus.innerHTML = "It's not so easy...";
					barOpen.animate((_status - 100) * 0.2);
					break;
				case 104:
					_domstatus.innerHTML = "Wait for it!";
					barOpen.animate((_status - 100) * 0.2);
					break;
				case 105:
					_domstatus.innerHTML = "Quick! Open the lock!";
					barOpen.animate((_status - 100) * 0.2);
					break;
				case 201:
					_domstatus.innerHTML = "Go! Go!";
					barBroken.animate((_status - 200) * 0.2);
					break;
				case 202:
					_domstatus.innerHTML = "Warning!";
					barBroken.animate((_status - 200) * 0.2);
					break;
				case 203:
					_domstatus.innerHTML = "It will break!";
					barBroken.animate((_status - 200) * 0.2);
					break;
				case 204:
					_domstatus.innerHTML = "MOOOOOVE!!";
					barBroken.animate((_status - 200) * 0.2);
					break;
				case 205:
					_domstatus.innerHTML = "Jimy is broken! Retry!";
					barBroken.animate((_status - 200) * 0.2);
					break;
			}
			if (_status > 300 && _status < 400) {
				_domstatus.innerHTML = "Level passed!";
			}
			if (_status === 500) {
				_domstatus.innerHTML = "Congratulations! You pick all locks!<p>GAME OVER!</p>";
				_domlevel.innerHTML = "";
				game.close();
			}

		}
	},false);
}

// add an event listener for the game status changes and animate the bar
function handle_status(s) {
	console.log(s);
}

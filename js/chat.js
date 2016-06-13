// retrieve the users list
get_users();
window.setInterval(function(){
	get_users();
}, 20000);


// subscribe to chat SSE service
setTimeout(function() {
	var source = new EventSource('/phplibs/chatSSE.php');
	source.addEventListener('message', function(e) { handle_chat(e); }, false);
	source.addEventListener('list_users', function(e) { list_users(JSON.parse(e.data)); }, false);
	// Workaround for Firefox browsers
	if ($.browser.mozilla)
		source.addEventListener('ping', function() {}, false);
}, 700);

// send POST to retrieve users list
function get_users() {
	var data = { request: 'list_users' };
	req.sendPost(data, function(d) { list_users(JSON.parse(d.responseText).response); });
}

// callback for get_users: display the results
function list_users(data) {
	if (data != null) {
		var data = data.users;
		list = document.getElementById('listUsers');
		list.innerHTML = '';
		var ul = $('<ul/>').appendTo(list);
		var u = document.getElementsByClassName('menu')[0].children[0].innerHTML;
		$.each(data, function(i) {
			if (data[i] === u) {
				data[i] += ' <i class="fa fa-user" aria-hidden="true"></i>';
				var li = $('<li/>').addClass('icon').append(data[i]).appendTo(ul);
			}else {
				var li = $('<li/>').addClass('icon').append(data[i]).appendTo(ul).click(function () { start_game(u, data[i]); });
			}
		});
	}
}

// bind the key event (return pressed) to send a message in chat
$("#send-message").keyup(function(event){
	var input = $('#send-message');
	if (event.keyCode == 13 && input.val().trim().length > 0){
		var user = document.getElementsByClassName('menu')[0].children[0].innerHTML;
		var data = {
			request: 'send_message',
			message: input.val()
		}
		req.sendPost(data, function(data) {
			if (data.status === 200)
				input.val('');
		});
	}
});

// if a message is received from the sever display it
function handle_chat(data) {
	var user = document.getElementsByClassName('menu')[0].children[0].innerHTML;
	var chat = $('.message-list');
	if (data.origin !== window.location.origin) {
		source.close();
		return;
	} else {
		var msg = JSON.parse(data.data);
		if (msg != null) {
			var li = $('<li/>').addClass('message wordwrap').appendTo(chat);
			if (msg.user === user)
				var span = $('<span/>').addClass('user').text(msg.user).appendTo(li);
			else
				var span = $('<span/>').addClass('users').text(msg.user).appendTo(li);
			li.append(': ' + msg.msg);
			// if the size of the chat window is too big remove oldest messages
			while(parseInt(chat.height()) >= 210)
				$('.message-list li').first().remove();
		}
	}
}

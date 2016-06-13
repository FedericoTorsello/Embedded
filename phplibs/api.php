<?php
require_once __DIR__ . '/Rest.inc.php';
require_once __DIR__ . '/JWS.php';
require_once __DIR__ . '/MysqlLib.php';

Use Sse\Data;

session_start();

class API extends REST {
	public $data = '';

	private $db;
	private $jws;
	private $redis_chat = array('server' => array('port' => 3501, 'password' => REDIS_PASS, 'database' => 0));
	private $redis_users = array('server' => array('port' => 3501, 'password' => REDIS_PASS, 'database' => 1));
	private $redis_game = array('server' => array('port' => 3501, 'password' => REDIS_PASS, 'database' => 2), 'gc_lifetime' => 2);

	public function __construct() {
		parent::__construct();
		$this->db = new MysqlLib();
	}

	// for each request parse the content and response
	public function processApi() {
		// if is an 'auth' request check credentials and login the user
		if (isset($this->_request['request'], $this->_request['username'], $this->_request['password']) && $this->_request['request'] === 'auth') {
			$user = $this->_request['username']?? '';
			$pass = $this->_request['password']?? '';
			$this->login($user, $pass);
			return;
		}
		// if in a 'register' request parse and validate the input and, if valid, insert the information in DB
		if (!isset($this->_request['JWSAuth']) && isset($this->_request['request'], $this->_request['username'], $this->_request['password'], $this->_request['email'])) {
			if ($this->_request['request'] === 'register') {
				if ($this->insert_user($this->_request['username'], $this->_request['password'], $this->_request['email']))
					$this->response('Success', 200);
				else
					$this->response('Information not valid', 403);
			}
			return;
		}
		// If the user is authenticaded validate is token
		$this->jws = new JWTAuth($this->_request['JWSAuth']?? $_COOKIE['sessionID']);
		if ($this->jws->isValid() && isset($this->jws->getPayload()['username'], $this->_request['request'])) {
			// retrieve the username
			$gusername = $this->jws->getPayload()['username'];
			// parse the request field
			switch ($this->_request['request']) {
			case 'list_users':
				// list all users connected and logged
				$search_logged = 'SELECT username FROM users WHERE logged=1;';
				// set a keepalive flag for this user
				$keepalive = 'UPDATE users SET logged = 1 WHERE username = ?;';
				$this->db->query($keepalive, $gusername);
				$res = $this->db->query($search_logged);
				$users = array();
				while($r = $res->fetch_assoc())
					$users[] = $r['username'];
				$this->response(array('users' => $users), 200);
				break;
			case 'logout':
				// set the user state and clean all cookies then destroy the data session
				$this->db->query('UPDATE users SET logged = 0 WHERE username = ?;', $gusername);
				$data = new Data('redis', $this->redis_users);
				$search_logged = 'SELECT username FROM users WHERE logged = 1;';
				$res = $this->db->query($search_logged);
				$users = array();
				while($r = $res->fetch_assoc())
					$users[] = $r['username'];
				// inform all users
				$data->set('list_users', json_encode(
					array(
						'users' => $users,
						'time' => time()
					)
				));
				setcookie($_COOKIE['sessionID'], '' , 1);
				setCookie($_COOKIE['sessionID'], false);
				setcookie($_COOKIE['game'], '' , 1);
				setCookie($_COOKIE['game'], false);
				unset($_COOKIE);
				session_unset();
				session_destroy();
				session_write_close();
				$this->response('https://embedded16.duckdns.org', 307);
				break;
			case 'send_message':
				// a message is sent from the client chat -> send to all other users
				$data = new Data('redis', $this->redis_chat);
				if (isset($this->_request['message'])) {
					$data->set('message', json_encode(
						array(
							'msg' => htmlentities($this->_request['message']),
							'time' => time(),
							'user' => $this->jws->getPayload()['username']
						)
					));
					$this->response('Received',200);
				} else {
					$this->response('Message Malformed', 406);
				}
				break;
			case 'start_game':
				// a game is started set the cookie with the opponent name (TODO: improve)
				if (isset($this->_request['remoteuser'])) {
					setcookie('game', base64_encode($this->_request['remoteuser']));
					$this->response('Game started', 200);
				} else
					$this->response('Invalid request', 403);
				break;
			case 'update_info':
				// a message with an update of the distance is sent from $gusername
				if (isset($this->_request['distance'], $this->_request['status'], $this->_request['level'])) {
					$data = new Data('redis', $this->redis_game);
					$data->set("info $gusername", json_encode(
						array(
							'distance' => $this->_request['distance'],
							'status'   => $this->_request['status'],
							'level'    => $this->_request['level']
						)
					));
					$this->response('OK', 200);
				} else {
					$this->response('Invalid request', 403);
				}
				break;
			default:
				$this->response('Invalid request', 404);
				break;
			}
		} else
			$this->response('Invalid token', 403);
		// if the request is invalid inform the sender
	}

	// register an user if the information provided are valid
	private function insert_user($user, $pass, $email):bool {
		if (strlen($user) <= 15 && strlen($user) > 0 && strlen($pass) >= 6 && filter_var($email, FILTER_VALIDATE_EMAIL)) {
			$insert_user = 'INSERT INTO users(username, password, email) VALUES (?, ?, ?);';
			$check_user = 'SELECT id FROM users WHERE username = ?;';
			$res = $this->db->query($check_user, $user);
			if (isset($res) && $res->fetch_assoc()['id'] >= 1)
				return false;
			else {
				// store the hashed password
				$hash = password_hash($pass, PASSWORD_DEFAULT);
				$this->db->query($insert_user, $user, $hash, $email);
				return true;
			}
		}
		return false;
	}

	// check if a users is logged
	private function isLogged($name):bool {
		$check = 'SELECT id FROM users WHERE username = ? LIMIT 1';
		$res = $this->db->query($check, $name)->fetch_assoc();
		return isset($res)?? false;
	}

	// login a user given username and password
	private function login($user, $pass) {
		if (isset($user, $pass) && $this->search_user($user, $pass)) {
			$data = new Data('redis', $this->redis_users);
			$search_logged = 'SELECT SQL_CACHE username FROM users WHERE logged=1;';
			$res = $this->db->query($search_logged);
			$users = array();
			while($r = $res->fetch_assoc())
				$users[] = $r['username'];
			// update the connected users list
			$data->set('list_users', json_encode(
				array(
					'users' => $users,
					'time' => time()
				)
			));
			// regenerate the cookie session
			session_regenerate_id(true);
			$_SESSION['username'] = $user;
			$_SESSION['expires'] = time() + 15;
			// create a JWT
			$this->jws = new JWTAuth();
			$this->jws->setCookie($user);
			$this->response('index.php', 200);
		} else {
			$this->response('Wrong Credentials', 403);
		}
	}

	// given an usernae and password check if the credentials are correct
	private function search_user($user, $pass):bool {
		$check = 'SELECT id, username,password FROM users WHERE username=? LIMIT 1';
		$login = 'SELECT * FROM users WHERE username=? AND password=?';
		$res = $this->db->query($check, $user)->fetch_assoc();
		if (isset($res) && password_verify($pass, $res['password'])) {
			$logged = 'UPDATE users SET logged = 1 WHERE id = ?;';
			$this->db->query($logged, intval($res['id']));
			return true;
		}
		return false;
	}
}

// Process request
$api = new API;
$api->processApi();

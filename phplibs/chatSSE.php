<?php
require_once __DIR__ . '/../vendor/autoload.php';
require_once __DIR__ . '/../config/conf.inc.php';

use Sse\Data;
use Sse\SSE;
use Sse\Event;

// create a data instance which is shared across all data instances with Server-Sent Events
$sse = new SSE();

// settings for redis DB
$redis_chat = array('server' => array('port' => 3501, 'password' => REDIS_PASS, 'database' => 0));
$redis_users = array('server' => array('port' => 3501, 'password' => REDIS_PASS, 'database' => 1));
$data_chat = new Data('redis', $redis_chat);
$data_users = new Data('redis', $redis_users);

// check for new messages and broadcast them to all subscribers
class LatestMessage implements Event {
	private $cache = 0;
	private $data;
	private $storage;
	private $key;

	public function __construct($key, $data) {
		$this->storage = $data;
		$this->key = $key;
	}

	public function update(){
		return json_encode($this->data);
	}

	public function check(){
		global $sse;
		// fetch
		$this->data = json_decode($this->storage->get($this->key));

		// if is a reconnection do not send information; save last time update
		if($this->cache == 0 && $sse->is_reconnect){
			$this->cache = $this->data->time;
			return false;
		}

		// if a new message needs to be sent return true
		if(isset($this->data->time) && $this->data->time !== $this->cache){
			$this->cache = $this->data->time;
			return true;
		}
		
		return false;
	}
};

// Ping workaround for Firefox browsers
class Ping implements Event {
	private $time;
	public function __construct() {
		$this->time = 0;
	}
	public function update() {}
	
	public function check(){
		if ($this->time < time()) {
			$this->time = time() + 1;
			return true;
		}
		return false;
	}
};

$sse->exec_limit = 10;
$sse->client_reconnect = 0.1;
$sse->sleep_time = 0.1;

// add the event handles, the client will subscribe to them
$sse->addEventListener('', new LatestMessage('message', $data_chat));
$sse->addEventListener('list_users', new LatestMessage('list_users', $data_users));
$sse->addEventListener('ping', new Ping());

// start the loop.
$sse->start();

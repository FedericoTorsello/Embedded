<?php
require_once __DIR__ . '/../vendor/autoload.php';
require_once __DIR__ . '/../config/conf.inc.php';

use Sse\Data;
use Sse\SSE;
use Sse\Event;

$redis = array('server' => array('port' => 3501, 'password' => REDIS_PASS, 'database' => 2));
$data = new Data('redis', $redis);

$sse = new SSE();

class LatestInfo implements Event {
	private $distance = 0;
	private $status = 0;
	private $data;
	private $user;
	private $storage;
	private $key;

	public function __construct($key, $data) {
		$this->storage = $data;
		// check the data for the opponent player stored in the cookie
		$this->user = base64_decode($_COOKIE['game']);
		$this->key = $key . " " . $this->user;
	}

	public function update(){
		return json_encode($this->data);
	}

	// retrieve and send data if updated
	public function check(){
		$this->data = json_decode($this->storage->get($this->key));
		if($this->data->distance !== $this->distance || $this->data->status != $this->status) {
			$this->distance = $this->data->distance;
			$this->status = $this->data->status;
			return true;
		}
		return false;
	}
};

$sse->exec_limit = 10;
$sse->client_reconnect = 0.01;
$sse->sleep_time = 0.01;

$sse->addEventListener('info', new LatestInfo('info', $data));

$sse->start();

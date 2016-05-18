<?php
require_once("Rest.inc.php");
require_once("../config/conf.inc.php");
require_once('../phplibs/JWS.php');

class API extends REST {
	public $data = "";

	private $db = NULL;

	public function __construct() {
		parent::__construct();
		#$this->db = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
	}

	public function processApi() {
		$j = new JWTAuth(RSA_PASS);
		if (isset($this->_request["gimme"]) && $this->_request["gimme"] == "cookie")
			$j->setCookie();
		else {
			if ($j->isValid())
				$this->response("OK", 200);
			else
				$this->response(array('response' => 'Invalid token'), 200);
		}
	}

	// Encode array into JSON
	private function json($data) {
		if(is_array($data)) {
			return json_encode($data);
		}
	}
}

$api = new API;
$api->processApi();

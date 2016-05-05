<?php
require_once("Rest.inc.php");
require_once("../config/conf.inc.php");

class API extends REST {
    public $data = "";

    private $db = NULL;

    public function __construct() {
		parent::__construct();
		$this->db = mysqli_connect(DB_HOST, DB_USER, DB_PASS, DB_NAME);
    }

	public function processApi() {
		$this->response($_POST, 200);
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

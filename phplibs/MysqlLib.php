<?php

require_once __DIR__ . '/../config/conf.inc.php';

class MysqlLib {
	private $db_host;
	private $db_name;
	private $db_user;
	private $db_pass;
	private $db;

	public function __construct() {
		$this->db_host = DB_HOST;
		$this->db_name = DB_NAME;
		$this->db_user = DB_USER;
		$this->db_pass = DB_PASS;
		$this->connect();
	}
	
	// connect to DB using Mysqli (TODO: switch to PDO)
	private function connect() {
		$this->db = new mysqli($this->db_host,
			$this->db_user,
			$this->db_pass,
			$this->db_name);
		if (mysqli_connect_error()) {
			die('Connect Error('.mysqli_connect_errno().') '.mysqli_connect_error());
		}
		$this->db->set_charset('utf8');
	}

	// check is the connection to DB is open
	private function check_connection() {
		if (!is_null($this->db) && !($this->db->ping()))
			$this->connect();
	}

	// utils to create array type for `bind_param` function
	private function typeOf($var) {
		switch (gettype($var)) {
		case 'string':
			return 's';
		case 'integer':
			return 'i';
		case 'double':
			return 'd';
		case 'blob':
			return 'b';
		}
	}

	// prepare and execute the query, return the results
	public function query($query, ...$param) {
		if (substr_count($query, '?') === count($param)) {
			$a_param = array();
			$t = '';
			foreach($param as &$p) {
				$t .= $this->typeOf($p);
				$a_param[] = &$p;
				unset($p);
			}
			array_unshift($a_param, $t);
			$this->check_connection();
			if ($stmt = $this->db->prepare($query)) {
				if (count($param) > 0)
					call_user_func_array(array($stmt, 'bind_param'), $a_param);
				$stmt->execute();
				$result = $stmt->get_result();
				return $result;
			}
		}
	}
}
?>

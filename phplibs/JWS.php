<?php
require_once __DIR__ . '/../vendor/autoload.php';
require_once __DIR__ . '/../config/conf.inc.php';
use Namshi\JOSE\SimpleJWS;

class JWTAuth {
	private $privateKey;
	private $publicKey;
	private $alg = 'RS512';
	private $cookieName = 'sessionID';
	private $jws;

	public function __construct($value=NULL) {
		// read public and private key
		$this->publicKey = openssl_pkey_get_public("file:///usr/share/nginx/html/embedded/config/public.key");
		$this->privateKey = openssl_pkey_get_private("file:///usr/share/nginx/html/embedded/config/private.key", RSA_PASS);
		if (isset($value))
			$this->jws = SimpleJWS::load($value);
		else
			$this->jws = new SimpleJWS(array('alg' => $this->alg));
	}

	public function setCookie($username) {
		// set a payload (WARNING: no sinsible information)
		$this->jws->setPayload(array('uid' => session_id(), 'username' => $username));
		$this->jws->sign($this->privateKey);
		// set the encrypted and signed cookie
		setcookie($this->cookieName, $this->jws->getTokenString(), 0, '/', '', true, false);
	}

	// check is a JWS is valid
	public function isValid() : bool {
		return $this->jws->isValid($this->publicKey, $this->alg);
	}

	// return the payload of the JWS cookie
	public function getPayload() {
		if ($this->isValid()) {
			return $this->jws->getPayload();
		}
	}
}

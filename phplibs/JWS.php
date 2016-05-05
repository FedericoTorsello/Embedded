<?php

require __DIR__ . '/../vendor/autoload.php';	
use Namshi\JOSE\SimpleJWS; 

class JWTAuth {

	private $privateKey;
	private $publicKey;
	private $alg = 'RS512';	
	private $jws;

	public function __construct($passphrase) {
		$this->publicKey = openssl_pkey_get_public("file:///usr/share/nginx/html/embedded/config/public.key");
		$this->privateKey = openssl_pkey_get_private("file:///usr/share/nginx/html/embedded/config/private.key", $passphrase);
		
		$this->jws = new SimpleJWS(array( 'alg' => $this->alg));
		
		// payload could be the username
		$this->jws->setPayload(array( 'uid' => 'embedded16'));
		$this->jws->sign($this->privateKey);
		setcookie('sessionID', $this->jws->getTokenString(), 0, '/', '', true, true);
	}

	public function isValid() : bool {
		print_r($this->jws->getPayload());
		return $this->jws->isValid($this->publicKey, $this->alg);
	}
}

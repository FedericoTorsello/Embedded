CREATE TABLE IF NOT EXISTS users (
	id int(3) NOT NULL AUTO_INCREMENT PRIMARY KEY,
	created DATETIME DEFAULT CURRENT_TIMESTAMP,
	username varchar(15) COLLATE utf8_general_ci NOT NULL,
	password varchar(255) COLLATE utf8_general_ci NOT NULL,
	email varchar(30) COLLATE utf8_general_ci NOT NULL,
	keepalive DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
	logged boolean NOT NULL DEFAULT 0,
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;

ALTER TABLE users ADD INDEX logged_index(logged);

SET GLOBAL event_scheduler = ON;

DELIMITER $$
CREATE EVENT IF NOT EXISTS `keepalive_logged`
	ON SCHEDULE EVERY 1 MINUTE STARTS '2016-06-01 00:00:00'
	ON COMPLETION PRESERVE
DO BEGIN
	UPDATE users SET logged = 0
	WHERE TIMESTAMPDIFF(SECOND, keepalive, now()) >= 20;
END;$$
DELIMITER ;
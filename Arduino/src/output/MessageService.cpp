#include "MessageService.h"

/** Variable for the serial event from Arduino */
String contentArduino = "";
MessageService msgService;
int i = 0;

/**@brief ###Init the serial and print a welcome message
 *
 * @param[in] baud The baud rate of the serial
 * @param[in] name The message to print
 */
void MessageService::init(const int baud, const String &name) {
    while(!Serial) { }
    Serial.begin(baud);
    Serial.println(name);
    Serial.flush();
}

/**@brief ###Parse a message from the serial
 *
 * When a message is readed is parsed and if is valid reply with an ACK
 * @param[in] msg The message received
 */
void MessageService::setMessage(const String msg) {
    this->currentMsg = msg;
    if (!msg.equals("")) {
        // Allocate a buffer to parse the JSON
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(msg);
        // If the message is valid
        if (root.success() && root.containsKey("payload") && root.containsKey("from") && root.containsKey("to")) {
            String content = root["payload"].asString();
            String sender = root["from"].asString();
            String receiver = root["to"].asString();
            // Send an ACK
            this->ackMsg(sender);
        } else {
            // Otherwise send an error
            msgService.errorMsg();
        }
    }
    this->currentMsg = "";
}

/**@brief ###Send a message error using JSON */
void MessageService::errorMsg() {
    String p = "";
    StaticJsonBuffer<35> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["payload"] = "Parse Error";
    root.printTo(p);
    Serial.println(p);
    Serial.flush();
}

/**@brief ###Send an ACK using JSON */
void MessageService::ackMsg(const String to) {
    String p = "";
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["to"] = to;
    root["payload"] = "ACK";
    root.printTo(p);
    Serial.println(p);
    Serial.flush();
}

/**@brief ###Send a message using JSON
 *
 * Create and send a JSON message to a receiver.
 * @param[in] content The content of the message
 * @param[in] receiver The receiver of the message
 */
void MessageService::sendMsg(const String content, const String receiver) {
    String p = "";
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["to"] = receiver;
    root["msg"] = content;
    root.printTo(p);
    Serial.println(p);
    Serial.flush();
}

/**@brief ###Send a service message using JSON
 *
 * Create and send a JSON message with informations about the status of the game.
 * @param[in] distance The distance read from the sonar
 * @param[in] status The status of the game or the lockpicking phase
 * @param[in] to The receiver of the message
 */
void MessageService::sendInfo(const int distance, const int status, const uint8_t level, const String to) {
    String p = "";
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["to"] = to;
    root["distance"] = distance;
    root["status"] = status;
    root["level"] = level;
    root.printTo(p);
    Serial.println(p);
    Serial.flush();
}

/**@brief ###When a serial event occurs read the message
 *
 * Read all bytes from the serial until a new line is detected and a message is created.
 */
void serialEvent() {
    while(Serial.available()) {
        // read byte by byte
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
            // flush garbage if present
            while (Serial.available() > 0) { Serial.read(); }
            if (i > 1) {
                msgService.setMessage(contentArduino);
                contentArduino = "";
            }
            i = 0;
        } else {
            i++;
            contentArduino += inChar;
        }
    }
}

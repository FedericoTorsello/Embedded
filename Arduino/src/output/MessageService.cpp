#include "MessageService.h"

String contentArduino = "";
MessageService msgService;
int i = 0;

void MessageService::init(const int baud, const String &name) {
    Serial.begin(baud);
    while(!Serial) { }
    Serial.println(name);
    Serial.flush();
}

void MessageService::setMessage(const String msg) {
    this->currentMsg = msg;
    if (!msg.equals("")) {
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(msg);
        Serial.println("REC " + this->currentMsg);
        if (root.success() && root.containsKey("msg") && root.containsKey("from") && root.containsKey("to")) {
            String content = root["msg"].asString();
            String sender = root["from"].asString();
            String receiver = root["to"].asString();
            Msg m(content, sender, receiver);
            msgService.ackMsg(sender);
        } else {
            msgService.errorMsg();
        }
    }
    this->currentMsg = "";
}

void MessageService::errorMsg() {
    String p = "";
    StaticJsonBuffer<35> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["msg"] = "Parse Error";
    root.printTo(p);
    Serial.println(p);
    Serial.flush();
}

void MessageService::ackMsg(const String to) {
    String p = "";
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["to"] = to;
    root["msg"] = "ACK";
    root.printTo(p);
    Serial.println(p);
    Serial.flush();
}

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

/* from arduino environment */
void serialEvent() {
    while(Serial.available()) {
        // read byte by byte
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
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

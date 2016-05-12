#include "MessageService.h"

String contentArduino = "";
MessageService msgService;
int i = 0;

void MessageService::init(const int baud, const String&  name) {
    Serial.begin(baud);
    while(!Serial) { }
    Serial.println(name);
    Serial.flush();
}

void MessageService::setMessage(String msg) {
    this->currentMsg = msg;
    if (!msg.equals("")) {
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(msg);
        if (root.success()) {
            String content = root["msg"].asString();
            String sender = root["from"].asString();
            String receiver = root["to"].asString();
            Msg m(content, sender, receiver);
        } else {
            msgService.errorMsg();
        }
    }
    this->currentMsg = "";
}

void MessageService::errorMsg(String to) {
    // default: to = "all"
    StaticJsonBuffer<50> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = "arduinoCore";
    root["to"] = to;
    root["msg"] = "Parse Error";
    root.printTo(Serial);
}

void MessageService::sendMsg(String content, String sender, String receiver) {
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = sender;
    root["to"] = receiver;
    root["msg"] = content;
    root.printTo(Serial);
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

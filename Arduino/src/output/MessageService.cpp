#include "MessageService.h"

String contentArduino = "";
MessageService msgService;
int i = 0;

void MessageService::init(const int baud, const String &name, Context *c) {
    while(!Serial) { }
    Serial.begin(baud);
    Serial.println(name);
    Serial.flush();
    pContext = c;
}

void MessageService::setMessage(const String msg) {
    this->currentMsg = msg;
    if (!msg.equals("")) {
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(msg);
        if (root.success() && root.containsKey("msg") && root.containsKey("from") && root.containsKey("to")) {
            String content = root["msg"].asString();
            String sender = root["from"].asString();
            String receiver = root["to"].asString();
            if (sender.equals("python") && content.equals("stop")) {
                pContext->setGameOver(true);
                //Serial.println("REC " + this->currentMsg + " " + pContext->isGameOver());
            }
            if (sender.equals("python") && content.equals("start")) {
                pContext->setGameOver(false);
                //Serial.println("REC " + this->currentMsg + " " + pContext->isGameOver());
            }
            this->ackMsg(sender);
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

void MessageService::sendCode(const int content, const String receiver, const String key) {
    String p = "";
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["from"] = this->from;
    root["to"] = receiver;
    root["msg"] = key;
    root[key] = content;
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

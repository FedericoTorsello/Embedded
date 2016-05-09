#include "MsgService.h"

/* Must be declared here for Arduino serialEvent() */
String content;
String sender;
MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable() {
    return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg() {
    if (msgAvailable) {
        Msg* msg = currentMsg;
        msgAvailable = false;
        currentMsg = NULL;
        sender = "";
        content = "";
        return msg;
    } else {
        return NULL;
    }
}

void MsgServiceClass::init(const int baud, const String&  name) {
    Serial.begin(baud);
    while(!Serial) { }
    // reserve 200 bytes for the inputString:
    content.reserve(256);
    sender.reserve(20);
    content = "";
    sender= "";
    currentMsg = NULL;
    msgAvailable = false;
    sendMsg(name);
}

void MsgServiceClass::sendMsg(const String& msg) {
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["msg"] = msg;
    root.printTo(Serial);
    Serial.flush();
}

void MsgServiceClass::sendMsgTo(const String& who, const String& msg) {
    StaticJsonBuffer<100> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["to"] = who;
    root["msg"] = msg;
    root.printTo(Serial);
    Serial.flush();
}

/* from arduino environment */
void serialEvent() {
    while(Serial.available()) {
        // read byte by byte
        char inChar = (char)Serial.read();
        if (inChar == '\n') {
            MsgService.currentMsg = new Msg(content);
            MsgService.msgAvailable = true;
            break;
        } else
            content += inChar;
    }
}

bool MsgServiceClass::isMsgAvailable(Pattern& pattern) {
    return (msgAvailable && pattern.match(*currentMsg));
}

Msg* MsgServiceClass::receiveMsg(Pattern& pattern) {
    if (msgAvailable && pattern.match(*currentMsg)) {
        Msg* msg = currentMsg;
        msgAvailable = false;
        currentMsg = NULL;
        sender = "";
        content = "";
        return msg;
    } else {
        return NULL;
    }
}

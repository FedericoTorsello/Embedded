#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include "ArduinoJson.h"

class Msg {
public:
    Msg(String content) {
        // Read the message from serial e parse it
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject &root = jsonBuffer.parseObject(content);
        // { "msg": "test1", "from": "serial" }
        if (root.success() && root.containsKey("msg") && root.containsKey("from")) {
            this->content = root["msg"].asString();
            this->sender = root["from"].asString();
        } else {
            JsonObject &root = jsonBuffer.createObject();
            root["to"] = this->sender;
            root["msg"] = "Parse Error";
            Serial.println(root.printTo(Serial));
            Serial.flush();
        }
    }

    String getContent() {
        return content;
    }

    String getSender() {
        return sender;
    }
private:
    String content;
    String sender;
};

class Pattern {
public:
    virtual boolean match(const Msg &) = 0;
};

class MsgServiceClass {
public:
    Msg* currentMsg;
    bool msgAvailable;
    void init(const int, const String &);
    bool isMsgAvailable();
    bool isMsgAvailable(Pattern &);
    Msg* receiveMsg();
    Msg* receiveMsg(Pattern &);
    void sendMsg(const String &);
    void sendMsgTo(const String &, const String &);
};

extern MsgServiceClass MsgService;

#endif

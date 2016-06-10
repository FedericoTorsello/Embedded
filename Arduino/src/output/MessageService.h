#ifndef __MESSAGESERVICE__
#define __MESSAGESERVICE__

#include "../control/Context.h"
#include "Arduino.h"
#include "ArduinoJson.h"

class MessageService {
public:
    void init(const int, const String &, Context *);
    void setMessage(String);
    String getMessage();
    void errorMsg();
    void ackMsg(const String);
    void sendMsg(const String, const String);
    void sendCode(const int, const String, const String);
private:
    String currentMsg = "";
    const String from = "arduino";
    Context *pContext;
};

extern MessageService msgService;

class Msg {
public:
    Msg(String c, String s, String r ) : content(c), sender(s), receiver(r) {
    }
private:
    String content;
    String sender;
    String receiver;
};

#endif

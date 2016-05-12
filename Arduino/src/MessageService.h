#ifndef __MESSAGESERVICE__
#define __MESSAGESERVICE__

#include "Arduino.h"
#include "ArduinoJson.h"

class MessageService {
public:
    void init(const int, const String &);
    void setMessage(String);
    String getMessage();
    void errorMsg();
    void ackMsg(String);
    void sendMsg(String, String, String);
private:
    String currentMsg = "";
    String sender = "";
};

extern MessageService msgService;

class Msg {
public:
    Msg(String c, String s, String r ): content(c), sender(s), receiver(r) {}
private:
    String content;
    String sender;
    String receiver;
};

#endif

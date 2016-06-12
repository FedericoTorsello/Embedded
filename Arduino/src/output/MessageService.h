#ifndef __MESSAGESERVICE__
#define __MESSAGESERVICE__

#include "../control/Context.h"
#include "Arduino.h"
#include "ArduinoJson.h"

/** Class to read and write data on serial */
class MessageService {
public:
    void init(const int, const String &);
    void setMessage(String);
    String getMessage();
    void errorMsg();
    void ackMsg(const String);
    void sendMsg(const String, const String);
    void sendInfo(const int, const int, const uint8_t, const String);
private:
    String currentMsg = "";
    const String from = "arduino";              /**< String of the sender */
};

extern MessageService msgService;

#endif

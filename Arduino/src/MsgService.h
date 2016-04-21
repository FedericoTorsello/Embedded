#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"

class Msg {
  String content;
  String sender;

public:
  Msg(String sender, String content) {
    this->content = content;
    this->sender = sender;
  }

  String getContent(){
    return content;
  }

  String getSender(){
    return sender;
  }
};

class Pattern {
public:
  virtual boolean match(const Msg& m) = 0;
};

class MsgServiceClass {

public:

  Msg* currentMsg;
  bool msgAvailable;

  void init(const String& name);

  bool isMsgAvailable();
  Msg* receiveMsg();

  bool isMsgAvailable(Pattern& pattern);
  Msg* receiveMsg(Pattern& pattern);

  void sendMsg(const String& msg);
  void sendMsgTo(const String& who, const String& msg);
};

extern MsgServiceClass MsgService;

#endif

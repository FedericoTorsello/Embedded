#include "Arduino.h"
#include "MsgService.h"

String content;
String sender;

MsgServiceClass MsgService;

bool MsgServiceClass::isMsgAvailable(){
  return msgAvailable;
}

Msg* MsgServiceClass::receiveMsg(){
  if (msgAvailable){
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

void MsgServiceClass::init(const String&  name){
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  content.reserve(256);
  sender.reserve(20);
  content = "";
  sender="";
  currentMsg = NULL;
  msgAvailable = false;
  Serial.println(String("join:"+name));
}

void MsgServiceClass::sendMsg(const String& msg){
  Serial.println(msg);
}

void MsgServiceClass::sendMsgTo(const String& who, const String& msg){
  Serial.println(String(who+":"+msg));
}

void serialEvent() {

  delay(50);

  /* reading the sender */
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if (inChar==':'){
       break;
    } else {
      sender += inChar;
    }
  }

  /* reading the content */

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // add it to the inputString:
    if (inChar=='$'){
       MsgService.currentMsg = new Msg(sender,content);
       MsgService.msgAvailable = true;
       break;
    } else {
      content += inChar;
    }
  }

}

bool MsgServiceClass::isMsgAvailable(Pattern& pattern){
  return (msgAvailable && pattern.match(*currentMsg));
}

Msg* MsgServiceClass::receiveMsg(Pattern& pattern){
  if (msgAvailable && pattern.match(*currentMsg)){
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

#include "LedMock.h"
#include "Arduino.h"

LedMock::LedMock(int pin){
  this->pin = pin;
}

void LedMock::switchOn(){
  Serial.println("LED " + String(this->pin) + " HIGH");
}

void LedMock::switchOff(){
  Serial.println("LED " + String(this->pin) + " LOW");
};

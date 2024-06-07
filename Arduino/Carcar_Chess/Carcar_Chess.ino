
#include "Button.h"
#include "Motor.h"

String readStringFromSerial()
{
  String str;
  while (Serial.available())
  {
    char c = Serial.read();
    str += c;
  }
  return str;
}

void setup()
{
  Serial.begin(9600);
  Button::setup();
  Motor::setup();
}

void loop()
{ 
  
  delay(100);
}

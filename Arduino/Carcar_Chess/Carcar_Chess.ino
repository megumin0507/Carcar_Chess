
#include "Button.h"

String move;
String oldMove;
bool bSuccess = false;

void printMove()
{
  if (move != oldMove)
  { 
    if (move == "") Serial.println("\"\"");
    else Serial.println(move);
    oldMove = move;
  }
}

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
}

void loop()
{ 
  if (!bSuccess)
  {
    Button::startReadingMove(move, bSuccess);
    printMove();
  }
  
  delay(100);
}

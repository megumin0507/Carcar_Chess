
#include "Button.h"
#include "Motor.h"

bool bSuccess = false;
String oldMove = "";
String move = "";

String moveSequence[5] = {"a1", "e5", "h2", "a4", "a8"};
//String moveSequence[2] = {"a4", "a8"};
int moveSequenceIndex = -1;

void motorTesting()
{ 
  Motor::runSpeed();
  if (Serial.available())
  {
    const char c = Serial.read();
    if (c == 'f')
    {
      YStepper.move(-100);
    }
    if (c == 'b')
    {
      YStepper.move(100);
    }
    if (c == 'l')
    {
      XStepper.move(100);
    }
    if (c == 'r')
    {
      XStepper.move(-100);
    }
    if (c == 'u')
    {
      Motor::moveMagnetUp();
      delay(600);
    }
    if (c == 'd')
    {
      Motor::moveMagnetDown();
      delay(600);
    }
  }
}

String readStringFromSerial1()
{
  String str;
  while (Serial1.available())
  {
    char c = Serial1.read();
    str += c;
    delay(50);
  }
  return str;
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Button::setup();
  Motor::setup(400);
  Motor::moveMagnetUp();

  // Motor::movePiece("a8e4");
  // Motor::movePiece("e4a8");
  // Motor::moveToCoordinate("a8");
}

void loop()
{  
  String btMove = readStringFromSerial1();
  if (btMove != "")
  {
    Serial.print("btMove = ");
    Serial.println(btMove);
    Motor::movePiece(btMove);
    delay(100);
  }

  motorTesting();
  
  //Motor::moveMagnetUp();
  
  
  // if (Motor::isFinishedRunning() && moveSequenceIndex != 4)
  // {
  //   moveSequenceIndex++;
  //   move = moveSequence[moveSequenceIndex];
  //   Serial.println(move);
  //   Motor::moveToCoordinate(move);
  //   delay(500);
  // }
  
  
  // Button::startReadingMove(move, bSuccess);
  // if (move != oldMove && !bSuccess)
  // {
  //   Serial.print("move = ");
  //   Serial.println(move);
  //   oldMove = move;
  // }
}

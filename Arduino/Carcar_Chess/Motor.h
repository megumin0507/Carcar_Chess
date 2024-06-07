
#include <Stepper.h>
#include <Servo.h>
#include <String.h>

#define EN 8
#define STEPX 2
#define DIRX 5
#define STEPY 3
#define DIRY 6
#define SERVO 4

#define SQUARESIZE 200

const int stepsPerRev = 200;
Stepper XStepper(stepsPerRev, STEPX, DIRX);
Stepper YStepper(stepsPerRev, STEPY, DIRY);
Servo servo;

class Motor
{
public:

  static void setup()
  {
    pinMode(EN, OUTPUT);
 	  digitalWrite(EN, LOW);
    
    servo.attach(SERVO);
  }

  static void setSpeed(long inSpeed)
  {
    XStepper.setSpeed(inSpeed);
    YStepper.setSpeed(inSpeed);
  }

  static void moveXTo(char targetCoordinate)
  {
    if (!checkXCoordinate(targetCoordinate))
    {
      Serial.print("[ERROR] Invalid X Coordinate! You entered: ");
      Serial.println(targetCoordinate);
      return;
    }

    /*
     * positive step doesn't mean go from left to right, wait to be confirmed
     */
    XStepper.step(squareSize * (targetCoordinate - currentXCoordinate));
    currentXCoordinate = targetCoordinate;
  }

  static void moveYTo(char targetCoordinate)
  {
    if (!checkYCoordinate(targetCoordinate))
    {
      Serial.print("[ERROR] Invalid Y Coordinate! You entered: ");
      Serial.println(targetCoordinate);
      return;
    }

    /*
     * positive step doesn't mean go from bottom to top, wait to be confirmed
     */
    YStepper.step(squareSize * (targetCoordinate - currentYCoordinate));
    currentYCoordinate = targetCoordinate;
  }

  static void moveTo(String targetCoordinate)
  { 
    if (targetCoordinate.length() != 2)
    {
      Serial.print("[ERROR] Wrong Coordinate length! You entered: ");
      Serial.println(targetCoordinate);
      return;
    }
    const char X = targetCoordinate[0];
    const char Y = targetCoordinate[1];

    if (checkCoordinates(X, Y))
    {
      Serial.print("[ERROR] Invalid Coordinate! You entered: ");
      Serial.println(targetCoordinate);
      return;
    }

    XStepper.step(squareSize * (X - currentXCoordinate));
    YStepper.step(squareSize * (Y - currentYCoordinate));
    currentXCoordinate = X;
    currentYCoordinate = Y;
  }

  static void resumeStepperPosition()
  {
    XStepper.step(-squareSize * (currentXCoordinate - 'a'));
    YStepper.step(-squareSize * (currentYCoordinate - '1'));
    currentXCoordinate = 'a';
    currentYCoordinate = '1';
  }
  
  static void moveMagnetUp()
  {
    servo.write(90);
  }

  static void moveMagnetDown()
  {
    servo.write(0);
  }

private:

  static bool checkXCoordinate(char X)
  {
    return X >= 'a' && X <= 'h';
  }

  static bool checkYCoordinate(char Y)
  {
    return Y >= '1' && Y <= '8';
  }

  static bool checkCoordinates(char X, char Y)
  {
    return checkXCoordinate(X) && checkYCoordinate(Y);
  }

  static int squareSize;
  static char currentXCoordinate;
  static char currentYCoordinate;
};

int Motor::squareSize = SQUARESIZE;
char Motor::currentXCoordinate = 'a';
char Motor::currentYCoordinate = '1';

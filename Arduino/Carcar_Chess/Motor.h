
#include <AccelStepper.h>
#include <Servo.h>

#define STEPX 2
#define DIRX 5
#define STEPY 3
#define DIRY 6
#define SERVO 11

AccelStepper XStepper(1, STEPX, DIRX);
AccelStepper YStepper(1, STEPY, DIRY);
Servo servo;

const int squareSize = 330;

class Motor
{
public:

  static void setup(int speed)
  { 
    maxSpeed = speed;
    XStepper.setMaxSpeed(maxSpeed);
    YStepper.setMaxSpeed(maxSpeed);
    XSpeed = maxSpeed;
    YSpeed = maxSpeed;
    XStepper.moveTo(0);
    YStepper.moveTo(0);

    servo.attach(SERVO);
  }

  static void runSpeed()
  { 
    XStepper.setSpeed(XSpeed);
    XStepper.runSpeedToPosition();
    YStepper.setSpeed(YSpeed);
    YStepper.runSpeedToPosition();
  }

  static void moveToCoordinate(String coordinate)
  {
    if (!checkCoordinate(coordinate)) return;

    const char X = coordinate[0];
    const char Y = coordinate[1];

    const int XIndex = X-'a';
    const int YIndex = '8' - Y;
    const int deltaX = XIndex - currentXIndex;
    const int deltaY = YIndex - currentYIndex;
    if (deltaX == 0 && deltaY == 0) return;

    // Serial.print("deltaX = ");
    // Serial.print(deltaX);
    // Serial.print(", deltaY = ");
    // Serial.println(deltaY);
    
    XSpeed = clamp(maxSpeed * deltaX/(deltaX + deltaY));
    YSpeed = clamp(maxSpeed * deltaY/(deltaX + deltaY));
    XStepper.moveTo(-squareSize * XIndex);
    YStepper.moveTo(squareSize * YIndex);

    // Serial.print("ditance X = ");
    // Serial.print(XStepper.distanceToGo());
    // Serial.print(", distance Y = ");
    // Serial.println(YStepper.distanceToGo());

    currentXIndex = XIndex;
    currentYIndex = YIndex;

    while(!isFinishedRunning()) runSpeed();
  }

  static void movePiece(String move)
  { 
    if (!checkMoveLength(move)) return;

    String firstCoor = getFirstCoorFromMove(move);
    String secondCoor = getSecondCoorFromMove(move);
    if (!checkCoordinate(firstCoor) || !checkCoordinate(secondCoor)) return;

    moveToCoordinate(firstCoor);
    moveMagnetUp();
    delay(500);
    moveToCoordinate(secondCoor);
    moveMagnetDown();
    delay(500);
  }

  static bool isFinishedRunning()
  {
    return XStepper.distanceToGo() == 0 && YStepper.distanceToGo() == 0;
  }
  
  static void moveMagnetUp()
  {
    servo.write(0);
  }

  static void moveMagnetDown()
  {
    servo.write(90);
  }

private:

  static int clamp(int value)
  {
    if (value < 300) value = 300;
    if (value > 600) value = 600;
    return value;
  }

  static bool checkXCoordinate(char X)
  {
    return X >= 'a' && X <= 'h';
  }

  static bool checkYCoordinate(char Y)
  {
    return Y >= '1' && Y <= '8';
  }

  static bool checkCoordinate(String coordinate)
  {
    if (coordinate.length() != 2)
    {
      Serial.print("Coordinate length is wrong! Length: ");
      Serial.println(coordinate.length());
      return false;
    }

    const char X = coordinate[0];
    const char Y = coordinate[1];
    if (!checkXCoordinate(X))
    {
      Serial.print("X coordinate is invalid! X coordinate: ");
      Serial.println(X);
      return false;
    }
    if (!checkYCoordinate(Y))
    {
      Serial.print("Y coordinate is invalid! Y coordinate: ");
      Serial.println(Y);
      return false;
    }

    return true;
  }

  static String getFirstCoorFromMove(String move)
  {
    if (!checkMoveLength(move)) return "";
    String coor = "";
    coor += move[0];
    coor += move[1];
    return coor;
  }

  static String getSecondCoorFromMove(String move)
  {
    if (!checkMoveLength(move)) return "";
    String coor = "";
    coor += move[2];
    coor += move[3];
    return coor;
  }

  static bool checkMoveLength(String move)
  {
    if (move.length() != 4)
    {
      Serial.print("Move length is wrong! Length: ");
      Serial.println(move.length());
      return false;
    }
    return true;
  }

  static int currentXIndex;
  static int currentYIndex;
  static int XSpeed;
  static int YSpeed;
  static int maxSpeed;
};

int Motor::currentXIndex = 0;
int Motor::currentYIndex = 0;
int Motor::XSpeed = 0;
int Motor::YSpeed = 0;
int Motor::maxSpeed = 0;

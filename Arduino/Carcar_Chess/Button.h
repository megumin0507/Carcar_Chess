
#include "Adafruit_Keypad.h"

#define R1 31
#define R2 33
#define R3 35
#define R4 37
#define C1 39
#define C2 41
#define C3 43

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] =
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {R1, R2, R3, R4};
byte colPins[COLS] = {C1, C2, C3};
                                  
Adafruit_Keypad keypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

class Button
{
public:

  static void setup()
  {
    keypad.begin();
  }

  static void startReadingMove(String& inMove, bool& bOutCompleted)
  { 
    keypad.tick();
    if (count == 4)
    {
      bOutCompleted = true;
      count = 0;
    }
    if (keypad.available())
    {
      keypadEvent event = keypad.read();
      const char key_char = (char)event.bit.KEY;
      const int key_int = event.bit.KEY - '0';

      if (!isValidKey(key_char)) return;
      //backspace
      if (key_char == '#')
      {
        if (event.bit.EVENT == KEY_JUST_PRESSED && bReleased[0] && inMoveIsNotEmpty())
        { 
          inMove.remove(inMove.length()-1);
          count--;
          bReleased[0] = false;
        }
        else if (event.bit.EVENT == KEY_JUST_RELEASED)
        {
          bReleased[0] = true;
        }
      }
      //normal number
      else
      {
        if (event.bit.EVENT == KEY_JUST_PRESSED && bReleased[key_int])
        { 
          char moveGot;
          if (isReadingLetter())
          {
            moveGot = key_int-1 + 'a';
          }
          if (isReadingNumber())
          {
            moveGot = key_int + '0';
          }
          inMove += moveGot;
          count++;
          bReleased[key_int] = false;
        }
        else if (event.bit.EVENT == KEY_JUST_RELEASED)
        {
          bReleased[key_int] = true;
        }
      }
    }
  }
private:

  static bool isReadingLetter() { return count == 0 || count == 2; }
  static bool isReadingNumber() { return count == 1 || count == 3; }
  static bool inMoveIsNotEmpty() { return !count == 0; }
  static bool isValidKey(char c) { return c >= '1' && c <= '8' || c == '#'; }

  static int count;
  static bool bReleased[9];
};

int Button::count = 0;
bool Button::bReleased[9] = {true, true, true, true, true, true, true, true, true};

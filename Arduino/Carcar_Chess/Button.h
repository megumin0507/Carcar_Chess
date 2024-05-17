
#define BA 2
#define B1 3
#define BBS 4

class Button
{
public:

  static void setup()
  {
    pinMode(BA, INPUT_PULLUP);
    pinMode(B1, INPUT_PULLUP);
    pinMode(BBS, INPUT_PULLUP);
  }

  static void startReadingMove(String& inMove, bool& bOutSuccess)
  {
    if (digitalRead(BA) == LOW && isReadingLetter())
    {
      inMove += 'a';
      count++;
    }
    else if (digitalRead(B1) == LOW && isReadingNumber())
    {
      inMove += '1';
      count++;
    }
    else if (digitalRead(BBS) == LOW && bReleased && inMoveIsNotEmpty())
    {
      inMove.remove(inMove.length()-1, 1);
      bReleased = false;
      count--;
    }

    if (digitalRead(BBS) == HIGH)
    {
      bReleased = true;
    }
    if (count == 4)
    {
      bOutSuccess = true;
      count = 0;
    }
  }
private:

  static bool isReadingLetter() { return count == 0 || count == 2; }
  static bool isReadingNumber() { return count == 1 || count == 3; }
  static bool inMoveIsNotEmpty() { return !count == 0; }

  static int count;
  static bool bReleased;
};

int Button::count = 0;
bool Button::bReleased = true;

#include <Arduino.h>
#include "ILI9341_t3.h"


class StatusBar {
  public:
    StatusBar(ILI9341_t3 * tft, int x = 0, int y = 0, byte lenght = 90, byte high = 6); //Constructor
    ~StatusBar();//Decons
    void DrawIt(byte val = 0);
    void DrawBorder();
    void StatBar();
    int ReturnX();
    int ReturnY();
  private:
    uint16_t ColorConvert(uint8_t r, uint8_t g, uint8_t b);
    bool _firstRun = true;
    byte _val, _oldVal, _lenght, _height;
    int _x, _y;
    ILI9341_t3* _tft;
};

//Constructor
StatusBar::StatusBar(ILI9341_t3 * tft, int x, int y, byte lenght, byte high)
{
  _x = x;
  _y = y;
  _tft = tft;
  _lenght = lenght;
  _height = high;
}

//Deconstructor
StatusBar::~StatusBar(void)
{
  //Fill this later
}

//Return internal values
int StatusBar::ReturnX() {
  return _x;
}
int StatusBar::ReturnY() {
  return _y;
}


//Draw Call
void StatusBar::DrawIt(byte val)
{
  _val = map(val, 0, 100, 0, _lenght - 2); //Map the incoming value to internal value


  if (_firstRun)
  {
    DrawBorder();
    StatBar();
    _oldVal = _val;
    _firstRun = false;

  }
  else
  {
    StatBar();
    _oldVal = _val;

  }

}

//Convert drawRGB24toRGB565
uint16_t StatusBar::ColorConvert(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

void StatusBar::StatBar()
{
  if (_oldVal == _val) {}

  else if (_oldVal < _val) {
    //Fill New
    while (_oldVal < _val)
    {
      _tft->fillRect(_x + 2, _y + 1, _oldVal, _height - 2, ILI9341_BLUE);
      _oldVal++;

    }
  }
  else {
    //Delete Old
    while (_oldVal > _val)
    {
      _tft->fillRect(_oldVal + _x, _y + 1, 1, _height - 2, ILI9341_BLACK);
      _oldVal--;
    }
  }
}

void StatusBar::DrawBorder()
{
  _tft->drawRect(_x, _y, _lenght, _height, ILI9341_WHITE);
}


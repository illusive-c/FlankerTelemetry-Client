#include <Arduino.h>
#include "ILI9341_t3.h"


class BarGraph {
  public:
    BarGraph(ILI9341_t3 * tft, int x = 0, int y = 0, byte lenght = 90, byte high = 6, int minVal = 0, int maxVal = 100); //Constructor
    void DrawIt(int val = 0);
  private:
    bool _firstRun = true;
    byte _val, _oldVal, _lenght, _height;
    int _x, _y, _maxVal, _minVal;
    int _values[40];
    ILI9341_t3* _tft;
};

//Constructor
BarGraph::BarGraph(ILI9341_t3 * tft, int x, int y, byte lenght, byte high, int minVal, int maxVal)
{
  _x = x;
  _y = y;
  _tft = tft;
  _lenght = lenght;
  _height = high;
}

void BarGraph::DrawIt(int val)
{
  if (_firstRun)
  {
    _firstRun = false;
    _tft->drawRect(_x,_y,_lenght,_height, ILI9341_WHITE);
  }
}

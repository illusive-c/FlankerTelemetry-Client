#include "class_CircularBuffer.h"

Que _queue(28);

class BarGraph
{
  private:
    bool _firstRun = true;
    int _maxspeed = MAXDOWNLOAD;
    byte _val, _oldVal, _lenght, _height, _barWidth;
    int _x, _y, _maxVal, _minVal;
    int _values[30];
    byte _currentIndex;
    ILI9341_t3* _tft;
    void DrawL(int x, int var);

  public:

    BarGraph(ILI9341_t3 * tft, int x = 0, int y = 0, byte lenght = 90, byte high = 30, byte barWidth = 2, int maxspeed = 1); //Constructor
    void DrawIt(int val = 0);
};

//Constructor
BarGraph::BarGraph(ILI9341_t3* tft, int x, int y, byte lenght, byte high, byte barWidth, int maxspeed)
{
  _currentIndex = 0;
  _tft = tft;
  _barWidth = barWidth;
  _x = x;
  _y = y;
  _tft = tft;
  _lenght = lenght;
  _height = high;
  _maxspeed = maxspeed;

}

void BarGraph::DrawIt(int val)
{
  if (_firstRun)
  {
    _firstRun = false;
    _tft->drawRect(_x, _y, _lenght, _height, ILI9341_WHITE);
  }

  _queue.addItem(val);

  _tft->fillRect(_x + 1, _y + 1, _lenght - 3, _height - 3, ILI9341_BLACK);//Delete
  for (byte i = 0; i < _queue.count(); i++)
  {
    int k = map(_queue.peek(i), 0, _maxspeed, 0, 25);
    this->DrawL(_x + 2 + (i * 3), k);
  }

}

void BarGraph::DrawL(int x, int var)
{
  if (var < 28) {
    int startY = _y + _height - 4;
    for (byte i = 1; i < 3; i++)
    {
      _tft->drawLine(x + i, startY, x + i, startY - var, ILI9341_WHITE);
    }
  }
}

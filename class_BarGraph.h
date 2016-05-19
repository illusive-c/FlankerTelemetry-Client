class BarGraph
{
  private:
    bool _firstRun = true;
    byte _val, _oldVal, _lenght, _height, _barWidth;
    int _x, _y, _maxVal, _minVal;
    int _values[30];
    byte _currentIndex;
    ILI9341_t3* _tft;
    void DrawL(int x, byte var);

  public:
    QueueArray <int> _queue;
    BarGraph(ILI9341_t3 * tft, int x = 0, int y = 0, byte lenght = 90, byte high = 30, byte barWidth = 2); //Constructor
    void DrawIt(int val = 0);
};

//Constructor
BarGraph::BarGraph(ILI9341_t3* tft, int x, int y, byte lenght, byte high, byte barWidth)
{
  _currentIndex = 0;
  _tft = tft;
  _barWidth = barWidth;
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
    _tft->drawRect(_x, _y, _lenght, _height, ILI9341_WHITE);
  }
  if (_queue.count() >= 27)
  {
    _queue.pop();
  }
  _queue.enqueue(val);
  for (byte i = 0; i < _queue.count(); i++)
  {

  }

  _tft->fillRect(_x + 1, _y + 1, _lenght - 3, _height - 3, ILI9341_BLACK);//Delete

  if (val < 26) {
    DrawL(_x + 2, val);
  }
}

void BarGraph::DrawL(int x, byte var)
{
  byte startY = _y + _height - 4;
  for (byte i = 1; i < 3; i++)
  {
    _tft->drawLine(x + i, startY, x + i, startY - var, ILI9341_WHITE);
  }
}

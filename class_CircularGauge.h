//Modified version of 
//https://learn.adafruit.com/2-8-tft-touchscreen/graphics-library

#include <Arduino.h>
#include "ILI9341_t3.h"

#define ILI9341_GREY 0x2104 // Dark grey 16 bit colour

class CircularGauge
{
  private:
    bool _firstRun = true;
    int _oldValue = 1;
    unsigned int _x, _y, _r, _w;
    unsigned int _vmin, _vmax;
    int _angle = 150;
    byte _scheme;
    String _units;
    ILI9341_t3* _tft;
    unsigned int rainbow(byte value);
    void Draw(int value);
  public:
    CircularGauge(ILI9341_t3* tft, int vmin, int vmax, int x, int y, int r, String units, byte scheme);//Constructor
    void DrawIt(int val);
    void Clear();//Paint the are used by the clas to black
};


CircularGauge::CircularGauge(ILI9341_t3* tft, int vmin, int vmax, int x, int y, int r, String units, byte scheme)
{
  _tft = tft;
  _vmin = vmin;
  _vmax = vmax;
  _x = x + r;
  _y = y + r; //calculate center
  _w = r / 4;
  _r = r;
  _units = units;
  _scheme = scheme;


}

void CircularGauge::Clear()
{
  _tft->fillCircle(_x, _y, _r + 2, ILI9341_BLACK);

}

void CircularGauge::DrawIt(int val)
{
  if (_oldValue == val) {
    return;
  }
  else
  {
    _oldValue = val;
    this->Draw(val);
  }
}

void CircularGauge::Draw(int value)
{
  if (_firstRun)
  {
    this->Clear();
    _tft->drawCircle(_x, _y, _r + 1, ILI9341_WHITE);
    _tft->drawCircle(_x, _y, _r + 2, ILI9341_WHITE);
    _firstRun = false;
  }
  int text_colour = 0; // To hold the text colour

  int v = map(value, _vmin, _vmax, -_angle, _angle); // Map the value to an angle v

  byte seg = 5; // Segments are 5 degrees wide = 60 segments for 300 degrees
  byte inc = 10; // Draw segments every 5 degrees, increase to 10 for segmented ring

  // Draw colour blocks every inc degrees
  for (int i = -_angle; i < _angle; i += inc) {

    // Choose colour from scheme
    int colour = 0;
    switch (_scheme) {
      case 0: colour = ILI9341_RED; break; // Fixed colour
      case 1: colour = ILI9341_GREEN; break; // Fixed colour
      case 2: colour = ILI9341_BLUE; break; // Fixed colour
      case 3: colour = rainbow(map(i, -_angle, _angle, 0, 127)); break; // Full spectrum blue to red
      case 4: colour = rainbow(map(i, -_angle, _angle, 63, 127)); break; // Green to red (high temperature etc)
      case 5: colour = rainbow(map(i, -_angle, _angle, 127, 63)); break; // Red to green (low battery etc)
      default: colour = ILI9341_BLUE; break; // Fixed colour
    }

    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * 0.0174532925);
    float sy = sin((i - 90) * 0.0174532925);
    uint16_t x0 = sx * (_r - _w) + _x;
    uint16_t y0 = sy * (_r - _w) + _y;
    uint16_t x1 = sx * _r + _x;
    uint16_t y1 = sy * _r + _y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * 0.0174532925);
    float sy2 = sin((i + seg - 90) * 0.0174532925);
    int x2 = sx2 * (_r - _w) + _x;
    int y2 = sy2 * (_r - _w) + _y;
    int x3 = sx2 * _r + _x;
    int y3 = sy2 * _r + _y;

    if (i < v) { // Fill in coloured segments with 2 triangles
      _tft->fillTriangle(x0, y0, x1, y1, x2, y2, colour);
      _tft->fillTriangle(x1, y1, x2, y2, x3, y3, colour);
      text_colour = colour; // Save the last colour drawn
    }
    else // Fill in blank segments
    {
      _tft->fillTriangle(x0, y0, x1, y1, x2, y2, ILI9341_GREY);
      _tft->fillTriangle(x1, y1, x2, y2, x3, y3, ILI9341_GREY);
    }
  }

  // Set the text colour to default
  //tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  // Uncomment next line to set the text colour to the last segment value!
  _tft->setTextColor(text_colour, ILI9341_BLACK);

  _tft->setTextSize(3);

  //Center the text depending on the value
  if (value < 10)_tft->setCursor (_x - 8, _y - 12);
  else if (value < 100) {
    _tft->setCursor (_x - 17, _y - 12);
  }
  else {
    _tft->setCursor (_x - 25 , _y - 12);
  }
  
  _tft->print(value);

  //Draw the unit
  _tft->setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  _tft->setTextSize(1);
  _tft->setCursor(_x - 8, _y + 15);
  _tft->print(_units);

}



// #########################################################################
// Return a 16 bit rainbow colour
// #########################################################################
unsigned int CircularGauge::rainbow(byte value)
{
  // Value is expected to be in range 0-127
  // The value is converted to a spectrum colour from 0 = blue through to 127 = red

  byte red = 0; // Red is the top 5 bits of a 16 bit colour value
  byte green = 0;// Green is the middle 6 bits
  byte blue = 0; // Blue is the bottom 5 bits

  byte quadrant = value / 32;

  if (quadrant == 0) {
    blue = 31;
    green = 2 * (value % 32);
    red = 0;
  }
  if (quadrant == 1) {
    blue = 31 - (value % 32);
    green = 63;
    red = 0;
  }
  if (quadrant == 2) {
    blue = 0;
    green = 63;
    red = value % 32;
  }
  if (quadrant == 3) {
    blue = 0;
    green = 63 - 2 * (value % 32);
    red = 31;
  }
  return (red << 11) + (green << 5) + blue;
}

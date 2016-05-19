#include <Arduino.h>

class Que {
  private:
    byte _size;
    int * items = NULL;
    int _icount = 0;
    int shift();
  public:
    Que(int val);
    void addItem(int val);
    void setSize(byte val);
    int peek(int i);
    int count();
};

Que::Que(int Size) {
  _size = Size;
  items = (int *)malloc (_size * sizeof (int)+1);
  for (int i=0; i <_size;i++)
  {
    items[i]= 2;
    }
}

void Que::addItem(int val)
{
  shift();
  items[0] = val;
  if (_icount != _size) _icount++;

}

int Que::shift() {
  if (_icount != 0) {
    int retVal = items[_icount - 1];

    for (int i = _icount; i > 0; i--)
    {
      items[i] = items[i-1];
    }
    return retVal;
  }
  else return 0;
}

int Que::peek(int i)
{
  return items[i];
}

int Que::count()
{
  return _icount;
}

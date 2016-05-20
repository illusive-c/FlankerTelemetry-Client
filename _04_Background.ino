/*
 * Draw static background elements. 
 * 
 * 20/05/2016
 * Flanker
 */

void DrawBox(int x, int y, int h = SQR, int w = SQR / 2, String text = "" )
{
  //tft.drawRect(x, y, h, w, ILI9341_WHITE);
  tft.drawRoundRect(x, y, h, w, 2, ILI9341_WHITE);
  tft.setCursor(x + 6, y + 5);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println(text);
}

void DrawBackGround() 
{

  //White Border
  tft.fillRect(0, 0, WIDTH, HEIGHT, ILI9341_WHITE);
  tft.fillRect(2, 2, WIDTH - 4, HEIGHT - 4, ILI9341_BLACK);

  //Seperator Lines
  tft.fillRect(2, 15, 317, 3, ILI9341_WHITE); //Top horizontal line
  tft.fillRect(260, 2, 3, 15, ILI9341_WHITE);//Top vertical line(left of clock)
  tft.fillRect(2, 179, 317, 3, ILI9341_WHITE);//Bottom horizontal line

  //Bottom Boxes
  DrawBox(PADDING , 185, SQR, SQR / 2, "CPU Load %");
  DrawBox(PADDING * 2 + SQR , 185, SQR, SQR / 2, "NET");
  DrawBox(PADDING * 3 + SQR * 2 , 185, SQR, SQR / 2, "Temp");

  //Central Boxes
  const byte BoxWidth = ((WIDTH - 2 * PADDING) - PADDING) / 2;
  const byte BoxHeight = (174 - PADDING * 4) / 2;
  DrawBox(PADDING, 20, BoxWidth, BoxHeight, "1");
  DrawBox(PADDING * 2 + BoxWidth, 20, BoxWidth, BoxHeight, "2");
  DrawBox(PADDING, 20 + BoxHeight + 2, BoxWidth, BoxHeight, "3");
  DrawBox(PADDING * 2 + BoxWidth, 20 + BoxHeight + 2, BoxWidth, BoxHeight, "4");
}

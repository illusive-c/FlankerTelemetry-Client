//Buffer
String lastCPU;

//Draw CPU Load and RAM Load graphs
void CPU_Load_Draw(byte CPU_Load, byte CPU1_Load, byte CPU2_Load, byte CPU3_Load, byte CPU4_Load,  byte RAM_Load) {

  if (!recvInProgress) {
    tft.setTextSize(1);
    //Total Load
    if (lastCPU != CPU_Load) {
      tft.setCursor(SQR / 2 + 32, HEIGHT - SQR / 2 - PADDING + 3);
      tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
      if (CPU_Load == 100)CPU_Load = 99;//Make sure CPU load text never reaches 100
      tft.println(CPU_Load);
      lastCPU = CPU_Load;
    }

    CPU1LoadBar.DrawIt(CPU1_Load);
    CPU2LoadBar.DrawIt(CPU2_Load);
    CPU3LoadBar.DrawIt(CPU3_Load);
    CPU4LoadBar.DrawIt(CPU4_Load);



  }
}
void DateDraw(String date, String day)
{
  String  temp = date + " " + day;
  tft.setTextSize(1);
  tft.setCursor(5, 5);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.println(date + " " + day);
}

void HourDraw(String hour)
{
  tft.setTextSize(1);
  tft.setCursor(266, 5);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.println(hour);
}


//Draw IP Adress
void IP_Draw(bool stat, String ip)
{
  tft.setTextSize(1);
  tft.setCursor(PADDING * 2 + SQR + 2, 200);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.println(ip);
}


void Net_Draw(int up, int down) {

  tft.fillRect(PADDING * 2 + SQR + 2, 210,30,10,ILI9341_BLACK);
  tft.setTextSize(1);
  tft.setCursor(PADDING * 2 + SQR + 2, 210);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.println(SpeedConvert(down));

  /*
   *  downBar.setValue(map(down, 0, maxDownSpeed, 0, 100));
   t_Down.setText(ConvertStr(SpeedConvert(down)));
   */
  /*
    upBar.setValue(map(up, 0, maxUpSpeed, 0, 100));
    t_Up.setText(ConvertStr(SpeedConvert(up) ));
    //debug((String)downSpeed);
  */
}

/*
void VolumeDraw(bool Mute, int Volume, int Peak)
{
  if (Mute == true) j4.setValue(0);
  else   j4.setValue(Volume);

  peakBar.setValue(Peak);

}
*/

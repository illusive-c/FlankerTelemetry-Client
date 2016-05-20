/*********************************************************************************************************************************  
   Flanker Telemetry's client side code
   -------------------------------------------------------------------------------------------------------------------------------
   Required Hardware:
   
   -Teensy Development Board https://www.pjrc.com/store/teensy32.html
      Very powerful 32Bit development board. I used 3.2 version but I believe this code should work for 3.1 and LC variants also.
      NOTE: Theoretically you could adapt this code to work with any arduino, but the display refresh rate is absymal with them. 
            With teensy 3.2 and it's optimized library I can reach 60+hz refresh rates. Arduino nano struggles even with 1hz.
            
   -ILI9341 SPI TFT(320x240) http://goo.gl/noX1DK
      
   -------------------------------------------------------------------------------------------------------------------------------   
   Required External Libraries:
   
   -ILI9341_t3.h - https://github.com/PaulStoffregen/ILI9341_t3/blob/master/ILI9341_t3.h
   Specific library for Teensy boards and ILI9341 based TFT displays. Optimized to within an inch of it's life. 
   Superb work from PaulStoffregen.
  -------------------------------------------------------------------------------------------------------------------------------                   
  License: BSD License
  20/05/2016
  Can "Flanker" Sahin
  can at cansahin.net
*********************************************************************************************************************************/


#include <SPI.h>
#include <ILI9341_t3.h>
#include "Includes.h"
#include "class_BarGraph.h"
#include "class_StatusBar.h"
#include "class_CircularGauge.h"

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

StatusBar CPU1LoadBar(&tft, 10, 200);
StatusBar CPU2LoadBar(&tft, 10, 208);
StatusBar CPU3LoadBar(&tft, 10, 216);
StatusBar CPU4LoadBar(&tft, 10, 224);

BarGraph NetGraph(&tft, 114, 200, 93, 29, 2, MAXDOWNLOAD);

CircularGauge G1(&tft, 0, 100, 120, 60, 40, "FPS", 5);

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  DrawBackGround();

  CPU1LoadBar.DrawIt(0);
  CPU2LoadBar.DrawIt(0);
  CPU3LoadBar.DrawIt(0);
  CPU4LoadBar.DrawIt(0);

  G1.DrawIt(0);
}


void loop() {
  //debug(random(100));
  SerialRead();
  showNewData();
  HeartBeat();
  //debug(Benchmark(false));
}

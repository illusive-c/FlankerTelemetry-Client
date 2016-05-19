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

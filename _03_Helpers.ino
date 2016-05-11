
//debug
void debug(String message) {
  /*tft.setCursor(10, 100);
  tft.setTextColor(WHITE,BLACK);  tft.setTextSize(2);
  tft.println(message);*/
  Serial.println(message);
}
//

//Check if serial connection with PC is active
void HeartBeat() {
  if (millis() - lastStatus > 1000) {
    cStatus = false;
  }
  else {
    cStatus = true;
  }
}


//Convert speed from Kbps to Mbps
String SpeedConvert(int inc) {
  if (inc > 999)
  {
    return String(inc / 1000) + "M";
  }
  else return String (inc) + "K";
}

//Benchmarking
String Benchmark ()
{

  unsigned long currentMicros = micros();
  String temp = String(currentMicros - previousMicros);
  previousMicros = currentMicros;
  return (temp + " ms");


}


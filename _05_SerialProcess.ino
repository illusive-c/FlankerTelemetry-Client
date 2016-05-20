/*
 * Serial operations happen here. Reads incoming lines (terminated by "\0")
 * Depending on the tag string is routed to different functions.
 * 
 * Note: Maximum lenght of incoming string is 64 bytes
 * 
 * TODO: 
 *       -Needs some tidying up. While performance is pretty good, style and readability 
 *           could be better. 
 * 
 *       -Maybe implement a parity check? Current sanity checks are quite effective 
 *           but there may be need for a more robust system down the line
 *           
 *           
 * 20/05/2016
 * Flanker
 */

void SerialRead() {

  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true && rc != startMarker) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= NUMCHARS) {
          ndx = NUMCHARS - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      memset(receivedChars, 0, 100);
      ndx = 0;
      recvInProgress = true;
    }
  }
}

void showNewData() {
  if (newData == true && !recvInProgress) {
    //debug(receivedChars);
    typeSelect(receivedChars);
    newData = false;
  }
}


void typeSelect(char data[NUMCHARS]) {

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(data, ",");     // get the first part - the string
  DataType = String(strtokIndx);
  //debug("Type: " + DataType)  ;
  lastStatus = millis();//Heathbeat functions variable. Marks when the last packet was received. 


  if (DataType == "CON") {
    Serial.println("<pong>\n");
    cDebug = true;

  }

  if (DataType == "STP") {
    cDebug = false;
    Serial.flush();
    delay(1000);
    cDebug = true;

  }

  //CPU and RAM LOAD
  if (DataType == "LOD") {

    strtokIndx = strtok(NULL, ",");
    byte CPU_Load = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    byte CPU1_Load = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    byte CPU2_Load = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    byte CPU3_Load = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    byte CPU4_Load = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    byte RAM_Load = atoi(strtokIndx);

     //    Draw_Ram();
    CPU_Load_Draw(CPU_Load, CPU1_Load, CPU2_Load, CPU3_Load, CPU4_Load, RAM_Load);
  }

  else if (DataType == "CTM") {// CPU Temperature

    strtokIndx = strtok(NULL, ",");
    CPU_Temp = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    CPU1_Temp = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    CPU2_Temp = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    CPU3_Temp = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    CPU4_Temp = atoi(strtokIndx);

    //    CPU_Temp_Draw();
    //debug (String(CPU_Temp));
  }

  else if (DataType == "NTW")//Download And Upload Speed
  {
    strtokIndx = strtok(NULL, ",");
    int downSpeed = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    int upSpeed = atoi(strtokIndx);

    Net_Draw(upSpeed, downSpeed);

  }

  else if (DataType == "IPA")
  {
    strtokIndx = strtok(NULL, ",");
    bool stat(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    String ip(strtokIndx);

    IP_Draw(stat, ip);
  }
  //DATE
  else if (DataType == "TME")
  {

    strtokIndx = strtok(NULL, ",");
    String date(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    String day(strtokIndx);

    DateDraw(date, day);
  }
  //HOUR
  else if (DataType == "HOR")
  {

    strtokIndx = strtok(NULL, ",");
    String hour(strtokIndx);

    HourDraw(hour);
  }



  /*
    else if (DataType == "VOL")
    { //Get sound information
      bool Mute;

      strtokIndx = strtok(NULL, ",");
      int Volume = atoi(strtokIndx);
      strtokIndx = strtok(NULL, ",");
      if (String(strtokIndx) == "True")
      {
        Mute = true;
      }
      else
      {
        Mute = false;
      }
      strtokIndx = strtok(NULL, ",");
      int Peak = atoi(strtokIndx);
      VolumeDraw(Mute, Volume, Peak);
    }

  }

  */

  else
  {
    //debug("Unrecognized packet received: " + DataType);
  }
}

